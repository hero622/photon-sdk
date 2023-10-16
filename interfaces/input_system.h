#pragma once

#include "../portal2.h"

class i_input_system {
public:
	void enable_input(bool enable) {
		return utils::memory::call_virtual<void>(offsets::enable_input, this, enable);
	}
	bool is_button_down(sdk::button_code_t code) {
		return utils::memory::call_virtual<bool>(offsets::is_button_down, this, code);
	}
	void get_cursor_position(int *x, int *y) {
		return utils::memory::call_virtual<void>(offsets::get_cursor_position, this, x, y);
	}
};