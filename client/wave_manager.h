#pragma once

#include "manager.h"
#include "config_home_manager.h"

class WaveManager : public Manager<WaveManager>
{
	friend class Manager<WaveManager>;

public:
	int get_current_wave() const
	{
		return current_wave;
	}

	void restart();

	void on_update(float delta);

protected:
	WaveManager() = default;

	~WaveManager() = default;

private:
	int current_wave = 0;			//��ǰ����
	int num_round = 0;				//��ǰ���λغ���
	int num_action = 0;				//��ǰʣ���ж�����
};
