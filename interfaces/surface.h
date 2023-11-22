#pragma once

#include "../source_sdk.h"
#include "../utils.h"

class i_surface {
public:
	void draw_set_color( int r, int g, int b, int a ) {
		return utils::memory::call_virtual<void>( offsets::draw_set_color, this, r, g, b, a );
	}
	void draw_filled_rect( int x0, int y0, int x1, int y1 ) {
		return utils::memory::call_virtual<void>( offsets::draw_filled_rect, this, x0, y0, x1, y1 );
	}
	void draw_outlined_rect( int x0, int y0, int x1, int y1 ) {
		return utils::memory::call_virtual<void>( offsets::draw_outlined_rect, this, x0, y0, x1, y1 );
	}
	void draw_line( int x0, int y0, int x1, int y1 ) {
		return utils::memory::call_virtual<void>( offsets::draw_line, this, x0, y0, x1, y1 );
	}
	int draw_get_texture_id( const char *filename ) {
		return utils::memory::call_virtual<int>( offsets::draw_get_texture_id, this, filename );
	}
	void draw_set_texture_file( int id, const char *filename, int hardware_filter, bool force_reload ) {
		return utils::memory::call_virtual<void>( offsets::draw_set_texture_file, this, id, filename, hardware_filter, force_reload );
	}
	void draw_set_texture_rgba( int id, const unsigned char *rgba, int wide, int tall ) {
		return utils::memory::call_virtual<void>( offsets::draw_set_texture_rgba, this, id, rgba, wide, tall );
	}
	void draw_set_texture( int id ) {
		return utils::memory::call_virtual<void>( offsets::draw_set_texture, this, id );
	}
	void draw_get_texture_size( int id, int &wide, int &tall ) {
		return utils::memory::call_virtual<void>( offsets::draw_get_texture_size, this, id, &wide, &tall );
	}
	void draw_textured_rect( int x0, int y0, int x1, int y1 ) {
		return utils::memory::call_virtual<void>( offsets::draw_textured_rect, this, x0, y0, x1, y1 );
	}
	bool is_texture_id_valid( int id ) {
		return utils::memory::call_virtual<bool>( offsets::is_texture_id_valid, this, id );
	}
	int create_new_texture_id( bool procedural = false ) {
		return utils::memory::call_virtual<int>( offsets::create_new_texture_id, this, procedural );
	}
	void get_screen_size( int &wide, int &tall ) {
		return utils::memory::call_virtual<void>( offsets::get_screen_size, this, &wide, &tall );
	}
	void unlock_cursor( ) {
		return utils::memory::call_virtual<void>( offsets::unlock_cursor, this );
	}
	sdk::h_font create_font( ) {
		return utils::memory::call_virtual<sdk::h_font>( offsets::create_font, this );
	}
	bool set_font_glyph_set( sdk::h_font font, const char *font_name, int tall, int weight, int blur, int scanlines, int flags, int range_min = 0, int range_max = 0 ) {
		return utils::memory::call_virtual<bool>( offsets::set_font_glyph_set, this, font, font_name, tall, weight, blur, scanlines, flags, range_min, range_max );
	}
	void get_text_size( sdk::h_font font, const wchar_t *text, int &wide, int &tall ) {
		return utils::memory::call_virtual<void>( offsets::get_text_size, this, font, text, &wide, &tall );
	}
	void get_clip_rect( int &x0, int &y0, int &x1, int &y1 ) {
		return utils::memory::call_virtual<void>( offsets::get_clip_rect, this, &x0, &y0, &x1, &y1 );
	}
	void set_clip_rect( int x0, int y0, int x1, int y1 ) {
		return utils::memory::call_virtual<void>( offsets::set_clip_rect, this, x0, y0, x1, y1 );
	}
	void draw_colored_text( sdk::h_font font, int x, int y, int r, int g, int b, int a, const char *text ) {
		// !!! this is __cdecl because it has varargs
		using fn_t = void( __cdecl * )( void *, sdk::h_font, int, int, int, int, int, int, const char * );
		return ( *reinterpret_cast<fn_t **>( this ) )[ offsets::draw_colored_text ]( this, font, x, y, r, g, b, a, text );
	}
	void start_drawing( ) {
		auto paint_traverse_ex = utils::memory::get_virtual( this, offsets::paint_traverse_ex );
		return utils::memory::read<void( __rescall * )( void * )>( paint_traverse_ex + offsets::start_drawing )( this );
	}
	void finish_drawing( ) {
		auto paint_traverse_ex = utils::memory::get_virtual( this, offsets::paint_traverse_ex );
		return utils::memory::read<void( __rescall * )( )>( paint_traverse_ex + offsets::finish_drawing )( );
	}

private:
	char pad_0000[ 0x280 ];  // 0x0000
public:
	bool enable_clipping;  // 0x0280
};
