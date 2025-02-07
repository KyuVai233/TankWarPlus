#pragma once

class Wave
{
public:
	static Wave* instance()
	{
		static Wave* instance;		// ��̬�ֲ���������֤Ψһ��
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
	int current_wave = 0;			//��ǰ����
	int num_round = 0;				//��ǰ���λغ���
	int num_action = 0;				//��ǰʣ���ж�����
};
