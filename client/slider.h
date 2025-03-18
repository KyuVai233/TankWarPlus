#pragma once

#include "vector2.h"
#include "util.h"

#include "SDL_image.h"

class Slider
{
public:
	Slider(SDL_Texture* tex_idle, SDL_Texture* tex_covered, bool is_vertical)
		:tex_idle(tex_idle), tex_covered(tex_covered), is_vertical(is_vertical)
	{ }

	~Slider() = default;

	void set_tex_button_slider(SDL_Texture* tex_button_slider)
	{
		this->tex_button_slider = tex_button_slider;
	}

	bool is_in_button_slider(float x, float y) const
	{
		SDL_Point size;
		SDL_QueryTexture(tex_button_slider, NULL, NULL, &size.x, &size.y);
		return (x >= pos_button_slider.x && x <= pos_button_slider.x + size.x) &&
			(y >= pos_button_slider.y && y <= pos_button_slider.y + size.y);
	}

	float get_val() const
	{
		return val;
	}

	void on_input(const SDL_Event& event);

	void on_render(SDL_Renderer* renderer);

private:
	Vector2 pos_slider;
	Vector2 pos_button_slider = pos_button_slider;

	SDL_Texture* tex_button_slider = nullptr;
	SDL_Texture* tex_covered = nullptr;
	SDL_Texture* tex_idle = nullptr;

	float val = 0;										//值（百分比）
	bool is_vertical = false;							//滑块是否纵向移动

	SDL_Point pos_cursor_last = { 0,0 };				//鼠标上一次位置
};
