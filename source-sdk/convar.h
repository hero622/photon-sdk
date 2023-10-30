#pragma once

#include "utlvector.h"

namespace sdk {
	class c_command {
	public:
		int arg_c( ) const { return argc; };
		const char *operator[]( int index ) const { return arg( index ); };
		const char *arg( int index ) const { return this->argv[ index ]; };

		enum {
			command_max_argc = 64,
			command_max_length = 512,
		};
		int argc;
		int argv0_size;
		char arg_s_buffer[ command_max_length ];
		char argv_buffer[ command_max_length ];
		const char *argv[ command_max_argc ];
	};

	typedef void ( *fn_command_callback_t )( const c_command &command );
	typedef int ( *fn_command_completion_callback )( const char *partial, char commands[ 64 ][ 64 ] );

	struct con_command_base {
		con_command_base( const char *name, const char *help_string = 0, int flags = 0 )
			: next( nullptr )
			, registered( false )
			, name( name )
			, help_string( help_string )
			, flags( flags ) {
		}
		virtual void _dtor( ) { };
#ifndef _WIN32
		virtual void _dtor1( ) { };
#endif
		virtual bool is_enabled( ) const { return false; };

		con_command_base *next;
		bool registered;
		const char *name;
		const char *help_string;
		int flags;
	};

	struct con_command : con_command_base {
		con_command( const char *name, fn_command_callback_t callback, const char *help_string = 0, int flags = 0, fn_command_completion_callback completion_func = 0 )
			: con_command_base( name, help_string, flags )
			, fn_command_callback( callback )
			, fn_completion_callback( completion_func )
			, has_completion_callback( completion_func != nullptr )
			, using_new_command_callback( true )
			, using_command_callback_interface( false ) {
		}

		union {
			void *fn_command_callback_v1;
			fn_command_callback_t fn_command_callback;
			void *command_callback;
		};
		union {
			fn_command_completion_callback fn_completion_callback;
			void *command_completion_callback;
		};
		bool has_completion_callback : 1;
		bool using_new_command_callback : 1;
		bool using_command_callback_interface : 1;
	};

	class i_con_var {
	public:
		virtual void set_value( const char *p_value ) = 0;
		virtual void set_value( float fl_value ) = 0;
		virtual void set_value( int n_value ) = 0;
		virtual const char *get_name( void ) const = 0;
		virtual bool is_flag_set( int n_flag ) const = 0;
	};

	typedef void ( *fn_change_callback_t )( i_con_var *var, const char *p_old_value, float fl_old_value );

	struct con_var : con_command_base {
		con_var( const char *name, const char *default_value, int flags, const char *help_string, bool b_min, float f_min, bool b_max, float f_max )
			: con_command_base( name, help_string, flags )
			, vtable( nullptr )
			, parent( nullptr )
			, default_value( default_value )
			, string( nullptr )
			, string_length( 0 )
			, f_value( 0.0f )
			, n_value( 0 )
			, has_min( b_min )
			, min_val( f_min )
			, has_max( b_max )
			, max_val( f_max )
			, fn_change_callback( ) {
		}

		void *vtable;
		con_var *parent;
		const char *default_value;
		char *string;
		int string_length;
		float f_value;
		int n_value;
		bool has_min;
		float min_val;
		bool has_max;
		float max_val;
		utl_vector<fn_change_callback_t> fn_change_callback;
	};
}  // namespace sdk
