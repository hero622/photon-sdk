#pragma once

#include "../source_sdk.h"

namespace utils {
	namespace render {
		void draw_filled_rect(int x0, int y0, int x1, int y1, sdk::color_t color);
		void draw_outlined_rect(int x0, int y0, int x1, int y1, sdk::color_t color);
		void draw_line(int x0, int y0, int x1, int y1, sdk::color_t color);
		void create_font(sdk::h_font &font, const char *font_name, int size, bool bold, int flags);
		template <typename... args_t>
		void text(int x, int y, sdk::h_font font, sdk::color_t color, bool center, const char *fmt, args_t... args);
		template <typename... args_t>
		sdk::vec2_t get_text_size(sdk::h_font font, const char *fmt, args_t... args);
	}  // namespace render
}  // namespace utils