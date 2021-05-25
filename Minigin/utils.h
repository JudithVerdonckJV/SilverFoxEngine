#pragma once

struct FVector2
{
	FVector2()
		: x{ 0.f }
		, y{ 0.f }
	{}

	FVector2(const float x, const float y)
		: x{ x }
		, y{ y }
	{}

	float x;
	float y;
};

struct IVector2
{
	IVector2()
		: x{ 0 }
		, y{ 0 }
	{}

	IVector2(const int x, const int y)
		: x{ x }
		, y{ y }
	{}

	int x;
	int y;
};