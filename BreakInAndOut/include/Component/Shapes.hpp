#pragma once
#include "raylib.h"

namespace Component {
	struct CircleShape
	{
		float radius;
		Color color = RED;

		void draw(const Vector2& position) const
		{
			DrawCircleV(position, radius, color);
		}
	};

	struct RectangleShape
	{
		Vector2 size;
		Color color = WHITE;

		void draw(const Vector2& position) const
		{
			DrawRectangleV(position, size, color);
		}
	};
};