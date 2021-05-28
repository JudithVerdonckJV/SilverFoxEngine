#pragma once
enum class EDirection
{
	DownRight = 0,
	DownLeft = 1,
	UpRight = 2,
	UpLeft = 3,
	Left = 4,
	Right = 5,
};

enum class ETileBehavior
{
	OneFlip = 0,
	TwoFlips = 1,
	CanUnflip = 2,
};

enum class ETileType
{
	Stage0 = 0,
	Stage1 = 1,
	Stage2 = 2,
};