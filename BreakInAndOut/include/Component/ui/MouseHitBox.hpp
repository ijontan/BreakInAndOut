#pragma once

#include "raylib.h"
#include <functional>

namespace Component {
	struct MouseHitBox
	{
		Vector2 position;
		Vector2 size;
		std::function<void()> onClick;
		std::function<void()> onHoverEnter;
		std::function<void()> onHoverLeave;
		bool hovering = false;

		MouseHitBox(Vector2 pos, Vector2 sz,
			std::function<void()> onClick,
			std::function<void()> onHoverEnter = nullptr,
			std::function<void()> onHoverLeave = nullptr
		)
			: position(pos), size(sz), onClick(onClick), onHoverEnter(onHoverEnter), onHoverLeave(onHoverLeave) {
		}

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

		void checkOnHoverEnter()
		{
			if (isMouseOver() && !hovering)
			{
				hovering = true;
				if (onHoverEnter)
					onHoverEnter();
			}
		}

		void checkOnHoverLeave()
		{
			if (!isMouseOver() && hovering)
			{
				hovering = false;
				if (onHoverLeave)
					onHoverLeave();
			}
		}
	};
};