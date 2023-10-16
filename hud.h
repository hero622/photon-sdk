#pragma once

#include "source_sdk.h"

#include <unordered_map>

namespace wh_api {
	class c_hud {
	public:
		const char *name;

		virtual void paint() = 0;
	};

	class c_thud {
	public:
		const char *name;

		virtual const char *get_text() = 0;
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
	virtual std::unordered_map<wh_api::c_hud *, hud_instance_t> &get_huds();
	virtual std::unordered_map<wh_api::c_thud *, thud_instance_t> &get_thuds();

public:
	virtual void reg(wh_api::c_hud *hud);
	virtual void reg(wh_api::c_thud *hud);
	virtual void unreg(wh_api::c_hud *hud);
	virtual void unreg(wh_api::c_thud *hud);

	void paint();  // this should not be called by mods
};