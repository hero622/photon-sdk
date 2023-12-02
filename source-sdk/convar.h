#pragma once

#include "utlvector.h"

namespace sdk {
	class c_command {
	public:
		int arg_c( ) const { return argc; };
		const char *operator[]( int index ) const { return arg( index ); };
		const char *arg( int index ) const { return argv[ index ]; };

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
	typedef int ( *fn_command_completion_callback_t )( const char *partial, char commands[ 64 ][ 64 ] );

	struct con_command_base {
		void *vtable;
		con_command_base *next;
		bool registered;
		const char *name;
		const char *help_string;
		int flags;
	};

	struct con_command : con_command_base {
		union {
			void *fn_command_callback_v1;
			fn_command_callback_t fn_command_callback;
			void *command_callback;
		};
		union {
			fn_command_completion_callback_t fn_completion_callback;
			void *command_completion_callback;
		};
		bool has_completion_callback : 1;
		bool using_new_command_callback : 1;
		bool using_command_callback_interface : 1;
	};

	class i_con_var {
	public:
		virtual void set_value( const char *value ) = 0;
		virtual void set_value( float value ) = 0;
		virtual void set_value( int value ) = 0;
		virtual const char *get_name( void ) const = 0;
		virtual bool is_flag_set( int flag ) const = 0;
	};

	typedef void ( *fn_change_callback_t )( i_con_var *var, const char *p_old_value, float fl_old_value );

	struct con_var : con_command_base {
		void *vtable_convar;
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
		fn_change_callback_t fn_change_callback;
	};
}  // namespace sdk
