#include "wave_manager.h"

void WaveManager::restart()
{
	current_wave = 0;
	num_round = 0;
	num_action = 0;
}

void WaveManager::on_update(float delta)
{
	Tank* tank = ConfigHomeManager::instance()->get_action_player()->get_tank();

	num_action = tank->get_num_actioned();
	if (num_action >= tank->get_current_speed())
	{
		num_action = 0;
		num_round++;
		tank->set_num_action(0);
	}

	int num_player = ConfigHomeManager::instance()->get_player_num();
	if (num_round >= num_player)
	{
		num_round = 0;
		current_wave++;
	}
}