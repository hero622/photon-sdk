#pragma once

#include "source_sdk.h"

#include <string>

class c_render {
public:
	virtual void draw_filled_rect( int x, int y, int w, int h, sdk::color_t color );
	virtual void draw_outlined_rect( int x, int y, int w, int h, sdk::color_t color );
	virtual void draw_line( int x, int y, int w, int h, sdk::color_t color );
	virtual bool create_font( sdk::h_font &font, const char *font_name, int size, bool bold, int flags );
	virtual void destruct_font( sdk::h_font font );
	virtual void draw_text( int x, int y, sdk::h_font font, sdk::color_t color, bool center, const char *text );
	virtual sdk::vec2_t get_text_size( sdk::h_font font, const char *text );
	virtual void draw_texture( int x, int y, int w, int h, const char *texture, sdk::color_t color = sdk::color_t( 255, 255, 255, 255 ) );
	virtual sdk::vec2_t get_screen_size( );
	virtual sdk::h_font get_font( unsigned long id );
	virtual sdk::vec2_t normalize( sdk::vec2_t vec );  // Translate screen X, Y pixel position to a normal value between (0, 1).
	virtual sdk::vec2_t to_screen( sdk::vec2_t vec );  // Translate X, Y position between (0, 1) to a position on the screen.
};
