#pragma once

#include "interfaces/command_line.h"
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
	// client
	void *base_client_dll;

	// engine
	i_engine_client *engine_client;
	void *client_state;
	void *engine_api;
	void *engine_vgui_internal;
	void *engine;
	void *server_plugin_helpers;

	// inputsystem
	i_input_stack_system *input_stack_system;
	i_input_system *input_system;

	// server
	void *server_game_dll;

	// tier0
	c_console *console;
	i_mem_alloc *mem_alloc;

	// vgui2
	i_scheme *scheme;
	i_scheme_manager *scheme_manager;
	void *vgui_input;

	// vguimatsurface
	c_font_manager *font_manager;
	i_surface *surface;

	// vstdlib
	i_command_line *command_line;
	i_cvar *cvar;
};
