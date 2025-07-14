
#pragma once
#include "raylib.h"

namespace Component {
	struct Position
	{
		Vector2 position;

		operator const Vector2() const
		{
			return position;
		}

		operator Vector2& ()
		{
			return position;
		}
	};
};
