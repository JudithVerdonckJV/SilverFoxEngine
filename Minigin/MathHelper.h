#pragma once

template<typename T>
inline T Clamp(T value, T min, T max)
{
	if (value < min) return min;
	else if (value > max) return max;
	else return value;
}

template<typename T>
bool EqualWithEpsilon(T value, T equalTo, T range)
{
	return value + range >= equalTo && value - range <= equalTo;
}

inline bool IsPointInsideRect(const FVector2& point, const FVector2& leftBottom, const FVector2& dimensions)
{
	return point.x > leftBottom.x && point.x < leftBottom.x + dimensions.x &&
		   point.y > leftBottom.y && point.x < leftBottom.y + dimensions.y;
}