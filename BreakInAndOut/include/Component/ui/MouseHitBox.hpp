#pragma once

#include "raylib.h"
#include <functional>

namespace Component {
	struct MouseHitBox
	{
		Vector2 position;
		Vector2 size;
		std::function<void()> onClick;

		MouseHitBox(Vector2 pos, Vector2 sz, std::function<void()> onClick)
			: position(pos), size(sz), onClick(onClick) {}

		bool isMouseOver() const
		{
			Vector2 mousePos = GetMousePosition();
			return (mousePos.x >= position.x && mousePos.x <= position.x + size.x &&
					mousePos.y >= position.y && mousePos.y <= position.y + size.y);
		}

		void checkClick() const
		{
			if (!isMouseOver())
				return;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && onClick)
				onClick();
		}
	};
}