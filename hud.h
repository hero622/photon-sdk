#pragma once

#include "source_sdk.h"
#include "utils.h"

namespace wh_api {
	class hud_t {
	public:
		sdk::vec2_t pos;
		sdk::vec2_t anchor;
		float scale;
		sdk::vec2_t bounds;

	protected:
		__forceinline void update_bounds(int x, int y) {
			if (bounds.x < x) bounds.x = x;
			if (bounds.y < y) bounds.y = y;
		}

		__forceinline void reset_bounds() {
			bounds.x = 0;
			bounds.y = 0;
		}
	};

	class i_hud : public hud_t {
	public:
		virtual void paint() = 0;
		virtual const char *get_name() = 0;
	};

	class i_thud : public hud_t {
	public:
		sdk::h_font font;
		const char *format = "{name}: {value}";

		virtual const char *get_text() = 0;
		virtual const char *get_name() = 0;

	protected:
		std::string formatted_text;

		void format_text(const char *value) {
			auto text = std::string(format);

			utils::string::replace(text, "{name}", std::string(get_name()));
			utils::string::replace(text, "{value}", std::string(value));

			formatted_text = text;
		}
	};
}  // namespace wh_api

class c_huds {
public:
	virtual void reg(wh_api::i_hud *hud);
	virtual void reg(wh_api::i_thud *thud);
	virtual void unreg(wh_api::i_hud *hud);
	virtual void unreg(wh_api::i_thud *thud);
};

#define filled_rect(_x, _y, w, h, color) \
	update_bounds(_x + w, _y + h);          \
	wh->render->draw_filled_rect(wh->render->to_screen(pos).x + _x, wh->render->to_screen(pos).y + _y, w, h, color);

#define outlined_rect(_x, _y, w, h, color) \
	update_bounds(_x + w, _y + h);            \
	wh->render->draw_outlined_rect(wh->render->to_screen(pos).x + _x, wh->render->to_screen(pos).y + _y, w, h, color);

#define line(_x, _y, w, h, color) \
	update_bounds(_x + w, _y + h);   \
	wh->render->draw_line(wh->render->to_screen(pos).x + _x, wh->render->to_screen(pos).y + _y, w, h, color);

#define init_font(font, font_name, size, bold, flags) \
	wh->render->create_font(font, font_name, size, bold, flags);

#define text(_x, _y, font, color, center, text)                                                                           \
	{                                                                                                                        \
		const auto size = wh->render->get_text_size(font, text);                                                                \
		update_bounds(_x + size.x, _y + size.y);                                                                                \
		wh->render->draw_text(wh->render->to_screen(pos).x + _x, wh->render->to_screen(pos).y + _y, font, color, center, text); \
	}

#define text_size(font, txt) \
	wh->render->get_text_size(font, txt);

#define texture(_x, _y, w, h, texture, color) \
	update_bounds(_x + w, _y + h);               \
	wh->render->draw_texture(wh->render->to_screen(pos).x + _x, wh->render->to_screen(pos).y + _y, w, h, texture, color);

#define screen_size() \
	wh->render->get_screen_size();

#define thud_text(txt)                                      \
	{                                                          \
		format_text(txt);                                         \
		bounds = wh->render->get_text_size(font, formatted_text); \
		return formatted_text.c_str();                            \
	}