#pragma once

#include "../source_sdk.h"

#include <string>

namespace utils {
	namespace render {
		void draw_filled_rect(int x, int y, int w, int h, sdk::color_t color);
		void draw_outlined_rect(int x, int y, int w, int h, sdk::color_t color);
		void draw_line(int x, int y, int w, int h, sdk::color_t color);
		bool create_font(sdk::h_font &font, const char *font_name, int size, bool bold, int flags);
		void text(int x, int y, sdk::h_font font, sdk::color_t color, bool center, std::string text);
		sdk::vec2_t get_text_size(sdk::h_font font, std::string text);
		void draw_texture(int x, int y, int w, int h, std::string texture, sdk::color_t color = sdk::color_t(255, 255, 255, 255));
		sdk::vec2_t get_screen_size();
	}  // namespace render
}  // namespace utils