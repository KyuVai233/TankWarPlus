#pragma once

class Wave
{
public:
	static Wave* instance()
	{
		static Wave* instance;		// 静态局部变量，保证唯一性
		return instance;
	}

	int get_current_wave() const
	{
		return current_wave;
	}

	void restart();

protected:
	Wave() = default;
	~Wave() = default;

private:
	int current_wave = 0;			//当前波数
	int num_round = 0;				//当前波次回合数
	int num_action = 0;				//当前剩余行动次数
};
