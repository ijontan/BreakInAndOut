#pragma once
#include "raylib.h"

namespace Component {
	struct Velocity
	{
		Vector2 velocity;

		operator const Vector2() const
		{
			return velocity;
		}

		operator Vector2& ()
		{
			return velocity;
		}
	};
};
