#pragma once
#include "../Component/CollisionBox.hpp"

namespace Utils
{
	bool checkCollision(const Vector2& ballPos, const float ballRadius, const Vector2& boxPos, const Component::CollisionBox &box);
	Vector2 getCollisionOffset(const Vector2& ballPos, const float ballRadius, const Vector2& boxPos, const Component::CollisionBox& box);
};
