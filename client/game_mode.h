#pragma once

#include <string>

class GameMode
{
public:
	GameMode() = delete;
	GameMode(const std::string game_mode_name, int max_val, int min_val)
		:game_mode_name(game_mode_name), MAX_NUM_PLAYER(max_val),  MIN_NUM_PLAYER(min_val)
	{ }

	~GameMode() = default;

public:
	const std::string game_mode_name;
	const int MAX_NUM_PLAYER;
	const int MIN_NUM_PLAYER;
};
