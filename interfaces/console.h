#pragma once

#include "../portal2.h"
#include "../source_sdk.h"
#include "../utils.h"

class c_console {
public:
	void(__cdecl *msg)(const char *msg_format, ...);
	void(__cdecl *color_msg)(const sdk::color_t &clr, const char *msg_format, ...);
	void(__cdecl *warning)(const char *msg_format, ...);
	void(__cdecl *dev_msg)(const char *msg_format, ...);
	void(__cdecl *dev_warning)(const char *msg_format, ...);

public:
	c_console(void *ptr) {
		this->msg = utils::memory::get_sym_addr<decltype(msg)>(ptr, symbols::msg);
		this->color_msg = utils::memory::get_sym_addr<decltype(color_msg)>(ptr, symbols::color_msg);
		this->warning = utils::memory::get_sym_addr<decltype(warning)>(ptr, symbols::warning);
		this->dev_msg = utils::memory::get_sym_addr<decltype(dev_msg)>(ptr, symbols::dev_msg);
		this->dev_warning = utils::memory::get_sym_addr<decltype(dev_warning)>(ptr, symbols::dev_warning);
	}
};