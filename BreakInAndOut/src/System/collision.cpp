#include "../../include/Systems.hpp"
#include <iostream>

void System::collision(Scene* scene) {
	const auto ballView = scene->registry.view<Component::Position, Component::CircleShape, Component::Velocity>();

	const auto blockView = scene->registry.view<Component::Position, Component::CollisionBox>();

	for (const auto& ballEntity : ballView) {
		const float ballRadius = ballView.get<Component::CircleShape>(ballEntity).radius;
		Vector2& ballPos = ballView.get<Component::Position>(ballEntity).position;
		Vector2& ballVelocity = ballView.get<Component::Velocity>(ballEntity).velocity;

		for (const auto& blockEntity : blockView) {
			if (ballEntity == blockEntity) 
				continue;
			const Vector2& blockPos = blockView.get<Component::Position>(blockEntity).position;
			const Component::CollisionBox& box = blockView.get<Component::CollisionBox>(blockEntity);

			if (!Utils::checkCollision(ballPos, ballRadius, blockPos, box)) 
				continue;

			Vector2 offset = Utils::getCollisionOffset(ballPos, ballRadius, blockPos, box);

			if (abs(offset.x) < abs(offset.y)) {
				offset.y = 0.0f; // Only adjust the x-axis
			} else {
				offset.x = 0.0f; // Only adjust the y-axis
			}

			ballPos.x += offset.x;
			ballPos.y += offset.y;
			if (offset.x != 0.0f) {
				ballVelocity.x *= -1.0f;
			}
			if (offset.y != 0.0f) {
				ballVelocity.y *= -1.0f;
			}

		}
	}
}
