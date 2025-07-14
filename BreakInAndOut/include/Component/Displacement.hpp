
#pragma once
#include "raylib.h"
#include <cmath>
#include <raymath.h>

namespace Component {
	struct Displacement
	{
		Vector2 displacement = { 0.0f, 0.0f };
		Vector2 from = { 0.0f, 0.0f };


		Displacement(const Vector2& position)
		{
			const float screenWidth = GetScreenWidth();
			const float screenheight = GetScreenHeight();
			const float magnitude = std::sqrt(screenWidth * screenWidth + screenheight * screenheight);
			const Vector2 direction = Vector2Normalize(Vector2{ position.x - screenWidth * 0.5f, position.y - screenheight * 0.5f });

			from = Vector2Scale(direction, magnitude);
		}

		operator const Vector2() const
		{
			return displacement;
		}

		operator Vector2& ()
		{
			return displacement;
		}
	};
};
