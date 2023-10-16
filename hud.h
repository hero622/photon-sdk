#pragma once

#include "source_sdk.h"

#include <vector>

namespace wh_api {
	class c_hud {
	public:
		sdk::vec2_t anchor;
		sdk::vec2_t pos;
		float size;

		const char *name;  // set this

		virtual void paint() = 0;
	};

	class c_thud {
	public:
		sdk::vec2_t anchor;
		sdk::vec2_t pos;
		float size;
		sdk::h_font font;

		const char *name;  // set this

		virtual const char *get_text() = 0;
	};
}  // namespace wh_api

class c_huds {
private:
	virtual std::vector<wh_api::c_hud *> &get_huds();
	virtual std::vector<wh_api::c_thud *> &get_thuds();

public:
	virtual void reg(wh_api::c_hud *hud);
	virtual void reg(wh_api::c_thud *hud);
	virtual void unreg(wh_api::c_hud *hud);
	virtual void unreg(wh_api::c_thud *hud);

	void paint();  // this should not be called by mods
};