#include "button.h"

void Button::on_update(float delta)
{
	switch (status)
	{
	case Button::ButtonStatus::Idle:
		current_texture = texture_idle;
		break;
	case Button::ButtonStatus::Covered:
		current_texture = texture_covered;
		break;
	case Button::ButtonStatus::ClickedLeft:
		current_texture = texture_clicked;
		Mix_PlayChannel(-1, music_clicked, 0);
		take_on_left_clicked();
		break;
	case Button::ButtonStatus::ClickedRight:
		current_texture = texture_clicked;
		Mix_PlayChannel(-1, music_clicked, 0);
		take_on_right_clicked();
		break;
	default:
		break;
	}
}

void Button::on_render(SDL_Renderer* renderer)
{
	SDL_Rect rect_src;
	rect_src.x = position_src.x, rect_src.y = position_src.y;
	rect_src.w = size_src.x, rect_src.h = size_src.y;

	SDL_Rect rect_dst;
	rect_dst.x = position_dst.x, rect_dst.y = position_dst.y;
	rect_dst.w = size_dst.x, rect_dst.h = size_dst.y;

	draw(renderer, current_texture, &rect_src, &rect_dst);
}