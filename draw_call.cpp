#include "draw_call.h"

#include "wormhole.h"

draw_call::filled_rect::filled_rect( int x, int y, int w, int h, sdk::color_t color ) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->color = color;
}
void draw_call::filled_rect::call( ) {
	wh->render->draw_filled_rect( x, y, w, h, color );
}

draw_call::outlined_rect::outlined_rect( int x, int y, int w, int h, sdk::color_t color ) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->color = color;
}
void draw_call::outlined_rect::call( ) {
	wh->render->draw_outlined_rect( x, y, w, h, color );
}

draw_call::line::line( int x, int y, int w, int h, sdk::color_t color ) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->color = color;
}
void draw_call::line::call( ) {
	wh->render->draw_line( x, y, w, h, color );
}

draw_call::text::text( int x, int y, sdk::h_font font, sdk::color_t color, bool center, std::string txt ) {
	this->x = x;
	this->y = y;
	this->font = font;
	this->color = color;
	this->center = center;
	this->txt = txt;

	const auto text_size = wh->render->get_text_size( font, txt );
	this->w = text_size.x;
	this->h = text_size.y;
}
void draw_call::text::call( ) {
	wh->render->draw_text( x, y, font, color, center, txt );
}

draw_call::texture::texture( int x, int y, int w, int h, std::string path, sdk::color_t color ) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->path = path;
	this->color = color;
}
void draw_call::texture::call( ) {
	wh->render->draw_texture( x, y, w, h, path, color );
}
