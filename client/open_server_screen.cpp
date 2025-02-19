#include "open_server_screen.h"

void OpenServerScreen::on_input(const SDL_Event& event)
{
	SDL_Point pos_cursor = { event.motion.x,event.motion.y };
	switch (event.type)
	{
	case SDL_MOUSEBUTTONUP:
		for (Button* button : button_list)
		{
			if (button->check_in_button(pos_cursor.x, pos_cursor.y))
			{
				if (event.button.button == SDL_BUTTON_LEFT)
					button->set_button_status(Button::ButtonStatus::ClickedLeft);
				else if (event.button.button == SDL_BUTTON_RIGHT)
					button->set_button_status(Button::ButtonStatus::ClickedRight);
			}
		}
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
		{
			if (is_write_ip)
				str_ip.pop_back();
			if (is_write_port)
				str_port.pop_back();
		}
		else if (event.key.keysym.scancode == SDLK_RETURN)
		{
			if (is_write_ip)
				is_write_ip = false;
			if (is_write_port)
				is_write_port = false;
		}
		break;
	case SDL_TEXTINPUT:
	{
		const char* word = event.text.text;
		for (int i = 0; word[i] != '\0'; i++)
		{
			if (is_write_ip)
				if (isalnum(word[i]) || word[i] == '.')
					str_ip += word[i];
				else if (is_write_port)
					if (word[i] >= '0' && word[i] <= '9')
						str_port += word[i];
		}
		break;
	}
	case SDL_MOUSEMOTION:
		for (Button* button : button_list)
		{
			if (button->check_in_button(pos_cursor.x, pos_cursor.y)
				&& button->get_button_status() == Button::ButtonStatus::Idle)
			{
				button->set_button_status(Button::ButtonStatus::Covered);
				Mix_PlayChannel(-1, button->get_music_covered(), 0);
			}
			else
				button->set_button_status(Button::ButtonStatus::Idle);
		}
		break;
	default:
		break;
	}
}

void OpenServerScreen::on_update(float delta)
{
	Screen::on_update(delta);

	//匹配ip
	if (!is_write_ip && !str_ip.empty())
	{
		std::regex pattern_ip("^(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)(\.(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)){3}$");
		if (std::regex_match(str_ip, pattern_ip))
		{
			ConfigHomeManager::instance()->set_ip(str_ip);
		}
	}

	//匹配端口
	if (!is_write_port && !str_port.empty())
	{
		std::regex pattern_port("^(0|[1-9]\d{0,3}|[1-5]\d{4}|6[0-4]\d{3}|65[0-4]\d{2}|655[0-2]\d|6553[0-5])$");
		if (std::regex_match(str_port, pattern_port))
		{
			ConfigHomeManager::instance()->set_port(std::atoi(str_port.c_str()));
		}
	}
}

void OpenServerScreen::on_render(SDL_Renderer* renderer)
{
	Screen::on_render(renderer);
}

void OpenServerScreen::connect()
{
	ConfigGameManager* instance = ConfigGameManager::instance();
	const std::string str_address = ConfigHomeManager::instance()->get_address();
	instance->client = new httplib::Client(str_address);
	instance->client->set_keep_alive(true);

	httplib::Result result_join = instance->client->Post("join", 
		instance->get_player()->get_player_id(), "text/plain");
	if (!result_join || result_join != 200)
	{
		//未连接到服务器
		return;
	}
	
	int order = std::stoi(result_join->body);
	if (order == -1)
	{
		//名字未定义
		return;
	}
}