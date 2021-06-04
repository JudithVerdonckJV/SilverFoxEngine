#pragma once
#include <math.h>

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

	float Magnitude() const noexcept
	{
		return std::sqrtf(x * x + y * y);
	}

	float MagnitudeSquared() const noexcept
	{
		return x * x + y * y;
	}

	void Normalize()
	{
		float length = Magnitude();

#ifdef _DEBUG
		if (length <= 0.f)
		{
			std::cout << "FVector2 Normalize: magnitude invalid, vector not normalized!\n";
			return;
		}
#endif
		*this /= length;
	}

	//FVector2 with FVector2
	FVector2 operator+(const FVector2& other) const
	{
		return FVector2{ x + other.x, y + other.y };
	}

	FVector2& operator+=(const FVector2& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	FVector2 operator-(const FVector2& other) const
	{
		return *this + FVector2{-other.x, -other.y};
	}

	FVector2& operator-=(const FVector2& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	bool operator>(const FVector2& other) const
	{
		return x > other.x && y > other.y;
	}

	bool operator>=(const FVector2& other) const
	{
		return x >= other.x && y >= other.y;
	}

	bool operator<(FVector2& other) const
	{
		return other > *this;
	}

	bool operator<=(FVector2& other) const
	{
		return other >= *this;
	}

	//FVector2 with floats
	FVector2 operator+(const float other) const
	{
		return FVector2{ x + other, y + other };
	}

	FVector2& operator+=(const float other)
	{
		this->x += other;
		this->y += other;
		return *this;
	}

	FVector2 operator-(const float other) const
	{
		return FVector2{ x - other, y - other };
	}

	FVector2& operator-=(const float other)
	{
		this->x -= other;
		this->y -= other;
		return *this;
	}

	FVector2 operator/(const float other) const
	{
		return FVector2{ x / other, y / other };
	}

	FVector2& operator/=(const float other)
	{
		this->x /= other;
		this->y /= other;
		return *this;
	}

	FVector2 operator*(const float other) const
	{
		return FVector2{ x * other, y * other };
	}

	FVector2& operator*=(const float other)
	{
		this->x *= other;
		this->y *= other;
		return *this;
	}

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