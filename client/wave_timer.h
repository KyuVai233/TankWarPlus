#pragma once

#include "wave_manager.h"

#include <functional>

class WaveTimer
{
public:
	WaveTimer() = default;
	~WaveTimer() = default;

	void restart()
	{
		final_wave = WaveManager::instance()->get_current_wave() + wait_wave;
		shotted = false;
	}

	void set_wait_wave(float val)
	{
		wait_wave = val;
	}

	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}

	void set_on_timeout(std::function<void()> on_timeout)
	{
		this->on_timeout = on_timeout;
	}

	void pause()
	{
		paused = true;
	}

	void resume()
	{
		paused = true;
	}

	int get_remaining_wave() const
	{
		return final_wave - WaveManager::instance()->get_current_wave();
	}

	void on_update()
	{
		if (paused)	return;

		if (WaveManager::instance()->get_current_wave() >= final_wave)
		{
			bool can_shot = (!one_shot || (one_shot && !shotted));
			shotted = true;
			if (can_shot && on_timeout)
				on_timeout();

			final_wave += wait_wave;
		}
	}

private:
	int wait_wave = 0;					//���μ�ʱ��������������
	int final_wave = 0;					//����ʱ����
	bool paused = false;				//�Ƿ���ͣ
	bool shotted = false;				//�Ƿ��������
	bool one_shot = false;				//�Ƿ񵥴δ���
	std::function<void()> on_timeout;	//����ִ�к���
};
