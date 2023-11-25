#pragma once

#include "../source_sdk.h"

class i_scheme {
public:
	sdk::h_font get_font( const char *font_name, bool proportional = false ) {
		return utils::memory::call_virtual<os( 3, 4 ), sdk::h_font>( this, font_name, proportional );
	}
};

class i_scheme_manager {
public:
	i_scheme *get_i_scheme( unsigned long scheme ) {
		return utils::memory::call_virtual<os( 8, 9 ), i_scheme *>( this, scheme );
	}
};
