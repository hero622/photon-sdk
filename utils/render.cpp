#include "render.h"

#include "../wormhole.h"

#include <string>

void utils::render::draw_filled_rect(int x0, int y0, int x1, int y1, sdk::color_t color) {
	wh->portal2->surface->draw_set_color(color.r, color.g, color.b, color.a);
	wh->portal2->surface->draw_filled_rect(x0, y0, x1, y1);
}

void utils::render::draw_outlined_rect(int x0, int y0, int x1, int y1, sdk::color_t color) {
	wh->portal2->surface->draw_set_color(color.r, color.g, color.b, color.a);
	wh->portal2->surface->draw_outlined_rect(x0, y0, x1, y1);
}

void utils::render::draw_line(int x0, int y0, int x1, int y1, sdk::color_t color) {
	wh->portal2->surface->draw_set_color(color.r, color.g, color.b, color.a);
	wh->portal2->surface->draw_line(x0, y0, x1, y1);
}

bool utils::render::create_font(sdk::h_font &font, const char *font_name, int size, bool bold, int flags) {
	font = wh->portal2->surface->create_font();
	return wh->portal2->surface->set_font_glyph_set(font, font_name, size, bold ? 800 : 0, 0, 0, flags);
}

void utils::render::text(int x, int y, sdk::h_font font, sdk::color_t color, bool center, const char *text) {
	int text_x = x;
	int text_y = y;
	int text_width, text_height;

	if (center) {
		wchar_t wtext[128];
		mbstowcs_s(nullptr, wtext, text, 128);

		wh->portal2->surface->get_text_size(font, wtext, text_width, text_height);
		text_x = x - text_width / 2;
	}

	wh->portal2->surface->draw_colored_text(font, text_x, text_y, color.r, color.g, color.b, color.a, text);
}

sdk::vec2_t utils::render::get_text_size(sdk::h_font font, const char *text) {
	int text_width, text_height;

	wchar_t wtext[128];
	mbstowcs_s(nullptr, wtext, text, 128);

	wh->portal2->surface->get_text_size(font, wtext, text_width, text_height);

	return sdk::vec2_t(text_width, text_height);
}