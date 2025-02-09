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

	void set_is_click_left(bool flag)
	{
		is_clicked_left = flag;
	}

	bool get_is_clicked_left() const
	{
		return is_clicked_left;
	}

	void set_is_click_right(bool flag)
	{
		is_clicked_right = flag;
	}
	
	bool get_is_clicked_right() const
	{
		return is_clicked_right;
	}

	void set_on_left_clicked(std::function<void()> on_left_clicked)
	{
		this->on_left_clicked = on_left_clicked;
	}

	void take_on_left_clicked()
	{
		is_clicked_left = false;
		if (on_left_clicked)	on_left_clicked();
	}

	void set_on_right_clicked(std::function<void()> on_right_clicked)
	{
		this->on_right_clicked = on_right_clicked;
	}

	void take_on_right_clicked()
	{
		is_clicked_right = false;
		if (on_right_clicked)	on_right_clicked();
	}

	//���λ���Ƿ��ڰ�ť��
	bool check_in_button(float x, float y) const
	{
		return (x >= position.x && x <= position.x + size.x) &&
			(y >= position.y && y <= position.y + size.y);
	}

	void on_render(SDL_Renderer* renderer);

private:
	Vector2 position;							//λ��
	Vector2 size;								//��С
	bool is_visible = true;						//�Ƿ�ɼ�
	bool is_usable = true;						//�Ƿ����
	SDL_Texture* texture_idle = nullptr;		//��ť��������
	SDL_Texture* texture_covered = nullptr;		//��ť����������
	SDL_Texture* texture_clicked = nullptr;		//��ť���������
	SDL_Texture* current_texture = texture_idle;//��ť��ǰ����
	bool is_clicked_left = false;				//�Ƿ����
	bool is_clicked_right = false;				//�Ƿ��һ�

	std::function<void()> on_left_clicked;		//�����̧���ִ�лص�
	std::function<void()> on_right_clicked;		//���Ҽ�̧���ִ�лص�
};
