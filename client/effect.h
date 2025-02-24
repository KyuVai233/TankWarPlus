#pragma once

#include "wave_timer.h"

class EffectInvincibility
{
public:
	EffectInvincibility() = default;
	~EffectInvincibility() = default;

	void set_time(int wave)
	{
		timer.set_wait_wave(wave);
	}

	void set_one_shot(bool flag)
	{
		timer.set_one_shot(flag);
	}

	virtual void give_effect() = delete;

	void set_on_timeout(std::function<void()> on_timeout)
	{
		timer.set_on_timeout(on_timeout);
	}

	void pause()
	{
		timer.pause();
	}

	void resume()
	{
		timer.resume();
	}

	void restart()
	{
		timer.restart();
	}

	int get_remaining_wave() const
	{
		return timer.get_remaining_wave();
	}

private:
	WaveTimer timer;		//效果计时器
};
