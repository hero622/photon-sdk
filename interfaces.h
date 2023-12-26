#pragma once

#include "interfaces/console.h"
#include "interfaces/cvar.h"
#include "interfaces/engine_client.h"
#include "interfaces/font_manager.h"
#include "interfaces/input_system.h"
#include "interfaces/mem_alloc.h"
#include "interfaces/scheme.h"
#include "interfaces/surface.h"

class c_portal2 {
public:
	virtual void *get_interface( const char *module_name, const char *interface_name );

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
	void *engine_vgui_internal;
	i_mem_alloc *mem_alloc;
	i_input_system *input_system;
	void *base_client_dll;
	i_scheme_manager *scheme_manager;
	i_scheme *scheme;
	i_input_stack_system *input_stack_system;
	void *vgui_input;
	c_font_manager *font_manager;
};
