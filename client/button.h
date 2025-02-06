#pragma once

#include "vector2.h"
#include "util.h"

#include <functional>

class Button
{
public:
	Button(SDL_Texture* texture_idle, SDL_Texture* texture_covered, SDL_Texture* texture_clicked)
		:texture_idle(texture_idle), texture_covered(texture_covered), texture_clicked(texture_clicked)
	{ }
	~Button() = default;

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

	void set_size(const Vector2& position)
	{
		this->size = size;
	}

	void set_is_visible(bool flag)
	{
		is_visible = flag;
	}

	void set_is_usable(bool flag)
	{
		is_usable = flag;
	}

	void set_on_left_clicked(std::function<void()> on_left_clicked)
	{
		this->on_left_clicked = on_left_clicked;
	}

	void take_on_left_clicked()	const
	{
		if (on_left_clicked)	on_left_clicked();
	}

	void set_on_right_clicked(std::function<void()> on_right_clicked)
	{
		this->on_right_clicked = on_right_clicked;
	}

	void take_on_right_clicked()	const
	{
		if (on_right_clicked)	on_right_clicked();
	}

	//检测位置是否在按钮内
	bool check_in_button(float x, float y) const
	{
		return (x >= position.x && x <= position.x + size.x) &&
			(y >= position.y && y <= position.y + size.y);
	}

	void on_render(SDL_Renderer* renderer);

private:
	Vector2 position;							//位置
	Vector2 size;								//大小
	bool is_visible = true;						//是否可见
	bool is_usable = true;						//是否可用
	SDL_Texture* texture_idle = nullptr;		//按钮闲置纹理
	SDL_Texture* texture_covered = nullptr;		//按钮被覆盖纹理
	SDL_Texture* texture_clicked = nullptr;		//按钮被点击纹理
	SDL_Texture* current_texture = texture_idle;//按钮当前纹理

	std::function<void()> on_left_clicked;		//按左键抬起后执行回调
	std::function<void()> on_right_clicked;		//按右键抬起后执行回调
};
