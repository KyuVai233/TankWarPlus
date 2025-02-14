#include "main_screen.h"

MainScreen::MainScreen(SDL_Texture* tex_background, const std::string& screen_type)
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
	button->set_music_clicked(instance->find_audio("click_button"));
	button->set_on_left_clicked([&]()
		{
			set_next_screen("open_server_screen");
		});
	button_list.emplace_back(button);
}

void MainScreen::on_input(const SDL_Event& event)
{
	Screen::on_input(event);
}

void MainScreen::on_update(float delta)
{
	Screen::on_update(delta);
}

void MainScreen::on_render(SDL_Renderer* renderer)
{
	Screen::on_render(renderer);

	logo->draw_image(renderer);
}