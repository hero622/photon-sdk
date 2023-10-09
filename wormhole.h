#pragma once

#include "convar.h"
#include "events.h"
#include "hook.h"
#include "interfaces.h"
#include "source_sdk.h"
#include "utils.h"

namespace wh_api {
	class c_shared {
	public:
		c_portal2 *portal2;
		c_hook *hook;
		c_events *events;
	};

	class i_wormhole_mod {
	public:
		virtual bool load(c_shared *wh) = 0;
		virtual void unload() = 0;
		virtual void on_event(const char *msg) = 0;
	};
}  // namespace wh_api

extern wh_api::c_shared *wh;

#define expose_wormhole_mod(class_name)            \
	dll_export wh_api::i_wormhole_mod *create_mod() { \
		return new class_name();                         \
	}