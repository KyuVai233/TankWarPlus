#include "config_game_screen.h"

ConfigGameScreen::ConfigGameScreen(const std::string& screen_type, Mix_Chunk* background_bgm)
	:Screen(screen_type, background_bgm)
{
	ResourcesManager* instance = ResourcesManager::instance();
	{
		SDL_Texture* tex_game_config_background = instance->find_texture("game_config_background");
		Image* game_config_background = new Image(tex_game_config_background, { 0,0,1280,960 }, { 0,0,1280,960 });
		image_list.emplace_back(game_config_background);
	}
	{
		SDL_Texture* button_back_in_game_config_idle = instance->find_texture("button_back_in_game_config_idle");
		Button* button_back_in_game_config = new Button(button_back_in_game_config_idle, button_back_in_game_config_idle, nullptr);
		button_back_in_game_config->set_size_src(button_back_in_game_config->get_initial_size());
		button_back_in_game_config->set_position_dst({ 247,62 });
		button_back_in_game_config->set_music_covered(instance->find_audio("click_button"));
		button_list.emplace_back(button_back_in_game_config);
	}
	{
		SDL_Texture* button_player_id_idle = instance->find_texture("button_player_id_idle");
		Button* button_player_id = new Button(button_player_id_idle, button_player_id_idle, button_player_id_idle);
		button_player_id->set_size_src(button_player_id->get_initial_size());
		button_player_id->set_position_dst({ 525,256 });
		button_player_id->set_music_covered(instance->find_audio("click_button"));
		button_list.emplace_back(button_player_id);
	}
	{
		SDL_Texture* button_apply_in_game_config_idle = instance->find_texture("button_apply_in_game_config_idle");
		Button* button_apply_in_game_config = new Button(button_apply_in_game_config_idle, button_apply_in_game_config_idle, nullptr);
		button_apply_in_game_config->set_size_src(button_apply_in_game_config->get_initial_size());
		button_apply_in_game_config->set_position_dst({ 444,583 });
		button_apply_in_game_config->set_music_covered(instance->find_audio("click_button"));
		button_list.emplace_back(button_apply_in_game_config);
	}
	{
		SDL_Texture* button_init_game_config_idle = instance->find_texture("button_init_game_config_idle");
		Button* button_init_game_config = new Button(button_init_game_config_idle, button_init_game_config_idle, nullptr);
		button_init_game_config->set_size_src(button_init_game_config->get_initial_size());
		button_init_game_config->set_position_dst({ 708,583 });
		button_init_game_config->set_music_covered(instance->find_audio("click_button"));
		button_list.emplace_back(button_init_game_config);
	}
	{
		SDL_Texture* slider_volume_idle = instance->find_texture("slider_volume_idle");
		SDL_Texture* slider_volume_covered = instance->find_texture("slider_volume_covered");
		SDL_Texture* button_slider_volume = instance->find_texture("button_slider_volume");
		SDL_Texture* slider_volume_ban = instance->find_texture("slider_volume_ban");
		Slider* slider_volume = new Slider(slider_volume_idle, slider_volume_covered, false);
		slider_volume->set_tex_button_slider(button_slider_volume);
		slider_volume->set_tex_ban_slider(slider_volume_ban);
		slider_volume->set_pos_slider({ 544,398 });
		slider_volume->set_is_show_val(true);
		slider_volume->set_text_spacing({ 300,-1 });
		slider_volume->set_is_open_ban_slider(true);
		slider_list.emplace_back(slider_volume);
	}
}

void ConfigGameScreen::on_input(const SDL_Event& event)
{
	SDL_Point pos_cursor = { event.motion.x,event.motion.y };
	SDL_Keymod modState = SDL_GetModState();

	switch (event.type)
	{
	case SDL_MOUSEBUTTONUP:
		for (Button* button : button_list)
		{
			if (button->check_in_button(pos_cursor.x, pos_cursor.y))
			{
				button->set_button_status(Button::ButtonStatus::Clicked);
				if (event.button.button == SDL_BUTTON_LEFT)
					button->take_on_left_clicked();
				else if (event.button.button == SDL_BUTTON_RIGHT)
					button->take_on_right_clicked();
			}
		}
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
		{
			if (is_write_id && !str_player_id.empty())
				str_player_id.pop_back();
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
		{
			if (is_write_id)
			{
				is_write_id = false;
				if (button_player_id->check_in_button(pos_cursor.x, pos_cursor.y))
					button_player_id->set_button_status(Button::ButtonStatus::Covered);
				else
					button_player_id->set_button_status(Button::ButtonStatus::Idle);
			}
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_C && (modState & KMOD_CTRL))
		{
			if (is_write_id && !str_player_id.empty())
				SDL_SetClipboardText(str_player_id.c_str());
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_V && (modState & KMOD_CTRL))
		{
			char* text_ctrl_v = SDL_GetClipboardText();
			for (int i = 0; text_ctrl_v[i] != '\0'; i++)
			{
				if (is_write_id)
					if (isalnum(text_ctrl_v[i]) || text_ctrl_v[i] == '_')
						str_player_id += text_ctrl_v[i];
			}
		}
		break;
	case SDL_MOUSEMOTION:
		for (Button* button : button_list)
		{
			if (button->check_in_button(pos_cursor.x, pos_cursor.y)
				&& button->get_button_status() == Button::ButtonStatus::Idle)
			{
				button->set_button_status(Button::ButtonStatus::Covered);
				Mix_PlayChannel(-1, button->get_music_covered(), 0);
			}
			else if (!button->check_in_button(pos_cursor.x, pos_cursor.y)
				&& button->get_button_status() == Button::ButtonStatus::Covered)
				button->set_button_status(Button::ButtonStatus::Idle);
		}
		break;
	default:
		break;
	}

	for (Slider* slider : slider_list)
		slider->on_input(event);
}

void ConfigGameScreen::on_update(float delta)
{
	Screen::on_update(delta);

	for (Slider* slider : slider_list)
		slider->on_update(delta);
}

void ConfigGameScreen::on_render(SDL_Renderer* renderer)
{
	Screen::on_render(renderer);
}