#pragma once

#include "tank.h"
#include "team_type.h"

class Player
{
public:
	//������
	enum class Identity
	{
		None,					//��
		Owner,					//����
		Player,					//�������
		Visitor					//��ս���
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
	std::string player_id;						//���id
	Identity identity = Identity::None;			//���
	Tank* tank = nullptr;						//ѡ���tank
	int order = -1;								//0��ʼ
	/*
	error
	-1 û���ֻ������ظ�
	-2 �������ʧ��
	*/
	TeamType team = TeamType::Blue;				//����

	float last_time_hearted;					//�������ʱ��
	bool is_time_out = false;					//�Ƿ�ʱ
	const float MAX_TIME_OUT = 10000.0f;		//���ʱʱ��(ms)
};
