#pragma once

#include <cmath>

class Vector2
{
public:
	float x = 0;
	float y = 0;

public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y)
		: x(x), y(y) { }

	Vector2 operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	void operator+=(const Vector2& vec)
	{
		x += vec.x, y += vec.y;
	}

	Vector2 operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	void operator-=(const Vector2& vec)
	{
		x -= vec.x, y -= vec.y;
	}

	float operator*(const Vector2& vec) const
	{
		return x * vec.x + y * vec.y;
	}

	Vector2 operator*(float val) const
	{
		return Vector2(x * val, y * val);
	}

	void operator*=(float val)
	{
		x *= val, y *= val;
	}

	bool operator==(const Vector2& vec) const
	{
		return x == vec.x && y == vec.y;
	}

	bool operator>(const Vector2& vec) const
	{
		return length() > vec.length();
	}

	bool operator<(const Vector2& vec) const
	{
		return length() < vec.length();
	}

	//求模长
	float length() const
	{
		return sqrt(x * x + y * y);
	}

	//求单位向量
	Vector2 normalize() const
	{
		float len = length();

		if (len == 0)
			return Vector2(0, 0);

		return Vector2(x / len, y / len);
	}
};
