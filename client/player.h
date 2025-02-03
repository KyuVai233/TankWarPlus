#pragma once

#include "tank.h"

class Player
{
public:
	//玩家身份
	enum class Identity
	{
		Owner,					//房主
		GamePlayer,				//参与玩家
		Visitor,				//观战玩家
		None					//无
	};

public:
	Player()
	{
	}

	~Player()
	{
		if (!tank)	delete tank;
	}

	void set_player_id(const std::string& id)
	{
		this->player_id = player_id;
	}

	const std::string& get_player_id() const
	{
		return player_id;
	}

	void set_identity(const Identity& identity)
	{
		this->identity = identity;
	}

	const Identity& get_identity() const
	{
		return identity;
	}

	void choose_tank(Tank* tank)
	{
		this->tank = tank;
	}

	Tank* get_tank() const
	{
		return tank;
	}

	void set_order(int order)
	{
		this->order = order;
	}

	int get_order() const
	{
		return order;
	}

private:
	std::string player_id;		//玩家id
	Identity identity;			//身份
	Tank* tank = nullptr;		//选择的tank
	int order = -1;				//行动（座位）序号	

};
