#pragma once

#include "vector2.h"
#include "util.h"
#include "resources_manager.h"

#include "SDL_image.h"
#include "SDL_ttf.h"

#include <functional>

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
		SDL_QueryTexture(tex_button_slider, NULL, NULL, &size_button_slider.x, &size_button_slider.y);
	}

	void set_pos_slider(const Vector2& pos)
	{
		pos_slider = pos;
		SDL_Point size;
		SDL_QueryTexture(tex_covered, NULL, NULL, &size.x, &size.y);
		pos_button_slider = { pos.x + size.x / 2, pos.y + size.y / 2 };
	}

	void set_tex_ban_slider(SDL_Texture* tex)
	{
		tex_ban_slider = tex;
	}

	const Vector2& get_pos_button_slider() const
	{
		return pos_button_slider;
	}

	bool is_in_button_slider(float x, float y) const
	{
		return (x >= pos_button_slider.x - size_button_slider.x / 2 && x <= pos_button_slider.x + size_button_slider.x / 2) &&
			(y >= pos_button_slider.y - size_button_slider.y / 2 && y <= pos_button_slider.y + size_button_slider.y / 2);
	}

	float get_val() const
	{
		return val;
	}

	void set_is_show_val(bool flag)
	{
		is_show_val = flag;
	}

	void set_text_spacing(const Vector2& size)
	{
		text_spacing = size;
	}

	void set_clicked_text(std::function<void()> clicked_text)
	{
		this->clicked_text = clicked_text;
	}

	void set_is_open_ban_slider(bool flag)
	{
		is_open_ban_slider = flag;
	}

	void on_input(const SDL_Event& event);

	void on_update(float delta);

	void on_render(SDL_Renderer* renderer);

private:
	Vector2 pos_slider;
	Vector2 pos_button_slider;

	SDL_Texture* tex_button_slider = nullptr;
	SDL_Texture* tex_covered = nullptr;
	SDL_Texture* tex_idle = nullptr;
	SDL_Texture* tex_ban_slider = nullptr;
	SDL_Texture* tex_val = nullptr;

	float val = 50;										//值（百分比）
	bool is_vertical = false;							//滑块是否纵向移动
	bool is_clicked_mouse_left_and_in_button = false;	//是否按下鼠标左键
	bool is_show_val = false;							//是否显示值
	bool is_ban_slider = false;							//是否移除滑块效果
	bool is_open_ban_slider = false;					//是否开启点击文字移除滑块功能功能

	SDL_Point pos_cursor = { 0,0 };						//鼠标位置
	SDL_Point size_button_slider = { 0,0 };				//滑块纹理大小
	Vector2 text_spacing = { 0,0 };						//值与滑块(左上角)间距
	std::function<void()> clicked_text;					//点击val后效果
};
