#include "home_screen.h"

HomeScreen::HomeScreen(const std::string& screen_type, Mix_Chunk* background_bgm)
	:Screen(screen_type, background_bgm)
{
	ResourcesManager* instance = ResourcesManager::instance();
	{
		Image* home_background = new Image(instance->find_texture("home_background"), { 0,0,1600,1200 }, { 0,0,1280,960 });
		image_list.emplace_back(home_background);
	}
	{
		SDL_Texture* button_game_config_in_home_idle = instance->find_texture("button_game_config_in_home_idle");
		Button* button_game_config_in_home = new Button(button_game_config_in_home_idle, nullptr, nullptr);
		button_game_config_in_home->set_size_src(button_game_config_in_home->get_initial_size());
		button_game_config_in_home->set_position_dst({ 16,96 });
		button_game_config_in_home->set_music_clicked(instance->find_audio("click_button"));
		button_list.emplace_back(button_game_config_in_home);
	}
	{
		SDL_Texture* button_quit_in_home_idle = instance->find_texture("button_quit_in_home_idle");
		Button* button_quit_in_home = new Button(button_quit_in_home_idle, nullptr, nullptr);
		button_quit_in_home->set_size_src(button_quit_in_home->get_initial_size());
		button_quit_in_home->set_position_dst({ 16,8 });
		button_quit_in_home->set_music_clicked(instance->find_audio("click_button"));
		button_list.emplace_back(button_quit_in_home);
	}
	{
		SDL_Texture* button_home_config_idle = instance->find_texture("button_home_config_idle");
		Button* button_home_config = new Button(button_home_config_idle, nullptr, nullptr);
		button_home_config->set_size_src(button_home_config->get_initial_size());
		button_home_config->set_position_dst({ 944,124 });
		button_home_config->set_music_clicked(instance->find_audio("click_button"));
		button_list.emplace_back(button_home_config);
	}
	{
		SDL_Texture* player_sit_blue_idle = instance->find_texture("player_sit_blue_idle");
		Button* player_sit_blue = new Button(player_sit_blue_idle, nullptr, nullptr);
		player_sit_blue->set_size_src(player_sit_blue->get_initial_size());
		player_sit_blue->set_position_dst({ 40,240 });
		player_sit_blue->set_music_clicked(instance->find_audio("click_button"));
		button_list.emplace_back(player_sit_blue);
	}
	{
		SDL_Texture* player_sit_green_idle = instance->find_texture("player_sit_green_idle");
		Button* player_sit_green = new Button(player_sit_green_idle, nullptr, nullptr);
		player_sit_green->set_size_src(player_sit_green->get_initial_size());
		player_sit_green->set_position_dst({ 1088,240 });
		player_sit_green->set_music_clicked(instance->find_audio("click_button"));
		button_list.emplace_back(player_sit_green);
	}
	{
		SDL_Texture* player_sit_orange_idle = instance->find_texture("player_sit_orange_idle");
		Button* player_sit_orange = new Button(player_sit_orange_idle, nullptr, nullptr);
		player_sit_orange->set_size_src(player_sit_orange->get_initial_size());
		player_sit_orange->set_position_dst({ 1088,563 });
		player_sit_orange->set_music_clicked(instance->find_audio("click_button"));
		button_list.emplace_back(player_sit_orange);
	}
	{
		SDL_Texture* player_sit_purple_idle = instance->find_texture("player_sit_purple_idle");
		Button* player_sit_purple = new Button(player_sit_purple_idle, nullptr, nullptr);
		player_sit_purple->set_size_src(player_sit_purple->get_initial_size());
		player_sit_purple->set_position_dst({ 1088,400 });
		player_sit_purple->set_music_clicked(instance->find_audio("click_button"));
		button_list.emplace_back(player_sit_purple);
	}
	{
		SDL_Texture* player_sit_red_idle = instance->find_texture("player_sit_red_idle");
		Button* player_sit_red = new Button(player_sit_red_idle, nullptr, nullptr);
		player_sit_red->set_size_src(player_sit_red->get_initial_size());
		player_sit_red->set_position_dst({ 40,563 });
		player_sit_red->set_music_clicked(instance->find_audio("click_button"));
		button_list.emplace_back(player_sit_red);
	}
	{
		SDL_Texture* player_sit_yellow_idle = instance->find_texture("player_sit_yellow_idle");
		Button* player_sit_yellow = new Button(player_sit_yellow_idle, nullptr, nullptr);
		player_sit_yellow->set_size_src(player_sit_yellow->get_initial_size());
		player_sit_yellow->set_position_dst({ 40,400 });
		player_sit_yellow->set_music_clicked(instance->find_audio("click_button"));
		button_list.emplace_back(player_sit_yellow);
	}
	{
		SDL_Texture* visitor_sit_idle = instance->find_texture("visitor_sit_idle");
		Button* visitor_sit = new Button(visitor_sit_idle, nullptr, nullptr);
		visitor_sit->set_size_src(visitor_sit->get_initial_size());
		visitor_sit->set_position_dst({ 232,776 });
		visitor_sit->set_music_clicked(instance->find_audio("click_button"));
		button_list.emplace_back(visitor_sit);
	}

	{
		SecondScreen* second_home_screen = new SecondScreen("second_home_screen");
		second_home_screen->set_position({ 224,204 });
		{
			SDL_Rect rect_src = { 0,0,848,556 };
			SDL_Rect rect_dst = { 0 + second_home_screen->get_position().x,0 + second_home_screen->get_position().y,848,556 };
			Image* second_home_background = new Image(instance->find_texture("second_home_background"), rect_src, rect_dst);
			second_home_screen->set_image(second_home_background);
		}
		second_screen_list.emplace_back(second_home_screen);
	}
}

