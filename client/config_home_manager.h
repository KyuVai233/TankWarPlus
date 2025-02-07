#pragma once

#include "manager.h"
#include "game_mode.h"
#include "config_game_manager.h"
#include "player.h"

#include <vector>
#include <string>

class ConfigHomeManager : public Manager<ConfigHomeManager>
{
	friend class Manager<ConfigHomeManager>;

public:
	//下一个游戏模式
	void next_game_mode()
	{
		if (game_mode_list.size() <= 1)	return;
		idx_game_mode = (idx_game_mode + game_mode_list.size() + 1) % (game_mode_list.size());
	}

	//上一个游戏模式
	void last_game_mode()
	{
		if (game_mode_list.size() <= 1)	return;
		idx_game_mode = (idx_game_mode + game_mode_list.size() - 1) % (game_mode_list.size());
	}

	const std::string& get_game_mode_name() const
	{
		return game_mode_list[idx_game_mode]->game_mode_name;
	}

	int get_player_num() const
	{
		return player_list.size();
	}

	const int get_max_player_num() const
	{
		return game_mode_list[idx_game_mode]->MAX_PLAYER_NUM;
	}
	
	const int get_mim_player_num() const
	{
		return game_mode_list[idx_game_mode]->MIN_PLAYER_NUM;
	}

	void set_ip(const std::string& ip)
	{
		this->ip = ip;
	}

	const std::string& get_ip() const
	{
		return ip;
	}

	void set_home_name(const std::string& home_name)
	{
		this->home_name = home_name;
	}

	const std::string& get_home_name() const
	{
		return home_name;
	}

	void set_port(int port)
	{
		this->port = port;
	}

	int get_port() const
	{
		return port;
	}

	Player* get_action_player() const
	{
		return player_list[idx_player];
	}

	std::vector<Player*> get_player_list() const
	{
		return player_list;
	}

	void add_player_in_list(Player* player)
	{
		player_list.emplace_back(player);
	}

	void remove_player_in_list(const std::string& player_id)
	{
		player_list.erase(std::remove_if(player_list.begin(), player_list.end(),
			[&](const Player* player)
			{
				bool can_remove = player->get_player_id() == player_id;
				if (can_remove)	delete player;
				return can_remove;
			}), player_list.end());
	}

	void add_idx_player()
	{
		idx_player++;
		if (idx_player >= player_list.size())
			idx_player = 0;
	}

	const std::string& get_address() const
	{
		return (ip + ":" + std::to_string(port));
	}

	void on_update(float delta)
	{

	}

protected:
	ConfigHomeManager()
	{
		player_list.emplace_back(ConfigGameManager::instance()->get_player());
	}

	~ConfigHomeManager() = default;

private:
	int idx_game_mode = 0;					

	GameMode* current_game_mode = nullptr;
	std::vector<GameMode*> game_mode_list;
	std::vector<Player*> player_list;
	int idx_player = 0;							//当前行动玩家

	std::string home_name;						//房间名
	std::string ip;								//ip
	int port;									//端口
};
