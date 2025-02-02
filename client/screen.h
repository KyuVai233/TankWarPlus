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

	//放置按钮
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
	ScreenType screen_type = ScreenType::None;		//场景类型
	std::vector<Button*> button_list;				//按钮列表
	SDL_Texture* tex_background = nullptr;			//背景图
};