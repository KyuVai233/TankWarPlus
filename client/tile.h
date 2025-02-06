#pragma once

#include "team_type.h"

#include <SDL.h>

class Tile
{
public:
	Tile() = default;

	~Tile() = default;

	void set_team_visible(TeamType team, bool is_visible);

	void set_have_tank(bool have_tank)
	{
		this->have_tank = have_tank;
	}

	bool get_have_tank() const
	{
		return have_tank;
	}

	virtual void on_tile_effect() { }

	virtual void on_update(float delta) { }

	virtual void on_render(SDL_Renderer* renderer, TeamType team) { }

private:
	struct TeamVisible
	{
		bool BlueVisible = false;
		bool RedVisible = false;
		bool YellowVisible = false;
		bool GreenVisible = false;
		bool PinkVisible = false;
		bool OrangeVisible = false;
	};

private:
	TeamVisible team_visible;			//队伍可见列表
	int tile_type = 0;					//瓦片类型

	bool have_tank = false;				//是否有坦克
	bool have_ammo = false;				//是否有导弹
	bool can_tank_move = true;			//坦克能否移动
	bool can_ammo_move = true;			//子弹能否穿过
};
