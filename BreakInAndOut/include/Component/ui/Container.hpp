#pragma once
#include "raylib.h"

namespace Component {
	struct Container {
		Vector2 position;
		Vector2 size;
		Color backgroundColor;

		Container(Vector2 pos, Vector2 sz, Color bgColor)
			: position(pos), size(sz), backgroundColor(bgColor) {}
		void draw() const {
			DrawRectangleV(position, size, backgroundColor);
		}
	};
}
