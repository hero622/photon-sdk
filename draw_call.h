#pragma once

#include "source_sdk.h"

#include <string>

// THIS WHOLE THING NEEDS A REWORK

namespace draw_call {
	struct draw_call_t {
		int x, y, w, h;

		virtual void call( ) = 0;
	};

	struct filled_rect : draw_call_t {
		sdk::color_t color;

		filled_rect( int x, int y, int w, int h, sdk::color_t color );

		virtual void call( );
	};
	struct outlined_rect : draw_call_t {
		sdk::color_t color;

		outlined_rect( int x, int y, int w, int h, sdk::color_t color );

		virtual void call( );
	};
	struct line : draw_call_t {
		sdk::color_t color;

		line( int x, int y, int w, int h, sdk::color_t color );

		virtual void call( );
	};
	struct text : draw_call_t {
		sdk::h_font font;
		sdk::color_t color;
		bool center;
		std::string txt;

		text( int x, int y, sdk::h_font font, sdk::color_t color, bool center, std::string txt );

		virtual void call( );
	};
	struct texture : draw_call_t {
		std::string path;
		sdk::color_t color;

		texture( int x, int y, int w, int h, std::string path, sdk::color_t color = sdk::color_t( 255, 255, 255, 255 ) );

		virtual void call( );
	};
}  // namespace draw_call
