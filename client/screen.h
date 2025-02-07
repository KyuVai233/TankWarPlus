#pragma once

#include "button.h"

#include "../thirdparty/httplib.h"

#include <vector>
#include <string>

class Screen
{
public:
	Screen() = delete;
	Screen(SDL_Texture* tex_background, const std::string& screen_type)
		:tex_background(tex_background), screen_type(screen_type), next_screen("none") { };
	~Screen() = default;

	void set_next_screen(const std::string& next_screen)
	{
		this->next_screen = next_screen;
	}

	virtual void on_input(const SDL_Event& event);
	virtual void on_render(SDL_Renderer* renderer);
	virtual void to_post();
	virtual void do_post();

protected:
	std::string screen_type;
	std::string next_screen;

	std::vector<Button*> button_list;				//°´Å¥ÁÐ±í
	SDL_Texture* tex_background = nullptr;			//±³¾°Í¼
};