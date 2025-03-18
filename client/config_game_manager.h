#pragma once

#include "manager.h"
#include "player.h"

#include "../thirdparty/httplib.h"

class ConfigGameManager : public Manager<ConfigGameManager>
{
	friend class Manager<ConfigGameManager>;

public:
	httplib::Client* client = nullptr;			//客户端
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

	void set_volume(float val)
	{
		volume = val;
	}

	float get_volume() const
	{
		return volume;
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
	Player* player = nullptr;					//玩家
	bool is_on_server = false;
	float volume = 50;							//音量（百分比）
};
