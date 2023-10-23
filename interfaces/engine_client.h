#pragma once

#include "../portal2.h"
#include "../utils.h"

class i_engine_client {
public:
	void cbuf_add_text(int target, const char *text, int tick_delay) {
		auto client_cmd_addr = utils::memory::get_virtual(this, offsets::client_cmd);
		utils::memory::read<void(__cdecl *)(int, const char *, int)>(client_cmd_addr + offsets::cbuf_add_text)(target, text, tick_delay);
	}
	void client_cmd(const char *cmd_string) {
		return utils::memory::call_virtual<void>(offsets::client_cmd, this, cmd_string);
	}
	void execute_client_cmd(const char *cmd_string) {
		return utils::memory::call_virtual<void>(offsets::execute_client_cmd, this, cmd_string);
	}
	int get_active_split_screen_slot() {
		return utils::memory::call_virtual<int>(offsets::get_active_split_screen_slot, this);
	}
	void *get_input_context(int id) {
		return utils::memory::call_virtual<void *>(offsets::get_input_context, this, id);
	}

public:
	void cbuf_add(const char *text, int delay) {
		auto target = this->get_active_split_screen_slot();
		this->cbuf_add_text(target, text, delay);
	}
};