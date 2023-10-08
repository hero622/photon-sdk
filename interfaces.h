#pragma once

#include "interfaces/console.h"
#include "interfaces/cvar.h"
#include "interfaces/engine_client.h"
#include "interfaces/surface.h"
#include "utils.h"

#include <string>

template <typename ret>
ret *get_interface(const std::string &module_name, const std::string &interface_name) {
	using create_interface_fn = void *(*)(const char *, int *);
	const auto fn = utils::memory::get_sym_addr<create_interface_fn>(utils::memory::get_module_handle(module_name.c_str()), "CreateInterface");

	if (fn) {
		void *result = nullptr;

		result = fn(interface_name.c_str(), nullptr);

		if (!result)
			return nullptr;

		utils::console::log("found interface %s in %s at %p.\n", interface_name.c_str(), module_name.c_str(), result);

		return static_cast<ret *>(result);
	}

	return nullptr;
}

class c_portal2 {
public:
	c_console *console;
	i_cvar *cvar;
	void *server_game_dll;
	void *engine_api;
	void *engine;
	i_engine_client *engine_client;
	void *client_state;
	void *server_plugin_helpers;
	i_surface *surface;
	void *i_engine_vgui_internal;
};