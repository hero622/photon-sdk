#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#ifdef _WIN32
#	include <windows.h>
#	include <memoryapi.h>
#else
#	include <dlfcn.h>
#	include <sys/mman.h>
#	define MAX_PATH 4096
#endif

#include "platform.h"

namespace utils {
	namespace memory {
		struct module_info_t {
			char name[ MAX_PATH ];
			char path[ MAX_PATH ];
			std::uint8_t *addr;
			std::size_t size;
		};
		static std::vector<module_info_t> g_module_info;

		bool get_module_info( const char *module_name, module_info_t *module_info );
		std::uint8_t *pattern_scan( const char *module_name, const char *signature ) noexcept;

		template <std::size_t index, typename t, typename... args_t>
		__forceinline t call_virtual( void *name, args_t... args ) {
			using fn_t = t( __rescall * )( void *, args_t... );

			auto fn = ( *reinterpret_cast<fn_t **>( name ) )[ index ];
			return fn( name, args... );
		}

		template <std::size_t index>
		__forceinline std::uint8_t *get_virtual( void *name ) {
			return reinterpret_cast<std::uint8_t *>( ( *static_cast<int **>( name ) )[ index ] );
		}

		template <typename t>
		__forceinline t read( std::uint8_t *source ) {
			auto rel = *reinterpret_cast<int *>( source );
			return ( t ) ( source + rel + sizeof( rel ) );
		}

		template <typename t>
		__forceinline t get_sym_addr( void *module_handle, const char *sym ) {
#ifdef _WIN32
			return ( t ) GetProcAddress( ( HMODULE ) module_handle, sym );
#else
			return ( t ) dlsym( module_handle, sym );
#endif
		}

		__forceinline void *get_module_handle( const char *module_name ) {
			auto info = module_info_t( );
			if ( !get_module_info( module_name, &info ) )
				return nullptr;
#ifdef _WIN32
			return GetModuleHandleA( info.path );
#else
			return dlopen( info.path, RTLD_NOLOAD | RTLD_NOW );
#endif
		}
	}  // namespace memory
}  // namespace utils
