#pragma once

#include "../source_sdk.h"

struct c_font_amalgam {
	struct font_range_t {
		int low_range;
		int high_range;
		void *win32_font;
	};

	sdk::utl_vector<font_range_t> fonts;
	int max_width;
	int max_height;
};

struct c_font_manager {
	sdk::utl_vector<c_font_amalgam> font_amalgams;
	sdk::utl_vector<void *> win32_fonts;

	char language[ 64 ];
	void *file_system;
	void *material_system;
};
