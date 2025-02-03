#include "button.h"

void Button::on_render(SDL_Renderer* renderer)
{
	SDL_Rect rect_src;
	rect_src.x = 0, rect_src.y = 0;
	rect_src.w = size.x, rect_src.h = size.y;

	SDL_Rect rect_dst;
	rect_dst.x = position.x, rect_dst.y = position.y;
	rect_dst.w = size.x, rect_dst.h = size.x;

	draw(renderer, texture, &rect_src, &rect_dst);
}