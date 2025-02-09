#pragma once

#include "image.h"
#include "screen.h"
#include "screen_manager.h"
#include "resources_manager.h"

class MainScreen : public Screen
{
public:
	MainScreen() = delete;
	MainScreen(SDL_Texture* tex_background, const std::string& screen_type)
		:Screen(tex_background, screen_type) 
	{
		const float mul = 3.5f;
		SDL_Rect rect_src = { 0,0,128,64 };
		SDL_Rect rect_dst = { 416,0,128 * mul,64 * mul };
		logo = new Image(ResourcesManager::instance()->find_texture("logo"),
			rect_src, rect_dst);
	}
	~MainScreen() = default;

	void on_input(const SDL_Event& event) override;
	void on_update(float delta) override;
	void on_render(SDL_Renderer* renderer) override;

private:
	Image* logo = nullptr;
	bool is_click_button_start_game = false;
};
