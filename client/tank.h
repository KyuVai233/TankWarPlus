#pragma once

#include "animation.h"
#include "config_game_manager.h"
#include "status_machine.h"
#include "tank_status_node.h"
#include "wave_timer.h"
#include "vector2.h"

#include <SDL.h>

#include <functional>
#include <string>
#include <unordered_map>

class Tank
{
public:
	Tank() = default;

	~Tank() = default;

public:
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	/*
	* enum class TankStatus
	{
		Idle,				//����
		Run,				//�ƶ�
		Turn,				//ת��
		Fire,				//����
		Damaged,			//���ƻ�װ��
		Destoryed			//����
	};
	*/

	enum class TankType
	{
		Little,				//����̹��
		Medium,				//����̹��
		Large,				//����̹��
		Anti				//��̹��
	};

public:
	const int get_MAX_HP() const
	{
		return MAX_HP;
	}
	
	void add_hp(int val);

	void add_hp(double percentage);

	void decrease_hp(int val);

	void init_hp()
	{
		current_hp = MAX_HP;
	}

	int get_current_hp() const
	{
		return current_hp;
	}

	void set_speed(int val);

	void init_speed()
	{
		current_speed = INITIAL_SPEED;
	}

	int get_current_speed() const
	{
		return current_speed;
	}

	void add_num_actioned()
	{
		num_actioned++;
	}

	int get_num_actioned() const
	{
		return num_actioned;
	}

	void set_num_action(int val)
	{
		num_actioned = val;
	}

	void add_attack_power(int val)
	{
		current_attack_power += val;
	}

	void add_attack_power(double percentage)
	{
		int val = (int)((percentage / 100) * current_attack_power);
		add_attack_power(val);
	}

	void decrease_attack_power(int val)
	{
		current_attack_power -= val;
	}

	void decrease_attack_power(double percentage)
	{
		int val = (int)((percentage / 100) * current_attack_power);
		decrease_attack_power(val);
	}

	void init_attack_power()
	{
		current_attack_power = INITIAL_ATTACK_POWER;
	}

	int get_current_attack_power() const
	{
		return current_attack_power;
	}

	//����
	virtual void on_fire();

	//װ���ӵ�����ʱ���ص����ã�
	void reload_ammo();

	const int get_MAX_AMMO_NUM() const
	{
		return MAX_AMMO_NUM;
	}

	int get_num_ammo() const
	{
		return num_ammo;
	}

	const int get_INITIAL_VISIBLE_RANGE() const
	{
		return INITIAL_VISIBLE_RANGE;
	}

	void set_visible_range(int val)
	{
		visible_range = val;
	}

	void init_visible_range()
	{
		visible_range = INITIAL_VISIBLE_RANGE;
	}

	int get_visible_range() const
	{
		return visible_range;
	}

	void set_position_in_map(int x, int y)
	{
		position_in_map = { x,y };
	}

	const SDL_Point& get_position_in_map() const
	{
		return position_in_map;
	}

	void set_is_invincible(bool flag)
	{
		is_invincible = flag;
	}

	void set_release_skill(std::function<void()> release_skill)
	{
		this->release_skill = release_skill;
	}

	void set_passive_skill(std::function<void()> passive_skill)
	{
		this->passive_skill = passive_skill;
	}

	void switch_direction(Direction dir)
	{
		direction = dir;
	}

	const TankType& get_tank_type() const
	{
		return tank_type;
	}

	void switch_status(const std::string& id)
	{
		status_machine.switch_status(id);
	}

	void set_animation(const std::string& id);
protected:

	struct AnimationGroup
	{
		Animation up;
		Animation down;
		Animation left;
		Animation right;
	};

protected:
	const int MAX_HP = 80;							//�������ֵ
	const int INITIAL_SPEED = 8;					//��ʼ�ٶ�
	const int INITIAL_ATTACK_POWER = 18;			//��ʼ������
	const int MAX_AMMO_NUM = 1;						//��󵯼���
	const int INITIAL_VISIBLE_RANGE = 8;			//�����Ұ��Χ

	int current_hp = 80;							//��ǰѪ��
	int current_speed = 8;							//��ǰ�ٶ�
	int num_actioned = 0;							//�Ѿ��ж��Ĵ���
	int current_attack_power = 18;					//��ǰ������
	int num_ammo = 1;								//��ǰ��ҩ����
	int visible_range = 8;							//��ǰ��Ұ��Χ

	SDL_Point position_in_map = { 0 };				//�ڵ�ͼ�е�λ�ã���Ƭ�����㣩

	bool is_invincible = false;						//�Ƿ��޵�
	bool is_visible = true;							//�Ƿ�ɼ�

	std::function<void()> release_skill;			//�������ܻص�
	std::function<void()> passive_skill;			//�������ܻص�

	WaveTimer timer_reload_ammo;					//װ�����μ�ʱ����һ����
	WaveTimer timer_active_skill;					//�������ܲ��μ�ʱ��
	WaveTimer timer_passive_skill;					//�������ܲ��μ�ʱ��

	Direction direction = Direction::Left;			//tank����
	TankType tank_type = TankType::Little;			//tank����
	StatusMachine status_machine;					//״̬��

	AnimationGroup* current_animation = nullptr;	//��ǰ����
	std::unordered_map<std::string, AnimationGroup> animaton_pool;
};
