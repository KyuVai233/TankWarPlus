#pragma once

#include "screen.h"

#include <string>

class ConfigGameScreen : public Screen
{
public:
	ConfigGameScreen(const std::string& screen_type, Mix_Chunk* background_bgm);

	~ConfigGameScreen() = default;

	void on_input(const SDL_Event& event) override;

	void on_update(float delta) override;

	void on_render(SDL_Renderer* renderer) override;

private:
	std::string str_player_id;
	bool is_write_id = false;

	Button* button_player_id = nullptr;
};
