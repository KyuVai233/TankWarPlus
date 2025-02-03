#include "status_machine.h"

void StatusMachine::on_update(float delta)
{
	if (!current_status)	return;

	if (need_init)
	{
		current_status->on_enter();
		need_init = false;
	}

	current_status->on_update(delta);
}

void StatusMachine::set_entry(const std::string& id)
{
	current_status = status_pool[id];
}

void StatusMachine::switch_status(const std::string& id)
{
	current_status->on_exit();
	current_status = status_pool[id];
	current_status->on_enter();
}

void StatusMachine::register_status(const std::string& id, StatusNode* status_node)
{
	status_pool[id] = status_node;
}