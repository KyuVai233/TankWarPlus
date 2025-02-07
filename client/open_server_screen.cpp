#include "open_server_screen.h"

void OpenServerScreen::to_post()
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
	if (order == -2)
	{
		//名字未定义
		return;
	}
	instance->get_player()->set_order(order);

	for (int i = 0; i < order; i++)
	{
		Player* player = new Player();
		httplib::Result result_get_player_list = instance->client->Post("get_player_list",
			std::to_string(i), "text/plain");
		if (!result_get_player_list || result_get_player_list != 200)
		{
			//未连接到服务器
			return;
		}
		const std::string& str_player = result_get_player_list->body;
		std::string player_id;
		int identity = 0;
		parse_get_player_list(str_player, player_id, identity);
		player->set_player_id(player_id);
		player->set_identity((Player::Identity)identity);
	}
}