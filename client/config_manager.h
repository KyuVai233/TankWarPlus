#pragma once

#include "manager.h"

class ConfigManager : public Manager<ConfigManager>
{
	friend class Manager<ConfigManager>;

public:
	int get_MAX_TANK_SPEED() const
	{
		return MAX_TANK_SPEED;
	}

protected:
	ConfigManager()
	{
	}

	~ConfigManager()
	{
	}

private:
	const int MAX_TANK_SPEED = 12;
};
