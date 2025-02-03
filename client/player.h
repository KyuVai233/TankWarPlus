#pragma once

#include "tank.h"

class Player
{
public:
	//������
	enum class Identity
	{
		Owner,					//����
		GamePlayer,				//�������
		Visitor,				//��ս���
		None					//��
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
	std::string player_id;		//���id
	Identity identity;			//���
	Tank* tank = nullptr;		//ѡ���tank
	int order = -1;				//�ж�����λ�����	

};
