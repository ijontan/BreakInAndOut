#pragma once
#include "raylib.h"

namespace Component {
	struct CircleShape
	{
		float radius;
		Color color = WHITE;

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

		void draw(const Vector2& position, Color color) const
		{
			DrawRectangleV(position, size, color);
		}

		void drawOutline(const Vector2& position, float lineThickness = 2.0f, Color color = WHITE) const
		{
			DrawRectangleLinesEx({ position.x, position.y, size.x, size.y }, lineThickness, color);
		}
	};
};