void HomeScreen::on_update(float delta)
{
	const std::string str_address = ConfigHomeManager::instance()->get_address();
}

void HomeScreen::do_post(float delta)
{
	ConfigGameManager::instance()->server.Post("hello",
		[&](const httplib::Request& req, httplib::Response& res)
		{
			std::cout << "hello from client" << std::endl;

			res.set_content("hello from server", "text/plain");
		});

	//加入房间 传入string player_id，传出string order
	ConfigGameManager::instance()->server.Post("join",
		[&](const httplib::Request& req, httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(mutex_join_or_switch);
			std::string player_id = req.body;
			ConfigHomeManager* instance = ConfigHomeManager::instance();

			int order = instance->get_num_player() - 1;
			if (instance->get_num_player() >= instance->get_max_num_player())
			{
				instance->add_num_visitor();
				order = instance->get_max_num_player() + instance->get_num_visitor();
			}
			if (player_id.empty())
				order = -1;
			for (Player* player : instance->get_player_list())
			{
				if (player->get_player_id() == player_id)
				{
					order = -1;
					break;
				}
			}
			res.set_content(std::to_string(order), "text/plain");
			if (order != -1)
			{
				Player* player = new Player();
				player->set_order(order);
				player->set_player_id(player_id);
				instance->add_player_in_list(player);
			}
		});

	//获取玩家列表并且记录时间一次（心跳） 传入需要的string order，传出json player_list[order](player_id,(identity, team_type))
	ConfigGameManager::instance()->server.Post("get_player_list",
		[&](const httplib::Request& req, httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(mutex_get_player_list);
			int order = std::stoi(req.body);
			ConfigHomeManager* instance = ConfigHomeManager::instance();
			int identity = 0;
			int team_type = 0;
			int identity_and_team_type = 0;
			std::string player_id;
			for (Player* player : instance->get_player_list())
			{
				if (player->get_order() == order)
				{
					player_id = player->get_player_id();
					identity = (int)player->get_identity();
					team_type = (int)player->get_team_type();
					int identity_and_team_type = identity * 10 + team_type;
					player->set_last_time_hearted(delta);
					break;
				}
			}
			const std::string str_player = write_cJSON_string_and_int(player_id, identity_and_team_type);
			res.set_content(str_player, "application/json");

		});

	//更换位置 传入json (player_id,team_type) 传出 string order
	ConfigGameManager::instance()->server.Post("switch_seat",
		[&](const httplib::Request& req, httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(mutex_join_or_switch);
			ConfigHomeManager* instance = ConfigHomeManager::instance();
			const std::string str_json = req.body;
			const std::string player_id;
			int order = -2;
			int team_type = 0;
			parse_cJSON_string_and_int(str_json, player_id, team_type);
			for (Player* player : instance->get_player_list())
			{
				if (player->get_team_type() == (TeamType)team_type)
				{
					order = -2;
					goto end;
				}
			}
			for (Player* player : instance->get_player_list())
			{
				if (player->get_player_id() == player_id)
				{
					player->set_team_type((TeamType)team_type);
					order = player->get_order();
					break;
				}
			}
		end:
			res.set_content(std::to_string(order), "text/plain");
		});

	//获取玩家（包括观战）人数
	ConfigGameManager::instance()->server.Post("get_all_player_num",
		[&](const httplib::Request& req, httplib::Response& res)
		{
			int num_player = ConfigHomeManager::instance()->get_num_player();
			res.set_content(std::to_string(num_player), "text/plain");
		});
}

void HomeScreen::handle_quit()
{
	ConfigHomeManager* instance = ConfigHomeManager::instance();
	for (Player* player : instance->get_player_list())
	{
		if (player->get_is_time_out())
		{
			instance->remove_player_in_list(player->get_player_id());
		}
	}
}