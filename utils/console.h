#pragma once

#include <iostream>

namespace utils {
	namespace console {
		void alloc( );
		void free( );

		template <typename... args_t>
		void log( const char *fmt, const args_t &...args ) {
			printf( fmt, args... );
		}
	}  // namespace console
}  // namespace utils
