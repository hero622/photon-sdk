#pragma once

#include "convar.h"
#include "draw_call.h"
#include "events.h"
#include "hook.h"
#include "hud.h"
#include "input.h"
#include "interfaces.h"
#include "menu.h"
#include "render.h"
#include "source_sdk.h"
#include "utils.h"

namespace wh_api {
	class c_shared {
	public:
		c_portal2 *portal2;  // Contains game interfaces exposed by Wormhole.
		c_convar *cvars;     // Create ConVars and ConCommands.
		c_hook *hook;        // Hook virtual/inline functions.
		c_events *events;    // Post events to other plugins.
		c_huds *huds;        // Register HUDs and THUDs.
		c_render *render;    // Wrapper around Source's Surface interface.
		c_input *input;      // Wrapper around Source's InputSystem interface.
		c_menu *menu;        // Wormhole's own menu framework.
	};

	struct wh_mod_info_t {
		const char *name;     // Name of mod.
		const char *version;  // Version of mod using semantic versioning.
	};

	class i_wormhole_mod {
	public:
		virtual bool load( c_shared *wh ) = 0;         // Called on mod load, return if load was successful or not.
		virtual void unload( ) = 0;                    // Called on mod unload.
		virtual void on_event( const char *msg ) = 0;  // Callback for all events, `msg` contains event name.
		virtual wh_mod_info_t get_info( ) = 0;         // Return mod info here.
		virtual void paint_menu( ) = 0;                // Called every frame when mod's settings menu is shown.
	};
}  // namespace wh_api

extern wh_api::c_shared *wh;  // Global pointer for shared classes.

#define expose_wormhole_mod( class_t, name ) \
	dll_export class_t *create_mod( ) {         \
		return static_cast<class_t *>( &name );    \
	}
