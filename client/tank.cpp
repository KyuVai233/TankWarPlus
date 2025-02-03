#include "tank.h"

void Tank::add_hp(int val)
{
	current_hp += val;
	if (current_hp > MAX_HP)
		current_hp = MAX_HP;
}

void Tank::add_hp(double percentage)
{
	int val = (int)((percentage / 100) * MAX_HP);
	add_hp(val);
}

void Tank::decrease_hp(int val)
{
	if (!is_invincible)
		current_hp -= val;
}

void Tank::set_speed(int val)
{
	current_speed = val;
	ConfigHomeManager* instance = ConfigHomeManager::instance();
	if (current_speed < 0)
		current_speed = 0;
	else if (current_hp > instance->get_MAX_TANK_SPEED())
		current_speed = instance->get_MAX_TANK_SPEED();
}

void Tank::on_fire()
{
	if (num_ammo <= 0)	return;
	num_ammo--;
	timer_reload_ammo.restart();
}

void Tank::reload_ammo()
{
	num_ammo++;
	if (num_ammo >= MAX_AMMO_NUM)
		num_ammo = MAX_AMMO_NUM;
	else
		timer_reload_ammo.restart();
}

void Tank::set_animation(const std::string& id)
{
	current_animation = &animaton_pool[id];

	current_animation->up.reset();
	current_animation->down.reset();
	current_animation->left.reset();
	current_animation->right.reset();
}