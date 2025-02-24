#pragma once

#include "image.h"
#include "screen.h"
#include "screen_manager.h"
#include "resources_manager.h"

class MainScreen : public Screen
{
public:
	MainScreen() = delete;
	MainScreen(const std::string& screen_type, Mix_Chunk* background_bgm);
	~MainScreen() = default;

	void on_input(const SDL_Event& event) override;
	void on_update(float delta) override;
	void on_render(SDL_Renderer* renderer) override;

private:
	bool is_click_button_start_game = false;
};
