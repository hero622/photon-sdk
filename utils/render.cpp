#include "render.h"

#include "../wormhole.h"

void utils::render::draw_filled_rect(int x, int y, int w, int h, sdk::color_t color) {
	wh->portal2->surface->draw_set_color(color.r, color.g, color.b, color.a);
	wh->portal2->surface->draw_filled_rect(x, y, x + w, y + h);
}

void utils::render::draw_outlined_rect(int x, int y, int w, int h, sdk::color_t color) {
	wh->portal2->surface->draw_set_color(color.r, color.g, color.b, color.a);
	wh->portal2->surface->draw_outlined_rect(x, y, x + w, y + h);
}

void utils::render::draw_line(int x, int y, int w, int h, sdk::color_t color) {
	wh->portal2->surface->draw_set_color(color.r, color.g, color.b, color.a);
	wh->portal2->surface->draw_line(x, y, x + w, y + h);
}

bool utils::render::create_font(sdk::h_font &font, const char *font_name, int size, bool bold, int flags) {
	font = wh->portal2->surface->create_font();
	return wh->portal2->surface->set_font_glyph_set(font, font_name, size, bold ? 800 : 0, 0, 0, flags);
}

void utils::render::text(int x, int y, sdk::h_font font, sdk::color_t color, bool center, std::string text) {
	int text_x = x;
	int text_y = y;
	int text_width, text_height;

	if (center) {
		wh->portal2->surface->get_text_size(font, std::wstring(text.begin(), text.end()).c_str(), text_width, text_height);
		text_x = x - text_width / 2;
	}

	wh->portal2->surface->draw_colored_text(font, text_x, text_y, color.r, color.g, color.b, color.a, text.c_str());
}

sdk::vec2_t utils::render::get_text_size(sdk::h_font font, std::string text) {
	int text_width, text_height;

	wh->portal2->surface->get_text_size(font, std::wstring(text.begin(), text.end()).c_str(), text_width, text_height);

	return sdk::vec2_t(text_width, text_height);
}

void utils::render::draw_texture(int x, int y, int w, int h, std::string texture, sdk::color_t color) {
	int id = wh->portal2->surface->draw_get_texture_id(texture.c_str());
	if (!id) {
		id = wh->portal2->surface->create_new_texture_id(true);
		wh->portal2->surface->draw_set_texture_file(id, texture.c_str(), false, true);
	}
	wh->portal2->surface->draw_set_texture(id);
	wh->portal2->surface->draw_set_color(color.r, color.g, color.b, color.a);
	wh->portal2->surface->draw_textured_rect(x, y, x + w, y + h);
}

sdk::vec2_t utils::render::get_screen_size() {
	int w, h;

	wh->portal2->surface->get_screen_size(w, h);

	return sdk::vec2_t(w, h);
}