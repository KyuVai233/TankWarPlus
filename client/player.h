#pragma once

#include "tank.h"
#include "team_type.h"

class Player
{
public:
	//玩家身份
	enum class Identity
	{
		None,					//无
		Owner,					//房主
		Player,					//参与玩家
		Visitor					//观战玩家
	};

public:
	Player() = default;

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

	void set_team_type(const TeamType& team)
	{
		this->team = team;
	}

	const TeamType& get_team_type() const
	{
		return team;
	}

	void end_the_round()
	{
		tank->set_num_action(tank->get_current_speed());
	}

	void set_last_time_hearted(float val)
	{
		last_time_hearted = val;
	}

	float get_last_time_hearted() const
	{
		return last_time_hearted;
	}

	void set_is_time_out(bool flag)
	{
		is_time_out = flag;
	}

	bool get_is_time_out() const
	{
		return is_time_out;
	}

	const float get_MAX_TIME_OUT() const
	{
		return MAX_TIME_OUT;
	}

private:
	std::string player_id;						//玩家id
	Identity identity = Identity::None;			//身份
	Tank* tank = nullptr;						//选择的tank
	int order = -1;								//0开始
	/*
	error
	-1 没名字或名字重复
	-2 请求操作失败
	*/
	TeamType team = TeamType::Blue;				//队伍

	float last_time_hearted;					//最后心跳时间
	bool is_time_out = false;					//是否超时
	const float MAX_TIME_OUT = 10000.0f;		//最大超时时间(ms)
};
