#include "slider.h"

void Slider::on_input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION: // 添加鼠标移动事件处理
		pos_cursor = { event.motion.x, event.motion.y };
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (is_in_button_slider(pos_cursor.x, pos_cursor.y))
			is_clicked_mouse_left_and_in_button = true;
		break;
	case SDL_MOUSEBUTTONUP:
		is_clicked_mouse_left_and_in_button = false;
		if (is_open_ban_slider && tex_ban_slider)
		{
			SDL_Point size_text;
			SDL_QueryTexture(tex_ban_slider, NULL, NULL, &size_text.x, &size_text.y);
			SDL_Rect rect = { pos_slider.x + text_spacing.x,pos_slider.y + text_spacing.y,size_text.x,size_text.y };
			if ((pos_cursor.x >= rect.x && pos_cursor.x <= rect.x + rect.w) &&
				(pos_cursor.y >= rect.y && pos_cursor.y <= rect.y + rect.h))
			{
				is_ban_slider = !is_ban_slider;
			}
		}
		break;
	default:
		break;
	}
}

void Slider::on_update(float delta)
{
	SDL_Point size_slider;
	SDL_QueryTexture(tex_covered, NULL, NULL, &size_slider.x, &size_slider.y);
	if (is_clicked_mouse_left_and_in_button && !is_ban_slider)
	{
		is_vertical ? pos_button_slider.y = pos_cursor.y : pos_button_slider.x = pos_cursor.x;
		if (pos_button_slider.x < pos_slider.x)	pos_button_slider.x = pos_slider.x;
		if (pos_button_slider.x > pos_slider.x + size_slider.x)	pos_button_slider.x = pos_slider.x + size_slider.x;
		if (pos_button_slider.y < pos_slider.y)	pos_button_slider.y = pos_slider.y;
		if (pos_button_slider.y > pos_slider.y + size_slider.y)	pos_button_slider.y = pos_slider.y + size_slider.y;
	}

	val = is_vertical ? (pos_button_slider.y - pos_slider.y) / size_slider.y : (pos_button_slider.x - pos_slider.x) / size_slider.x;
	if (is_ban_slider)
	{
		val = 0;
		if(is_vertical)
			pos_button_slider = { pos_slider.x + size_slider.x / 2,pos_slider.y};
		else
			pos_button_slider = { pos_slider.x,pos_slider.y + size_slider.y / 2 };
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
			0,(int)(pos_button_slider.y - pos_slider.y),
			size_idle.x,(int)(pos_slider.y + size_idle.y - pos_button_slider.y)
		};
		rect_covered_dst =
		{
			(int)pos_slider.x,(int)pos_slider.y,
			size_covered.x,(int)(pos_button_slider.y - pos_slider.y)
		};
		rect_idle_dst =
		{
			(int)pos_slider.x,(int)pos_button_slider.y,
			size_idle.x,(int)(pos_slider.y + size_idle.y - pos_button_slider.y)
		};
	}
	else
	{
		rect_covered_src =
		{
			0,0,
			(int)pos_button_slider.x,(int)size_covered.y
		};
		rect_idle_src =
		{
			(int)(pos_button_slider.x - pos_slider.x),0,
			(int)(pos_slider.x + size_idle.x - pos_button_slider.x),(int)size_idle.y
		};
		rect_covered_dst =
		{
			(int)pos_slider.x,(int)pos_slider.y,
			(int)(pos_button_slider.x - pos_slider.x),(int)size_covered.y
		};
		rect_idle_dst =
		{
			(int)pos_button_slider.x,(int)pos_slider.y,
			(int)(pos_slider.x + size_idle.x - pos_button_slider.x),(int)size_idle.y
		};
	}
	if(is_ban_slider && tex_ban_slider)
	{
		SDL_Point size_ban;
		SDL_QueryTexture(tex_ban_slider, NULL, NULL, &size_ban.x, &size_ban.y);
		SDL_Rect rect_src = { 0,0,size_ban.x,size_ban.y };
		SDL_Rect rect_dst = { pos_slider.x,pos_slider.y,size_ban.x,size_ban.y };
		draw(renderer, tex_ban_slider, &rect_src, &rect_dst);
	}
	else
	{
		draw(renderer, tex_covered, &rect_covered_src, &rect_covered_dst);
		draw(renderer, tex_idle, &rect_idle_src, &rect_idle_dst);
	}
	SDL_Rect rect_button_slider_src =
	{ 0,0,size_button_slider.x,size_button_slider.y };
	SDL_Rect rect_button_slider_dst = 
	{ (int)(pos_button_slider.x - size_button_slider.x / 2),(int)(pos_button_slider.y - size_button_slider.y / 2),
			size_button_slider.x,size_button_slider.y };
	if (tex_button_slider)
		draw(renderer, tex_button_slider, &rect_button_slider_src, &rect_button_slider_dst);

	if(is_show_val)
	{
		SDL_Color textColor = { 255,255,255,255 };
		int int_val = val * 100;
		std::string str_val = std::to_string(int_val);
		SDL_Surface* sur_val = TTF_RenderText_Solid(ResourcesManager::instance()->get_main_font(),
			str_val.c_str(), textColor);
		tex_val = SDL_CreateTextureFromSurface(renderer, sur_val);
		int w, h;
		SDL_QueryTexture(tex_val, NULL, NULL, &w, &h);
		SDL_Rect rect_src = { 0,0,w,h };
		SDL_Rect rect_dst = { pos_slider.x + text_spacing.x,pos_slider.y + text_spacing.y,w,h };
		draw(renderer, tex_val, &rect_src, &rect_dst);
		draw_help(renderer, &rect_dst);
	}
}