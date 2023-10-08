#pragma once

#include "../utils.h"

class i_engine_client {
public:
	void cbuf_add_text(int e_target, const char *p_text, int n_tick_delay) {
		auto client_cmd_addr = utils::memory::get_virtual(this, offsets::client_cmd);
		utils::memory::read<void(__cdecl *)(int, const char *, int)>(client_cmd_addr + offsets::cbuf_add_text)(e_target, p_text, n_tick_delay);
	}
	void client_cmd(const char *sz_cmd_string) {
		return utils::memory::call_virtual<void>(offsets::client_cmd, this, sz_cmd_string);
	}
	void execute_client_cmd(const char *sz_cmd_string) {
		return utils::memory::call_virtual<void>(offsets::execute_client_cmd, this, sz_cmd_string);
	}
	int get_active_split_screen_slot() {
		return utils::memory::call_virtual<int>(offsets::get_active_split_screen_slot, this);
	}

public:
	void cbuf_add(const char *text, int delay) {
		auto e_target = this->get_active_split_screen_slot();
		this->cbuf_add_text(e_target, text, delay);
	}
	void safe_unload() {
		this->client_cmd("wormhole_exit");
	}
};