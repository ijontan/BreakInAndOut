#pragma once

#include "raylib.h"

namespace Component {
	struct Text
	{
		Vector2 position;
		std::string text;
		Color color;
		int fontSize;

		Text(Vector2 pos, const std::string& txt, Color col, int size)
			: position(pos), text(txt), color(col), fontSize(size) {}

		void draw() const
		{
			DrawText(text.c_str(), static_cast<int>(position.x), static_cast<int>(position.y), fontSize, color);
		}
	};
}