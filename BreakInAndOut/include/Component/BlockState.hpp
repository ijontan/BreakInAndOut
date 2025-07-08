#pragma once


namespace Component
{
	enum BlockType
	{
		NORMAL,
		WALL,
		BALLOON,
		SPIKES
	};

	enum GhostLayer
	{
		REAL = 1 << 0,
		ONE = 1 << 1,
		TWO = 1 << 2,
		THREE = 1 << 3,
		FOUR = 1 << 4,
		FIVE = 1 << 5,
		SIX = 1 << 6,
		SEVEN = 1 << 7,
	};

	struct Block
	{
		BlockType type = NORMAL;
		GhostLayer layer = REAL;
		int health = 1;
	}
}