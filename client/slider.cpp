#include "slider.h"

void Slider::on_input(const SDL_Event& event)
{
	SDL_Point pos_cursor = { event.motion.x,event.motion.y };
	switch (event.type)
	{
		{
		case SDL_MOUSEBUTTONDOWN:
			SDL_Point size_slider;
			SDL_QueryTexture(tex_covered, NULL, NULL, &size_slider.x, &size_slider.y);
			SDL_Point move_distance =
			{ pos_cursor_last.x - pos_cursor.x, pos_cursor_last.y - pos_cursor.y };
			if (move_distance.x != 0 || move_distance.y != 0)
			{
				val = is_vertical ? move_distance.y / size_slider.y : move_distance.x / size_slider.x;
				is_vertical ? pos_button_slider.x += move_distance.x : pos_button_slider.y += move_distance.y;
				if (pos_button_slider.x < pos_slider.x)	pos_button_slider.x = pos_slider.x;
				if (pos_button_slider.x > pos_slider.x + size_slider.x)	pos_button_slider.x = pos_slider.x + size_slider.x;
				if (pos_button_slider.y < pos_slider.y)	pos_button_slider.y = pos_slider.y;
				if (pos_button_slider.y > pos_slider.y + size_slider.y)	pos_button_slider.y = pos_slider.y + size_slider.y;
				pos_cursor_last = pos_cursor;
			}
			break;
		}
	default:
		break;
	}
}

void Slider::on_render(SDL_Renderer* renderer)
{
	SDL_Point size_covered;
	SDL_QueryTexture(tex_covered, NULL, NULL, &size_covered.x, &size_covered.y);
	SDL_Point size_idle;
	SDL_QueryTexture(tex_idle, NULL, NULL, &size_idle.x, &size_idle.y);
	SDL_Rect rect_covered_src, rect_idle_src, rect_covered_dst, rect_idle_dst;
	if (is_vertical)
	{
		rect_covered_src =
		{
			0,0,
			size_covered.x,(int)pos_button_slider.y
		};
		rect_idle_src =
		{
			0,(int)pos_button_slider.y,
			size_idle.x,(int)(size_idle.y - pos_button_slider.y)
		};
		rect_covered_dst =
		{
			(int)pos_slider.x,(int)pos_slider.y,
			size_covered.x,(int)(pos_button_slider.y - pos_slider.y)
		};
		rect_idle_dst =
		{
			(int)pos_button_slider.x,(int)pos_button_slider.y,
			size_idle.x,(int)(size_idle.y - pos_button_slider.y)
		};
	}
	else
	{
		SDL_Rect rect_covered_src =
		{
			0,0,
			(int)pos_button_slider.x,(int)size_covered.y
		};
		SDL_Rect rect_idle_src =
		{
			pos_button_slider.x ,0,
			(int)(size_idle.x - pos_button_slider.x),(int)size_idle.y
		};
		SDL_Rect rect_covered_dst =
		{
			pos_slider.x,pos_slider.y,
			(int)(pos_button_slider.x - pos_slider.x),(int)size_covered.y
		};
		SDL_Rect rect_idle_dst =
		{
			(int)pos_button_slider.x,(int)pos_button_slider.y,
			(int)(size_idle.x - pos_button_slider.x),(int)size_idle.y
		};
	}
	draw(renderer, tex_covered, &rect_covered_src, &rect_covered_dst);
	draw(renderer, tex_idle, &rect_idle_src, &rect_idle_dst);
	SDL_Point size_button_slider;
	SDL_QueryTexture(tex_button_slider, NULL, NULL, &size_button_slider.x, &size_button_slider.y);
	SDL_Rect rect_button_slider_src =
	{ 0,0,size_button_slider.x,size_button_slider.y };
	SDL_Rect rect_button_slider_dst =
	{ pos_button_slider.x,pos_button_slider.y,size_button_slider.x,size_button_slider.y };
	if (tex_button_slider)
		draw(renderer, tex_button_slider, &rect_button_slider_src, &rect_button_slider_dst);
}