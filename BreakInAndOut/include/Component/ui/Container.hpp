#pragma once
#include "raylib.h"
#include "raymath.h"

namespace Component {
	struct Container {
		Vector2 position;
		Vector2 size;
		Color backgroundColor;
		Color borderColor;

		Container(Vector2 pos, Vector2 sz, Color bgColor, Color borderColor = Color{ 0, 0, 0, 0 })
			: position(pos), size(sz), backgroundColor(bgColor), borderColor(borderColor) {}
		void draw(const Vector2& displacement) const {
			const Vector2 displacedPosition = Vector2Add(position, displacement);
			DrawRectangleV(displacedPosition, size, backgroundColor);
			DrawRectangleLinesEx(
				{ displacedPosition.x, displacedPosition.y, size.x, size.y },
				2.0f,
				borderColor
			);
		}
	};
}
