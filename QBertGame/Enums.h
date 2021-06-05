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

enum class EObserverEvents
{
	CoilyDeath = 0,
	SlickSamDeath = 1,
	RemainingDisc = 2,
	Colorchange = 3,
};

enum class EGameModes
{
	Single = 0,
	Versus = 1,
	Coop = 2,
};

enum class ESounds
{
	QBertJump = 0,
	CoilyJump = 1,
	UggSpawn = 2,
	WrongwaySpawn = 3,
};