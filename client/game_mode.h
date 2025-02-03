#pragma once

#include <string>

class GameMode
{
public:
	GameMode() = delete;
	GameMode(const std::string game_mode_name, int max_val, int min_val)
		:game_mode_name(game_mode_name), MAX_PLAYER_NUM(max_val),  MIN_PLAYER_NUM(min_val)
	{ }

	~GameMode() = default;

public:
	const std::string game_mode_name;
	const int MAX_PLAYER_NUM;
	const int MIN_PLAYER_NUM;
};
