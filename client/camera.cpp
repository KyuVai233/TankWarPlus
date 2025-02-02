#include "camera.h"

Camera::Camera()
{
	timer_shake.set_one_shot(true);
	timer_shake.set_on_timeout([&]()
		{
			is_shaking = false;
			reset();
		});
}

void Camera::reset()
{
	position.x = 0;
	position.y = 0;
}

void Camera::on_update(float delta)
{
	timer_shake.on_update(delta);

	if (is_shaking)
	{
		position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
		position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
	}
}

void Camera::shake(float strength, float duration)
{
	is_shaking = true;
	shaking_strength = strength;

	timer_shake.set_wait_time(duration);
	timer_shake.restart();
}