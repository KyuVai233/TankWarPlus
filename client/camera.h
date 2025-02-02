#pragma once

#include "time_timer.h"
#include "vector2.h"

class Camera
{
public:
	Camera();
	~Camera() = default;

	void reset();

	const Vector2& get_position() const
	{
		return position;
	}

	void on_update(float delta);

	void shake(float strength, float duration);

private:
	Vector2 position;				//λ��
	TimeTimer timer_shake;			//�𶯼�ʱ��
	bool is_shaking = false;		//�Ƿ���
	float shaking_strength = 0;		//��ǿ�ȣ�0 - 1��
};
