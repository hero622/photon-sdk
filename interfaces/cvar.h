#pragma once

#include "../portal2.h"
#include "../source_sdk.h"

class i_cvar {
public:
	void register_con_command(sdk::con_command_base *p_command_base) {
		return utils::memory::call_virtual<void>(offsets::register_con_command, this, p_command_base);
	}
	void unregister_con_command(sdk::con_command_base *p_command_base) {
		return utils::memory::call_virtual<void>(offsets::unregister_con_command, this, p_command_base);
	}
	sdk::con_command_base *find_command_base(const char *name) {
		return utils::memory::call_virtual<sdk::con_command_base *>(offsets::find_command_base, this, name);
	}
};