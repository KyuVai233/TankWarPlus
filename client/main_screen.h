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
		ResourcesManager* instance = ResourcesManager::instance();

		const float mul = 3.5f;
		SDL_Rect rect_src = { 0,0,128,64 };
		SDL_Rect rect_dst = { 416,0,128 * mul,64 * mul };
		logo = new Image(instance->find_texture("logo"),
			rect_src, rect_dst);

		SDL_Texture* tex_me_test = instance->find_texture("me");
		Button* button = new Button(tex_me_test, tex_me_test, tex_me_test);
		button->set_size(button->get_initial_size());
		button->set_position({ 0,0 });
		button->set_on_left_clicked([&]()
			{
				set_next_screen("open_server_screen");
			});
		button_list.emplace_back(button);
	}
	~MainScreen() = default;

	void on_input(const SDL_Event& event) override;
	void on_update(float delta) override;
	void on_render(SDL_Renderer* renderer) override;

private:
	Image* logo = nullptr;
	bool is_click_button_start_game = false;
};
