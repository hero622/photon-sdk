#pragma once

#include "../source_sdk.h"

class i_cvar {
public:
	void register_con_command( sdk::con_command_base *command_base ) {
		return utils::memory::call_virtual<9, void>( this, command_base );
	}
	void unregister_con_command( sdk::con_command_base *command_base ) {
		return utils::memory::call_virtual<10, void>( this, command_base );
	}
	sdk::con_command_base *find_command_base( const char *name ) {
		return utils::memory::call_virtual<13, sdk::con_command_base *>( this, name );
	}

public:
	sdk::con_var *find_con_var( const char *name ) {
		return reinterpret_cast<sdk::con_var *>( find_command_base( name ) );
	}
};
