#pragma once

#include "../source_sdk.h"
#include "../utils.h"

class i_surface {
public:
	void draw_set_color(int r, int g, int b, int a) {
		return utils::memory::call_virtual<void>(offsets::draw_set_color, this, r, g, b, a);
	}
	void draw_filled_rect(int x0, int y0, int x1, int y1) {
		return utils::memory::call_virtual<void>(offsets::draw_filled_rect, this, x0, y0, x1, y1);
	}
	void draw_outlined_rect(int x0, int y0, int x1, int y1) {
		return utils::memory::call_virtual<void>(offsets::draw_outlined_rect, this, x0, y0, x1, y1);
	}
	void draw_line(int x0, int y0, int x1, int y1) {
		return utils::memory::call_virtual<void>(offsets::draw_line, this, x0, y0, x1, y1);
	}
	void draw_set_text_font(sdk::h_font font) {
		return utils::memory::call_virtual<void>(offsets::draw_set_text_font, this, font);
	}
	void draw_set_text_color(sdk::color_t col) {
		return utils::memory::call_virtual<void>(offsets::draw_set_text_color, this, col);
	}
	void draw_set_texture_file(int id, const char *filename, int hardware_filter, bool force_reload) {
		return utils::memory::call_virtual<void>(offsets::draw_set_texture_file, this, id, filename, hardware_filter, force_reload);
	}
	void draw_set_texture_rgba(int id, const unsigned char *rgba, int wide, int tall) {
		return utils::memory::call_virtual<void>(offsets::draw_set_texture_rgba, this, id, rgba, wide, tall);
	}
	void draw_set_texture(int id) {
		return utils::memory::call_virtual<void>(offsets::draw_set_texture, this, id);
	}
	void draw_get_texture_size(int id, int &wide, int &tall) {
		return utils::memory::call_virtual<void>(offsets::draw_get_texture_size, this, id, wide, tall);
	}
	void draw_textured_rect(int x0, int y0, int x1, int y1) {
		return utils::memory::call_virtual<void>(offsets::draw_textured_rect, this, x0, y0, x1, y1);
	}
	bool is_texture_id_valid(int id) {
		return utils::memory::call_virtual<bool>(offsets::is_texture_id_valid, this, id);
	}
	int create_new_texture_id(bool procedural) {
		return utils::memory::call_virtual<int>(offsets::create_new_texture_id, this, procedural);
	}
	int get_font_tall(sdk::h_font font) {
		return utils::memory::call_virtual<int>(offsets::get_font_tall, this, font);
	}
	int get_text_size(sdk::h_font font, const wchar_t *text, int &wide, int &tall) {
		return utils::memory::call_virtual<int>(offsets::get_text_size, this, font, text, wide, tall);
	}
	void start_drawing() {
		auto paint_traverse_ex = utils::memory::get_virtual(this, offsets::paint_traverse_ex);
		return utils::memory::read<void(__rescall *)(void *)>(paint_traverse_ex + offsets::start_drawing)(this);
	}
	void finish_drawing() {
		auto paint_traverse_ex = utils::memory::get_virtual(this, offsets::paint_traverse_ex);
		return utils::memory::read<void(__rescall *)()>(paint_traverse_ex + offsets::finish_drawing)();
	}
};