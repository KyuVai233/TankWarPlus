#pragma once

#include <functional>

class TimeTimer
{
public:
	TimeTimer() = default;
	~TimeTimer() = default;

	void restart()
	{
		pass_time = 0;
		shotted = false;
	}

	void set_wait_time(float val)
	{
		wait_time = val;
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

	void on_update(float delta)
	{
		if (paused)	return;

		pass_time += delta;
		if (pass_time >= wait_time)
		{
			bool can_shot = (!one_shot || (one_shot && !shotted));
			shotted = true;
			if (can_shot && on_timeout)
				on_timeout();

			pass_time -= wait_time;
		}
	}

private:
	float pass_time = 0;				//��ǰ�ѹ�ȥʱ��
	float wait_time = 0;				//ʱ���ʱ������ʱ��
	bool paused = false;				//�Ƿ���ͣ
	bool shotted = false;				//�Ƿ�������ɹ�
	bool one_shot = false;				//�Ƿ񵥴δ���
	std::function<void()> on_timeout;	//����ִ�к���
};
