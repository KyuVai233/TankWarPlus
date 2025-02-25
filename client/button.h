#pragma once

#include "vector2.h"
#include "util.h"

#include <SDL_mixer.h>

#include <functional>
#include <iostream>

class Button
{
public:
	Button(SDL_Texture* texture_idle, SDL_Texture* texture_covered, SDL_Texture* texture_clicked)
		:texture_idle(texture_idle), texture_covered(texture_covered), texture_clicked(texture_clicked)
	{ }
	~Button() = default;

	enum class ButtonStatus
	{
		Idle,
		Covered,
		Clicked,
	};

public:
	void set_position_src(const Vector2& position)
	{
		this->position_src = position;
		position_dst = position;
		position_usable = position;
	}

	void set_size_src(const Vector2& size)
	{
		this->size_src = size;
		size_dst = size;
		size_usable = size;
	}

	void set_position_dst(const Vector2& position)
	{
		this->position_dst = position;
		position_usable = position;
	}

	void set_size_dst(const Vector2& size)
	{
		this->size_dst = size;
		size_usable = size;
	}

	const Vector2& get_initial_size()
	{
		int width, height;
		SDL_QueryTexture(texture_idle, nullptr, nullptr, &width, &height);
		return { (float)width,(float)height };
	}

	void set_position_usable(const Vector2& vec)
	{
		position_usable = vec;
	}

	void set_size_usable(const Vector2& vec)
	{
		size_usable = vec;
	}

	SDL_Rect* get_rect_usable() const
	{
		SDL_Rect rect =
		{
			(float)position_usable.x,
			(float)position_usable.y,
			(float)size_usable.x,
			(float)size_usable.y
		};
		return &rect;
	}

	void set_is_visible(bool flag)
	{
		is_visible = flag;
	}

	void set_is_usable(bool flag)
	{
		is_usable = flag;
	}

	void set_button_status(ButtonStatus status)
	{
		if (status == ButtonStatus::Clicked &&
			(!on_left_clicked && !on_right_clicked))
			return;
		this->status = status;
	}

	const ButtonStatus& get_button_status() const
	{
		return status;
	}

	void set_music_covered(Mix_Chunk* music)
	{
		music_covered = music;
	}

	Mix_Chunk* get_music_covered() const
	{
		return music_covered;
	}

	void set_music_clicked(Mix_Chunk* music)
	{
		music_clicked = music;
	}

	Mix_Chunk* get_music_clicked() const
	{
		return music_clicked;
	}

	void set_on_left_clicked(std::function<void()> on_left_clicked)
	{
		this->on_left_clicked = on_left_clicked;
	}

	void take_on_left_clicked()
	{
		if (!on_left_clicked)	
		{
			status = ButtonStatus::Covered;
			return;
		}
		on_left_clicked();
	}

	void set_on_right_clicked(std::function<void()> on_right_clicked)
	{
		this->on_right_clicked = on_right_clicked;
	}

	void take_on_right_clicked()
	{
		if (!on_right_clicked)
		{
			status = ButtonStatus::Covered;
			return;
		}
		on_right_clicked();
	}

	//检测位置是否在按钮内
	bool check_in_button(float x, float y) const
	{
		return (x >= position_usable.x && x <= position_usable.x + size_usable.x) &&
			(y >= position_usable.y && y <= position_usable.y + size_usable.y);
	}

	void on_update(float delta);

	void on_render(SDL_Renderer* renderer);

private:
	Vector2 position_src = { 0,0 };				//截取位置
	Vector2 size_src;							//截取大小
	Vector2 position_dst = { 0,0 };				//目标位置
	Vector2 size_dst = size_src;				//目标大小
	Vector2 position_usable = { 0,0 };			//作用位置
	Vector2 size_usable = size_dst;				//作用大小
	bool is_visible = true;						//是否可见
	bool is_usable = true;						//是否可用
	SDL_Texture* texture_idle = nullptr;		//按钮闲置纹理
	SDL_Texture* texture_covered = nullptr;		//按钮被覆盖纹理
	SDL_Texture* texture_clicked = nullptr;		//按钮被点击纹理
	SDL_Texture* current_texture = texture_idle;//按钮当前纹理
	ButtonStatus status = ButtonStatus::Idle;	//按钮当前状态
	Mix_Chunk* music_covered = nullptr;			//鼠标悬浮时播放音效
	Mix_Chunk* music_clicked = nullptr;			//被点击时音效

	std::function<void()> on_left_clicked;		//按左键抬起后执行回调
	std::function<void()> on_right_clicked;		//按右键抬起后执行回调
};
