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
	Vector2 position;				//位置
	TimeTimer timer_shake;			//震动计时器
	bool is_shaking = false;		//是否震动
	float shaking_strength = 0;		//震动强度（0 - 1）
};
