#pragma once

#include "source_sdk.h"

class c_menu {
public:
	virtual bool button( sdk::vec2_t size, const char *label );
	virtual void checkbox( bool &val, const char *label );
	virtual void slider( int &val, int min, int max, const char *label );
	virtual void sliderf( float &val, float min, float max, const char *label );
	virtual void colorpicker( sdk::color_t &val, const char *label );
	virtual void combo( int &val, const char **items, const char *label );
	virtual void multicombo( int &val, const char **items, const char *label );
};
