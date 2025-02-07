#pragma once

#include "manager.h"
#include "player.h"

#include "../thirdparty/httplib.h"

class ConfigGameManager : public Manager<ConfigGameManager>
{
	friend class Manager<ConfigGameManager>;

public:
	httplib::Client* client = nullptr;			//�ͻ���
	httplib::Server server;

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
		player = new Player();
	}

	~ConfigGameManager()
	{
	}

private:
	const int MAX_TANK_SPEED = 12;				//̹������ٶ�

	Player* player = nullptr;					//���
	
};
