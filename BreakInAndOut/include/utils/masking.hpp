#pragma once

namespace Utils
{
	inline bool isBitSet(unsigned char mask, unsigned char bit)
	{
		return (mask & bit) != 0;
	}

	inline unsigned char setBit(unsigned char mask, unsigned char bit)
	{
		return mask | bit;
	}

	inline unsigned char clearBit(unsigned char mask, unsigned char bit)
	{
		return mask & ~bit;
	}

	inline unsigned char toggleBit(unsigned char mask, unsigned char bit)
	{
		return mask ^ bit;
	}

	inline unsigned int getBitIndex(unsigned char bit)
	{
		switch (bit)
		{
		case 1 << 0:
			return 0;
		case 1 << 1:
			return 1;
		case 1 << 2:
			return 2;
		case 1 << 3:
			return 3;
		case 1 << 4:
			return 4;
		case 1 << 5:
			return 5;
		case 1 << 6:
			return 6;
		case 1 << 7:
			return 7;
		default:
			return 0;
		}
	}
}
