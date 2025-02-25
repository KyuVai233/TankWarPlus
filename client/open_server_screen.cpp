#include "open_server_screen.h"

OpenServerScreen::OpenServerScreen(const std::string& screen_type, Mix_Chunk* background_bgm)
	:Screen(screen_type, background_bgm)
{
	ResourcesManager* instance = ResourcesManager::instance();

	{
		SDL_Rect rect_src = { 0,0,1280,900 };
		SDL_Rect rect_dst = { 0,0,1280,960 };
		Image* open_server_background = new Image(instance->find_texture("open_server_background"), rect_src, rect_dst);
		image_list.emplace_back(open_server_background);
	}
	{
		Image* img_background_plus = new Image(instance->find_texture("open_server_background_plus"),
			{ 0,0,128,128 }, { 384,204,512,512 });
		image_list.emplace_back(img_background_plus);
	}
	{
		Image* img_ip_word = new Image(instance->find_texture("ip_word"),
			{ 0,0,128,128 }, { 384,204,512,512 });
		image_list.emplace_back(img_ip_word);
	}
	{
		Image* img_port_word = new Image(instance->find_texture("port_word"),
			{ 0,0,128,128 }, { 384,204,512,512 });
		image_list.emplace_back(img_port_word);
	}

	{
		SDL_Texture* button_ip_idle = instance->find_texture("button_ip_idle");
		SDL_Texture* button_ip_clicked = instance->find_texture("button_ip_clicked");
		button_ip = new Button(button_ip_idle, button_ip_idle, button_ip_clicked);
		button_ip->set_size_src({ 128,128 });
		button_ip->set_position_dst({ 384,204 });
		button_ip->set_size_dst({ 512,512 });
		button_ip->set_position_usable({ 43 * 4 + 384,17 * 4 + 204 });
		button_ip->set_size_usable({ 72 * 4,15 * 4 });
		button_ip->set_music_covered(instance->find_audio("click_button"));
		button_ip->set_on_left_clicked([&]()
			{
				is_write_ip = true;
			});
		button_list.emplace_back(button_ip);
	}
	{
		SDL_Texture* button_port_idle = instance->find_texture("button_port_idle");
		SDL_Texture* button_port_clicked = instance->find_texture("button_port_clicked");
		button_port = new Button(button_port_idle, button_port_idle, button_port_clicked);
		button_port->set_size_src({ 128,128 });
		button_port->set_position_dst({ 384,204 });
		button_port->set_size_dst({ 512,512 });
		button_port->set_position_usable({ 43 * 4 + 384,37 * 4 + 204 });
		button_port->set_size_usable({ 72 * 4,15 * 4 });
		button_port->set_music_covered(instance->find_audio("click_button"));
		button_port->set_on_left_clicked([&]()
			{
				is_write_port = true;
			});
		button_list.emplace_back(button_port);
	}
	{
		SDL_Texture* button_connect_home_idle = instance->find_texture("button_connect_home_idle");
		SDL_Texture* button_connect_home_covered = instance->find_texture("button_connect_home_covered");
		Button* button_connect_home = new Button(button_connect_home_idle, button_connect_home_covered, button_connect_home_idle);
		button_connect_home->set_size_src(button_connect_home->get_initial_size());
		button_connect_home->set_position_dst({ 430,519 });
		button_connect_home->set_size_dst(button_connect_home->get_initial_size());
		button_connect_home->set_position_usable({ 430 + 3,519 + 15 });
		button_connect_home->set_size_usable({ 58,28 });
		button_connect_home->set_music_covered(instance->find_audio("click_button"));
		button_list.emplace_back(button_connect_home);
	}
	{
		SDL_Texture* button_create_home_idle = instance->find_texture("button_create_home_idle");
		SDL_Texture* button_create_home_covered = instance->find_texture("button_create_home_covered");
		Button* button_create_home = new Button(button_create_home_idle, button_create_home_covered, button_create_home_idle);
		button_create_home->set_size_src(button_create_home->get_initial_size());
		button_create_home->set_position_dst({ 545,519 });
		button_create_home->set_size_dst(button_create_home->get_initial_size());
		button_create_home->set_position_usable({ 545 + 3,519 + 15 });
		button_create_home->set_size_usable({ 58,28 });
		button_create_home->set_music_covered(instance->find_audio("click_button"));
		button_list.emplace_back(button_create_home);
	}
	{
		SDL_Texture* button_quit_open_server_idle = instance->find_texture("button_quit_open_server_idle");
		SDL_Texture* button_quit_open_server_covered = instance->find_texture("button_quit_open_server_covered");
		Button* button_quit_open_server = new Button(button_quit_open_server_idle, button_quit_open_server_covered, button_quit_open_server_idle);
		button_quit_open_server->set_size_src(button_quit_open_server->get_initial_size());
		button_quit_open_server->set_position_dst({ 660,519 });
		button_quit_open_server->set_size_dst(button_quit_open_server->get_initial_size());
		button_quit_open_server->set_position_usable({ 660 + 3,519 + 15 });
		button_quit_open_server->set_size_usable({ 58,28 });
		button_quit_open_server->set_music_covered(instance->find_audio("click_button"));
		button_list.emplace_back(button_quit_open_server);
	}
}

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
				button->set_button_status(Button::ButtonStatus::Clicked);
				if (event.button.button == SDL_BUTTON_LEFT)
					button->take_on_left_clicked();
				else if (event.button.button == SDL_BUTTON_RIGHT)
					button->take_on_right_clicked();
			}
		}
		if (!button_ip->check_in_button(pos_cursor.x, pos_cursor.y))
		{
			is_write_ip = false;
			button_ip->set_button_status(Button::ButtonStatus::Idle);
		}
		if (!button_port->check_in_button(pos_cursor.x, pos_cursor.y))
		{
			is_write_port = false; 
			button_port->set_button_status(Button::ButtonStatus::Idle);
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
		else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
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
			else if (!button->check_in_button(pos_cursor.x, pos_cursor.y)
				&& button->get_button_status() == Button::ButtonStatus::Covered)
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