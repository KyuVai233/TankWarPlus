#pragma once

#include "manager.h"

class ConfigGameManager : public Manager<ConfigGameManager>
{
	friend class Manager<ConfigGameManager>;

public:
	int get_MAX_TANK_SPEED() const
	{
		return MAX_TANK_SPEED;
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
};
