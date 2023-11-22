#pragma once

class c_events {
public:
	virtual void post( void *sender, const char *msg );  // Post events to all other mods, pass in the pointer to your i_wormhole_mod, message/event name as a C string.
};
