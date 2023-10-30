#pragma once

#include "../portal2.h"
#include "../source_sdk.h"

class i_scheme {
public:
	sdk::h_font get_font( const char *font_name, bool proportional = false ) {
		return utils::memory::call_virtual<sdk::h_font>( offsets::get_font, this, font_name, proportional );
	}
};

class i_scheme_manager {
public:
	i_scheme *get_i_scheme( unsigned long scheme ) {
		return utils::memory::call_virtual<i_scheme *>( offsets::get_i_scheme, this, scheme );
	}
};
