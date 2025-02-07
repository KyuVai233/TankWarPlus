#pragma once

#include "manager.h"
#include "player.h"

#include "../thirdparty/httplib.h"

class ConfigGameManager : public Manager<ConfigGameManager>
{
	friend class Manager<ConfigGameManager>;

public:
	httplib::Client* client = nullptr;			//¿Í»§¶Ë
	httplib::Server server;

public:
	Player* get_player() const
	{
		return player;
	}

protected:
	ConfigGameManager()
	{
		player = new Player();
	}

	~ConfigGameManager()
	{
	}

private:
	Player* player = nullptr;					//Íæ¼Ò
	
};
