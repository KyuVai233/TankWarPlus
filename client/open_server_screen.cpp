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
			{ 0,0,128,128 }, { 384,224,512,512 });
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
		button_port->set_position_dst({ 384,224 });
		button_port->set_size_dst({ 512,512 });
		button_port->set_position_usable({ 43 * 4 + 384,37 * 4 + 224 });
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
		button_connect_home->set_position_dst({ 490,519 });
		button_connect_home->set_size_dst(button_connect_home->get_initial_size());
		button_connect_home->set_position_usable({ 490 + 3,519 + 15 });
		button_connect_home->set_size_usable({ 58,28 });
		button_connect_home->set_music_covered(instance->find_audio("click_button"));
		button_list.emplace_back(button_connect_home);
		button_connect_home->set_on_left_clicked([&]()
			{
				/*
				httplib::Client client("192.168.192.134:25565");
				httplib::Result result = client.Post("hello");
				if (!result || result->status != 200)
				{
					std::cout << "error" << std::endl;

					return -1;
				}

				std::cout << result->body << std::endl;

				system("pause");
				*/
				if (!connect())
				{
					ConfigHomeManager* home_instance = ConfigHomeManager::instance();
					home_instance->set_ip("");
					next_screen = "open_server_screen";
				}
			});
	}
	{
		SDL_Texture* button_create_home_idle = instance->find_texture("button_create_home_idle");
		SDL_Texture* button_create_home_covered = instance->find_texture("button_create_home_covered");
		Button* button_create_home = new Button(button_create_home_idle, button_create_home_covered, button_create_home_idle);
		button_create_home->set_size_src(button_create_home->get_initial_size());
		button_create_home->set_position_dst({ 615,519 });
		button_create_home->set_size_dst(button_create_home->get_initial_size());
		button_create_home->set_position_usable({ 615 + 3,519 + 15 });
		button_create_home->set_size_usable({ 58,28 });
		button_create_home->set_music_covered(instance->find_audio("click_button"));
		button_list.emplace_back(button_create_home);
		button_create_home->set_on_left_clicked([&]()
			{
				create_home();
			});
	}
	{
		SDL_Texture* button_quit_open_server_idle = instance->find_texture("button_quit_open_server_idle");
		SDL_Texture* button_quit_open_server_covered = instance->find_texture("button_quit_open_server_covered");
		Button* button_quit_open_server = new Button(button_quit_open_server_idle, button_quit_open_server_covered, button_quit_open_server_idle);
		button_quit_open_server->set_size_src(button_quit_open_server->get_initial_size());
		button_quit_open_server->set_position_dst({ 740,519 });
		button_quit_open_server->set_size_dst(button_quit_open_server->get_initial_size());
		button_quit_open_server->set_position_usable({ 740 + 3,519 + 15 });
		button_quit_open_server->set_size_usable({ 58,28 });
		button_quit_open_server->set_music_covered(instance->find_audio("click_button"));
		button_quit_open_server->set_on_left_clicked([&]()
			{
				str_ip.clear();
				str_port.clear();
				set_next_screen("main_screen");
			});
		button_list.emplace_back(button_quit_open_server);
	}
}

