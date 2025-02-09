#include "home_screen.h"

void HomeScreen::on_update(float delta)
{
	const std::string str_address = ConfigHomeManager::instance()->get_address();
}

void HomeScreen::do_post(float delta)
{
	//���뷿�� ����string player_id������string order
	ConfigGameManager::instance()->server.Post("/join",
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
			res.set_content(std::to_string(order), "text/plain");
			if (order == -1)
				return;
			Player* player = new Player();
			player->set_order(order);
			player->set_player_id(player_id);
			instance->add_player_in_list(player);
		});

	//��ȡ����б��Ҽ�¼ʱ��һ�Σ������� ������Ҫ��string order������json player_list[order](player_id,(identity,team_type))
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

	//����λ�� ����json (player_id,team_type) ���� string order
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

	//��ȡ��ң�������ս������
	ConfigGameManager::instance()->server.Post("get_all_player_num",
		[&](const httplib::Request& req, httplib::Response& res)
		{
			int num_player = ConfigHomeManager::instance()->get_num_player();
			res.set_content(std::to_string(num_player), "text/plain");
		});
}

void HomeScreen::to_post()
{

}