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

static FVector2 WINDOW_SIZE{0.f, 0.f};