void OpenServerScreen::on_input(const SDL_Event& event)
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
			if (is_write_ip && !str_ip.empty())
				str_ip.pop_back();
			if (is_write_port && !str_port.empty())
				str_port.pop_back();
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
		{
			if (is_write_ip)
			{
				is_write_ip = false;
				if (button_ip->check_in_button(pos_cursor.x, pos_cursor.y))
					button_ip->set_button_status(Button::ButtonStatus::Covered);
				else
					button_ip->set_button_status(Button::ButtonStatus::Idle);
			}
			if (is_write_port)
			{
				is_write_port = false;
				if (button_port->check_in_button(pos_cursor.x, pos_cursor.y))
					button_port->set_button_status(Button::ButtonStatus::Covered);
				else
					button_port->set_button_status(Button::ButtonStatus::Idle);
			}
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_C && (modState & KMOD_CTRL))
		{
			if (is_write_ip && !str_ip.empty())
				SDL_SetClipboardText(str_ip.c_str());
			else if(is_write_port && !str_port.empty())
				SDL_SetClipboardText(str_port.c_str());
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_V && (modState & KMOD_CTRL))
		{
			char* text_ctrl_v = SDL_GetClipboardText();
			for (int i = 0; text_ctrl_v[i] != '\0'; i++)
			{
				if (is_write_ip)
					if (isalnum(text_ctrl_v[i]) || text_ctrl_v[i] == '.')
						str_ip += text_ctrl_v[i];
				if (is_write_port)
					if (text_ctrl_v[i] >= '0' && text_ctrl_v[i] <= '9')
						str_port += text_ctrl_v[i];
			}
		}
		break;
	case SDL_TEXTINPUT:
	{
		const char* word = event.text.text;
			if (is_write_ip)
				if (isalnum(*word) || *word == '.')
					str_ip += word;
				if (is_write_port)
					if (*word >= '0' && *word <= '9')
						str_port += word;
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
		std::regex pattern_ip("^(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)){3}$");
		if (std::regex_match(str_ip, pattern_ip) || str_ip == "localhost")
		{
			ConfigHomeManager::instance()->set_ip(str_ip);
		}
	}

	//匹配端口
	if (!is_write_port && !str_port.empty())
	{
		std::regex pattern_port("^(0|[1-9]\\d{0,3}|[1-5]\\d{4}|6[0-4]\\d{3}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])$");
		if (std::regex_match(str_port, pattern_port))
		{
			ConfigHomeManager::instance()->set_port(std::atoi(str_port.c_str()));
		}
	}
}

void OpenServerScreen::on_render(SDL_Renderer* renderer)
{
	Screen::on_render(renderer);
	SDL_Color textColor = { 0,0,0,255 };
	Vector2 text_spacing = { 10,15 };			//文字与文字框间距
	if(!str_ip.empty())
	{
		SDL_Surface* sur_ip = TTF_RenderText_Solid(ResourcesManager::instance()->get_main_font(),
			str_ip.c_str(), textColor);
		SDL_Texture* tex_ip = SDL_CreateTextureFromSurface(renderer, sur_ip);
		int w, h;
		SDL_QueryTexture(tex_ip, NULL, NULL, &w, &h);
		SDL_Rect rect_src = { 0,0,(float)w,(float)h };
		SDL_Rect rect_dst = { 43 * 4 + 384 + text_spacing.x,17 * 4 + 204 + text_spacing.y,(float)w,(float)h };
		draw(renderer, tex_ip, &rect_src, &rect_dst);
	}
	if(!str_port.empty())
	{
		SDL_Surface* sur_port = TTF_RenderText_Solid(ResourcesManager::instance()->get_main_font(),
			str_port.c_str(), textColor);
		SDL_Texture* tex_port = SDL_CreateTextureFromSurface(renderer, sur_port);
		int w, h;
		SDL_QueryTexture(tex_port, NULL, NULL, &w, &h);
		SDL_Rect rect_src = { 0,0,(float)w,(float)h };
		SDL_Rect rect_dst = { 43 * 4 + 384 + text_spacing.x,37 * 4 + 224 + text_spacing.y,(float)w,(float)h };
		draw(renderer, tex_port, &rect_src, &rect_dst);
	}
}

void OpenServerScreen::create_home()
{
	ConfigHomeManager* instance = ConfigHomeManager::instance();
	if (!instance->get_ip().empty() && instance->get_port() != 0)
	{
		ConfigGameManager::instance()->get_player()->set_identity(Player::Identity::Owner);
		ConfigGameManager::instance()->get_player()->set_order(0);
		set_next_screen("home_screen");
	}
}

bool OpenServerScreen::connect()
{
	is_write_ip = false;
	is_write_port = false;
	ConfigGameManager* instance = ConfigGameManager::instance();
	const std::string str_address = ConfigHomeManager::instance()->get_address();
	instance->client = new httplib::Client(str_address);
	instance->client->set_keep_alive(true);

	httplib::Result result_join = instance->client->Post("join", 
		instance->get_player()->get_player_id(), "text/plain");

	if (!result_join || result_join->status != 200)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"无法连接至服务器", "connect_error", NULL);
		return false;
	}

	int order = std::stoi(result_join->body);
	if (order == -1)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"名字未定义或重复", "name_error", NULL);
		return false;
	}
	
	set_next_screen("home_screen");
	return true;
}