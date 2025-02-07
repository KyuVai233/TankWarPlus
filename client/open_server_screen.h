#pragma once

#include "screen.h"
#include "config_game_manager.h"
#include "config_home_manager.h"

#include <SDL.h>

class OpenServerScreen : public Screen
{
public:
	OpenServerScreen(SDL_Texture* tex_background, const std::string& screen_type)
		:Screen(tex_background, screen_type)
	{
	}

	~OpenServerScreen() = default;

	void on_input(const SDL_Event& event) override;

	void on_render(SDL_Renderer* renderer) override;

	void to_post() override;

private:
	bool is_try_build = false;		//�Ƿ��Դ�������
	bool is_try_join = false;		//�Ƿ��Լ��뷿��
};
