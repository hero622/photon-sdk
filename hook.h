#pragma once

#include "ccon.h"
#include "utils.h"

class c_hook {
public:
	virtual bool create_hook( void *src, void *dst, void *&hook, void **orig );
	virtual bool remove_hook( void *hook );
	virtual bool enable_hook( void *hook );
	virtual bool disable_hook( void *hook );
};

#define hk_virtual( vtable, name, off ) \
	photon->hook->create_hook( reinterpret_cast<void *>( utils::memory::get_virtual<off>( vtable ) ), reinterpret_cast<void *>( name##_hk_fn ), name##_hk, reinterpret_cast<void **>( &name ) )

#define hk_inline( name, addr ) \
	photon->hook->create_hook( reinterpret_cast<void *>( addr ), reinterpret_cast<void *>( name##_hk_fn ), name##_hk, reinterpret_cast<void **>( &name ) )

#define unhk( name ) \
	photon->hook->remove_hook( name##_hk )

#define hk_cmd( name ) \
	photon->con->hook_cmd( #name, name##_hk, name )

#define unhk_cmd( name ) \
	photon->con->unhook_cmd( #name, name )
