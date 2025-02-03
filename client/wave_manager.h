#pragma once

#include "manager.h"

class WaveManager : public Manager<WaveManager>
{
	friend class Manager<WaveManager>;

public:
	int get_current_wave() const
	{
		return current_wave;
	}

	void add_current_wave()
	{
		current_wave++;
	}

	void restart()
	{
		current_wave = 0;
	}

	void on_update()
	{

	}

protected:
	WaveManager() = default;
	~WaveManager() = default;

private:
	int current_wave = 0;
};
