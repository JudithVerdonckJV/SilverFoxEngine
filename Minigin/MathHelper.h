#pragma once

template<typename T>
inline T Clamp(T value, T min, T max)
{
	if (value < min) return min;
	else if (value > max) return max;
	else return value;
}