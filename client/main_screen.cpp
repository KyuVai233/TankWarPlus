#include "main_screen.h"

MainScreen::MainScreen(const std::string& screen_type, Mix_Chunk* background_bgm)
	:Screen(screen_type, background_bgm)
{
	ResourcesManager* instance = ResourcesManager::instance();

	{
		SDL_Rect rect_src = { 0,0,1280,900 };
		SDL_Rect rect_dst = { 0,0,1280,960 };
		Image* main_background = new Image(instance->find_texture("main_background"), rect_src, rect_dst);
		image_list.emplace_back(main_background);
	}
	{
		const float mul = 3.5f;
		SDL_Rect rect_src = { 0,0,128,64 };
		SDL_Rect rect_dst = { 416,0,128 * mul,64 * mul };
		Image* logo = new Image(instance->find_texture("logo"), rect_src, rect_dst);
		image_list.emplace_back(logo);
	}

	{
		SDL_Texture* tex_button_fight_idle = instance->find_texture("button_fight_idle");
		SDL_Texture* tex_button_fight_covered = instance->find_texture("button_fight_covered");
		Button* button_fight = new Button(tex_button_fight_idle, tex_button_fight_covered, nullptr);
		button_fight->set_position_src({ 2,15 });
		button_fight->set_size_src({ 101,25 });
		button_fight->set_position_dst({ 60,250 });
		button_fight->set_size_dst({ 404,100 });
		button_fight->set_music_covered(instance->find_audio("click_button"));
		button_fight->set_on_left_clicked([&]()
			{
				set_next_screen("open_server_screen");
			});
		button_list.emplace_back(button_fight);
	}

	{
		SDL_Texture* tex_button_config_idle = instance->find_texture("button_config_idle");
		SDL_Texture* tex_button_config_covered = instance->find_texture("button_config_covered");
		Button* button_config = new Button(tex_button_config_idle, tex_button_config_covered, nullptr);
		button_config->set_position_src({ 2,15 });
		button_config->set_size_src({ 101,25 });
		button_config->set_position_dst({ 60,450 });
		button_config->set_size_dst({ 404,100 });
		button_config->set_music_covered(instance->find_audio("click_button"));
		button_config->set_on_left_clicked([&]()
			{
				set_next_screen("open_server_screen");
			});
		button_list.emplace_back(button_config);
	}

	{
		SDL_Texture* tex_button_help_idle = instance->find_texture("button_help_idle");
		SDL_Texture* tex_button_help_covered = instance->find_texture("button_help_covered");
		Button* button_help = new Button(tex_button_help_idle, tex_button_help_covered, nullptr);
		button_help->set_position_src({ 2,15 });
		button_help->set_size_src({ 101,25 });
		button_help->set_position_dst({ 60,650 });
		button_help->set_size_dst({ 404,100 });
		button_help->set_music_covered(instance->find_audio("click_button"));
		button_help->set_on_left_clicked([&]()
			{
				set_next_screen("open_server_screen");
			});
		button_list.emplace_back(button_help);
	}
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
}