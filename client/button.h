#pragma once

#include "vector2.h"
#include "util.h"

#include <functional>

class Button
{
public:
	Button() = default;
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

	void take_on_left_clicked()	const
	{
		if (on_left_clicked)	on_left_clicked();
	}

	void set_on_right_clicked(std::function<void()> on_right_clicked)
	{
		this->on_right_clicked = on_right_clicked;
	}

	//检测位置是否在按钮内
	bool check_in_button(float x, float y) const
	{
		return (x >= position.x && x <= position.x + size.x) &&
			(y >= position.y && y <= position.y + size.y);
	}

	void on_input(const SDL_Event& event);
	void on_render(SDL_Renderer* renderer);

private:
	Vector2 position;							//位置
	Vector2 size;								//大小
	bool is_visible = true;						//是否可见
	bool is_usable = true;						//是否可用
	SDL_Texture* texture = nullptr;				//按钮图片纹理

	std::function<void()> on_left_clicked;		//按左键抬起后执行回调
	std::function<void()> on_right_clicked;		//按右键抬起后执行回调
};
