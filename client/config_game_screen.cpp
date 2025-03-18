#include "config_game_screen.h"

ConfigGameScreen::ConfigGameScreen(const std::string& screen_type, Mix_Chunk* background_bgm)
	:Screen(screen_type, background_bgm)
{

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
}

void ConfigGameScreen::on_update(float delta)
{
	Screen::on_update(delta);
}

void ConfigGameScreen::on_render(SDL_Renderer* renderer)
{
	Screen::on_render(renderer);
}