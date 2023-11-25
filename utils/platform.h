#pragma once

#ifndef _WIN32
#	include <unistd.h>
#endif

#ifdef _WIN32
#	define module( name ) name ".dll"

#	define __rescall __thiscall

#	define dll_export extern "C" __declspec( dllexport )

#	define decl_hk( t, name, ... )                         \
		inline void *name##_hk;                                \
		inline t( __rescall *name )( void *ecx, __VA_ARGS__ ); \
		t __fastcall name##_hk_fn( void *ecx, int edx, __VA_ARGS__ )

#	define hk_fn( t, name, ... ) \
		t __fastcall name##_hk_fn( void *ecx, int edx, __VA_ARGS__ )

#	define os( win, linux ) win
#else
#	define module( name ) name ".so"

#	define __rescall __attribute__( ( __cdecl__ ) )
#	define __cdecl __attribute__( ( __cdecl__ ) )
#	define __fastcall __attribute__( ( __fastcall__ ) )

#	define __forceinline inline __attribute__( ( always_inline ) )

#	define dll_export extern "C" __attribute__( ( visibility( "default" ) ) )

#	define decl_hk( t, name, ... )                           \
		inline void *name##_hk;                                  \
		inline t( __rescall *name )( void *ecx, ##__VA_ARGS__ ); \
		t __rescall name##_hk_fn( void *ecx, ##__VA_ARGS__ )

#	define hk_fn( t, name, ... ) \
		t __rescall name##_hk_fn( void *ecx, ##__VA_ARGS__ )

#	define os( win, linux ) linux
#endif
