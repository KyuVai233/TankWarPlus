#pragma once

#include "screen.h"
#include "resources_manager.h"

class MainScreen : public Screen
{
public:
	MainScreen() = delete;
	MainScreen(SDL_Texture* tex_background, const std::string& screen_type)
		:Screen(tex_background, screen_type){ }
	~MainScreen() = default;

	void on_input(const SDL_Event& event) override;
	void on_render(SDL_Renderer* renderer) override;

private:

};
