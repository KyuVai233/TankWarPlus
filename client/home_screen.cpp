#include "home_screen.h"

void HomeScreen::do_post()
{
	//传入string player_id，传出string order
	ConfigGameManager::instance()->server.Post("/join",
		[&](const httplib::Request& req, httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(mutex_join);
			std::string player_id = req.body;
			ConfigHomeManager* instance = ConfigHomeManager::instance();
			int order = instance->get_player_num();
			if (instance->get_player_num() >= instance->get_max_player_num())
				order = -1;
			if (player_id.empty())
				order = -2;
			res.set_content(std::to_string(order), "text/plain");
			if (order == -2)
				return;
			Player* player = new Player();
			player->set_order(order);
			player->set_player_id(player_id);
			
		});

	//传入需要的string order，传出json player_list[order](player_id,identity)
	ConfigGameManager::instance()->server.Post("get_player_list",
		[&](const httplib::Request& req, httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(mutex_get_player_list);
			int order = std::stoi(req.body);
			ConfigHomeManager* instance = ConfigHomeManager::instance();
			int identity = 0;
			std::string player_id;
			for (Player* player : instance->get_player_list())
			{
				if (player->get_order() == order)
				{
					player_id = player->get_player_id();
					identity = (int)player->get_identity();
					break;
				}
			}
			const std::string str_player = write_get_player_list(player_id, identity);
			res.set_content(str_player, "application/json");

		});
}