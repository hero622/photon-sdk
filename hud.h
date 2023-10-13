#pragma once

#include "source_sdk.h"

#include <vector>

namespace wh_api {
	class c_hud {
	public:
		sdk::vec2_t anchor;
		sdk::vec2_t pos;
		float size;

		virtual void paint() = 0;
	};

	class c_thud {
	public:
		virtual const char *get_text() = 0;
	};
}  // namespace wh_api

class c_huds {
private:
	static std::vector<wh_api::c_hud *> &get_list();

public:
	virtual void reg(wh_api::c_hud *hud);
	virtual void unreg(wh_api::c_hud *hud);

	void paint_all();
};