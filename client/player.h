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
		GamePlayer,				//�������
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

	void set_team(const TeamType& team)
	{
		this->team = team;
	}

	void end_the_round()
	{
		tank->set_num_action(tank->get_current_speed());
	}

private:
	std::string player_id;						//���id
	Identity identity = Identity::None;			//���
	Tank* tank = nullptr;						//ѡ���tank
	int order = -1;								//���뷿����ţ�-2��ʾû����
	TeamType team = TeamType::Blue;				//����
};
