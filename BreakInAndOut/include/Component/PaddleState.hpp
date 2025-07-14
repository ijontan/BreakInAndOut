#pragma once
#include "raylib.h"

namespace Component
{
	struct PaddleState
	{
		int health = 3;
		bool started = false;
		Vector2 aimDirection = { 0.0f, -1.0f };
		float angle = 0;
	};
};
