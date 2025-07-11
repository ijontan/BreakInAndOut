#pragma once

#include "../utils/bezier.hpp"
#include "../utils/masking.hpp"

#include <cmath>
#include <algorithm>

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

	struct BlockState
	{
		BlockType type = NORMAL;
		GhostLayer layer = REAL;
		unsigned char targetOpacity = 255;
		unsigned char startOpacity = 255;
		float t = 1.0f;
		int health = 1;


		BlockState(BlockType type, GhostLayer layer, int health = 1)
			: type(type), layer(layer), targetOpacity(255), startOpacity(255), t(1.0f), health(health) {
		}

		void step(float deltaTime)
		{
			if (t < 1.0f)
			{
				t += deltaTime;
				if (t > 1.0f) t = 1.0f;
			}
		}

		void setColorTransition(unsigned char mask, unsigned char newStartOpacity)
		{
			startOpacity = newStartOpacity;
			if (!Utils::isBitSet(mask, layer))
			{
				int layerIndex = Utils::getBitIndex(layer);
				int selectedLayer = Utils::getBitIndex(Utils::clearBit(mask, Component::GhostLayer::REAL));
				auto diff = std::abs(layerIndex - selectedLayer);
				targetOpacity = std::clamp(70 - diff * 20, 0, 255);
			}
			else
				targetOpacity = 255;
			t = 0.0f;
		}
	};
};