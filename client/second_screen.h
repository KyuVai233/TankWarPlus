#pragma once

#include "button.h"
#include "image.h"
#include "slider.h"
#include "resources_manager.h"

#include <string>

class SecondScreen
{
public:
	SecondScreen(const std::string& screen_type)
	{
	}

	~SecondScreen()
	{
	}

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

	const Vector2& get_position() const
	{
		return position;
	}

	void on_input(const SDL_Event& event);
	void on_update(float delta);
	void on_render(SDL_Renderer* renderer);
	void do_post(float delta);
	void entry_screen();
	void set_button(Button* button);
	void set_image(Image* image);

private:
	Vector2 position = { 0,0 };
	std::vector<Button*> button_list;									//��ť�б�
	std::vector<Image*> image_list;										//ͼƬ�б�
	std::vector<Slider*> slider_list;									//�����б�
};

