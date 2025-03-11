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

	void open_server()
	{
		is_on_server = true;
	}

	void close_server()
	{
		is_on_server = false;
	}

	bool get_is_on_server() const
	{
		return is_on_server;
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
	bool is_on_server = false;
};
