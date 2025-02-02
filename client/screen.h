#pragma once

#include "button.h"
#include "screen_type.h"

#include <vector>

class Screen
{
public:
	Screen() = delete;
	Screen(ScreenType screen_type)
		:screen_type(screen_type) { }
	~Screen() = default;

	const ScreenType& get_screen_type() const
	{
		return screen_type;
	}

	//���ð�ť
	void put_button(Button* button)
	{
		button_list.emplace_back(button);
	}

	void set_tex_backfround(SDL_Texture* tex_background)
	{
		this->tex_background = tex_background;
	}

	void on_input(const SDL_Event& event);
	void on_render(SDL_Renderer* renderer);

private:
	ScreenType screen_type = ScreenType::None;		//��������
	std::vector<Button*> button_list;				//��ť�б�
	SDL_Texture* tex_background = nullptr;			//����ͼ
};