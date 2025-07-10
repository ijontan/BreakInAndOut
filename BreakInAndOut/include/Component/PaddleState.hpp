#pragma once
#include "raylib.h"

namespace Component
{
	struct PaddleState
	{
		int health = 3;
		Vector2 aimDirection = { 0.0f, 0.0f };
	};
};
