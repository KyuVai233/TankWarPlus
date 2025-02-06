#pragma once

#include "manager.h"
#include "player.h"

class ConfigGameManager : public Manager<ConfigGameManager>
{
	friend class Manager<ConfigGameManager>;

public:
	int get_MAX_TANK_SPEED() const
	{
		return MAX_TANK_SPEED;
	}

	Player* get_player() const
	{
		return player;
	}

protected:
	ConfigGameManager()
	{
	}

	~ConfigGameManager()
	{
	}

private:
	const int MAX_TANK_SPEED = 12;				//坦克最大速度

	Player* player = nullptr;					//玩家

};
