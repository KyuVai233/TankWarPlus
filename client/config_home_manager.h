#pragma once

#include "manager.h"
#include "game_mode.h"
#include "player.h"

#include <vector>

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

	void on_update(float delta);

protected:
	ConfigHomeManager()
	{
	}

	~ConfigHomeManager() = default;

private:
	int idx_game_mode = 0;					

	GameMode* current_game_mode = nullptr;
	std::vector<GameMode*> game_mode_list;
	std::vector<Player*> player_list;
};
