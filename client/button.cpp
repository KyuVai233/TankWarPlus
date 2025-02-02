#include "button.h"

void Button::on_input(const SDL_Event& event)
{
	if (!is_usable)	return;

	SDL_Point pos_cursor = { event.motion.x,event.motion.y };
	switch (event.type)
	{
	case SDL_MOUSEBUTTONUP:
		if (check_in_button(pos_cursor.x, pos_cursor.y))
		{
			if (event.button.button == SDL_BUTTON_LEFT && on_left_clicked)
				on_left_clicked();
			else if (event.button.button == SDL_BUTTON_RIGHT && on_right_clicked)
				on_right_clicked();
		}
		break;
	default:
		break;
	}
}

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