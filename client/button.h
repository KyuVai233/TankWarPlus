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
		ClickedLeft,
		ClickedRight
	};

public:
	void set_position_src(const Vector2& position)
	{
		this->position_src = position;
	}

	void set_size_src(const Vector2& size)
	{
		this->size_src = size;
	}

	void set_position_dst(const Vector2& position)
	{
		this->position_dst = position;
	}

	void set_size_dst(const Vector2& size)
	{
		this->size_dst = size;
	}

	const Vector2& get_initial_size()
	{
		int width, height;
		SDL_QueryTexture(texture_idle, nullptr, nullptr, &width, &height);
		return { (float)width,(float)height };
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
		if (on_left_clicked)	on_left_clicked();
	}

	void set_on_right_clicked(std::function<void()> on_right_clicked)
	{
		this->on_right_clicked = on_right_clicked;
	}

	void take_on_right_clicked()
	{
		if (on_right_clicked)	on_right_clicked();
	}

	//���λ���Ƿ��ڰ�ť��
	bool check_in_button(float x, float y) const
	{
		return (x >= position_dst.x && x <= position_dst.x + size_dst.x) &&
			(y >= position_dst.y && y <= position_dst.y + size_dst.y);
	}

	void on_update(float delta);

	void on_render(SDL_Renderer* renderer);

private:
	Vector2 position_src = { 0,0 };				//��ȡλ��
	Vector2 size_src;							//��ȡ��С
	Vector2 position_dst = { 0,0 };				//Ŀ��λ��
	Vector2 size_dst = size_src;				//Ŀ���С
	bool is_visible = true;						//�Ƿ�ɼ�
	bool is_usable = true;						//�Ƿ����
	SDL_Texture* texture_idle = nullptr;		//��ť��������
	SDL_Texture* texture_covered = nullptr;		//��ť����������
	SDL_Texture* texture_clicked = nullptr;		//��ť���������
	SDL_Texture* current_texture = texture_idle;//��ť��ǰ����
	ButtonStatus status = ButtonStatus::Idle;	//��ť��ǰ״̬
	Mix_Chunk* music_covered = nullptr;			//�������ʱ������Ч
	Mix_Chunk* music_clicked = nullptr;			//�����ʱ��Ч

	std::function<void()> on_left_clicked;		//�����̧���ִ�лص�
	std::function<void()> on_right_clicked;		//���Ҽ�̧���ִ�лص�
};
