#pragma once

#include "draw_call.h"
#include "source_sdk.h"
#include "utils.h"

#include <vector>

namespace wh_api {
	class hud_t {
	public:
		sdk::vec2_t pos;
		sdk::vec2_t anchor;
		float scale;
		sdk::vec2_t bounds;
	};

	class i_hud : public hud_t {
	public:
		std::vector<draw_call::draw_call_t *> draw_calls;

		virtual void paint() = 0;
		virtual const char *get_name() = 0;

	protected:
		__forceinline void draw_filled_rect(int x, int y, int w, int h, sdk::color_t color) {
			draw_calls.push_back(new draw_call::filled_rect(x, y, w, h, color));
		}
		__forceinline void draw_outlined_rect(int x, int y, int w, int h, sdk::color_t color) {
			draw_calls.push_back(new draw_call::outlined_rect(x, y, w, h, color));
		}
		__forceinline void draw_line(int x, int y, int w, int h, sdk::color_t color) {
			draw_calls.push_back(new draw_call::line(x, y, w, h, color));
		}
		__forceinline void draw_text(int x, int y, sdk::h_font font, sdk::color_t color, bool center, std::string text) {
			draw_calls.push_back(new draw_call::text(x, y, font, color, center, text));
		}
		__forceinline void draw_texture(int x, int y, int w, int h, std::string texture, sdk::color_t color = sdk::color_t(255, 255, 255, 255)) {
			draw_calls.push_back(new draw_call::texture(x, y, w, h, texture, color));
		}
	};

	class i_thud : public hud_t {
	public:
		unsigned long font;
		const char *format = "{name}: {value}";

		virtual const char *get_text() = 0;
		virtual const char *get_name() = 0;
	};
}  // namespace wh_api

class c_huds {
public:
	virtual void reg(wh_api::i_hud *hud);
	virtual void reg(wh_api::i_thud *thud);
	virtual void unreg(wh_api::i_hud *hud);
	virtual void unreg(wh_api::i_thud *thud);
};