#include "../../include/utils/collisionDetection.hpp"

namespace Utils {
	bool checkCollision(const Vector2& ballPos, const float ballRadius, const Vector2& boxPos, const Component::CollisionBox& box) {
		return (ballPos.x + ballRadius >= boxPos.x &&
			ballPos.x - ballRadius <= boxPos.x + box.size.x &&
			ballPos.y + ballRadius >= boxPos.y &&
			ballPos.y - ballRadius <= boxPos.y + box.size.y);
	}

	Vector2 getCollisionOffset(const Vector2& ballPos, const float ballRadius, const Vector2& boxPos, const Component::CollisionBox& box) {
		return {
			(ballPos.x < boxPos.x) ? (boxPos.x - (ballPos.x + ballRadius)) : (boxPos.x + box.size.x - (ballPos.x - ballRadius)),
			(ballPos.y < boxPos.y) ? (boxPos.y - (ballPos.y + ballRadius)) : (boxPos.y + box.size.y - (ballPos.y - ballRadius))
		};
	}
}
