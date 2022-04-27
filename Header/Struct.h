#pragma once

typedef struct tagVector2
{
	float	x;
	float	y;
	tagVector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	tagVector2()
	{
		x = 0.f;
		y = 0.f;
	};
	tagVector2& operator +(tagVector2& vec2)
	{
		VECTOR2 vec;
		vec.x = this->x + vec2.x;
		vec.y = this->y + vec2.y;
		return vec;
	}

	tagVector2& operator +=(tagVector2& vec2)
	{
		this->x += vec2.x;
		this->y += vec2.y;
		return *this;
	}

	const POINT& To_Int()
	{
		POINT pt;
		pt.x = (int)x;
		pt.y = (int)y;

		return pt;
	}
}VECTOR2;

