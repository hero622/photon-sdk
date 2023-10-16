#pragma once

#include "source_sdk.h"

#include <unordered_map>

namespace wh_api {
	class i_hud {
	public:
		virtual void paint() = 0;
		virtual const char *get_name() = 0;
	};

	class i_thud {
	public:
		virtual const char *get_text() = 0;
		virtual const char *get_name() = 0;
	};
}  // namespace wh_api

struct hud_instance_t {
	sdk::vec2_t pos;
	sdk::vec2_t anchor;
	float scale;
};

struct thud_instance_t {
	sdk::vec2_t pos;
	sdk::vec2_t anchor;
	float scale;
	sdk::h_font font;
};

class c_huds {
private:
	virtual std::unordered_map<wh_api::i_hud *, hud_instance_t> &get_huds();
	virtual std::unordered_map<wh_api::i_thud *, thud_instance_t> &get_thuds();

public:
	virtual void reg(wh_api::i_hud *hud);
	virtual void reg(wh_api::i_thud *hud);
	virtual void unreg(wh_api::i_hud *hud);
	virtual void unreg(wh_api::i_thud *hud);

	void paint();  // this should not be called by mods
};