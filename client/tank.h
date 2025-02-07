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
		Idle,				//闲置
		Run,				//移动
		Turn,				//转向
		Fire,				//开火
		Damaged,			//被破坏装置
		Destoryed			//被损坏
	};
	*/

	enum class TankType
	{
		Little,				//轻型坦克
		Medium,				//中型坦克
		Large,				//重型坦克
		Anti				//反坦克
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

	//开火
	virtual void on_fire();

	//装填子弹（计时器回调调用）
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
	const int MAX_HP = 80;							//最大生命值
	const int INITIAL_SPEED = 8;					//初始速度
	const int INITIAL_ATTACK_POWER = 18;			//初始攻击力
	const int MAX_AMMO_NUM = 1;						//最大弹夹量
	const int INITIAL_VISIBLE_RANGE = 8;			//最大视野范围

	int current_hp = 80;							//当前血量
	int current_speed = 8;							//当前速度
	int num_actioned = 0;							//已经行动的次数
	int current_attack_power = 18;					//当前攻击力
	int num_ammo = 1;								//当前弹药数量
	int visible_range = 8;							//当前视野范围

	SDL_Point position_in_map = { 0 };				//在地图中的位置（瓦片数量算）

	bool is_invincible = false;						//是否无敌
	bool is_visible = true;							//是否可见

	std::function<void()> release_skill;			//主动技能回调
	std::function<void()> passive_skill;			//被动技能回调

	WaveTimer timer_reload_ammo;					//装弹波次计时器（一发）
	WaveTimer timer_active_skill;					//主动技能波次计时器
	WaveTimer timer_passive_skill;					//被动技能波次计时器

	Direction direction = Direction::Left;			//tank方向
	TankType tank_type = TankType::Little;			//tank类型
	StatusMachine status_machine;					//状态机

	AnimationGroup* current_animation = nullptr;	//当前动画
	std::unordered_map<std::string, AnimationGroup> animaton_pool;
};
