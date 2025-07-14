#include "../../include/Systems.hpp"
#include <iostream>

static void bounceBall(Vector2& ballPos, float ballRadius, Vector2& ballVelocity, const Vector2& blockPos, const Component::CollisionBox& box)
{
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

static void damageBlock(Scene *scene, Component::BlockState& blockState, entt::entity block)
{
	if (blockState.health > 1) {
		blockState.health--;
	} else {
		scene->registry.destroy(block);
	}
}

void System::collision(Scene* scene)
{
	// TODO:fix the hardcoded screen size
	const auto width = GetScreenWidth() - 400;
	const auto height = GetScreenHeight();

	const auto ballView = scene->registry.view<Component::Position, Component::CircleShape, Component::Velocity>();
	const auto blockView = scene->registry.view<Component::Position, Component::CollisionBox, Component::BlockState>();

	for (const auto& ballEntity : ballView) {
		const float ballRadius = ballView.get<Component::CircleShape>(ballEntity).radius;
		Vector2& ballPos = ballView.get<Component::Position>(ballEntity).position;
		Vector2& ballVelocity = ballView.get<Component::Velocity>(ballEntity).velocity;


		if ((ballPos.x < 0 && ballVelocity.x < 0) || (ballPos.x > width && ballVelocity.x > 0))
		{
			ballVelocity.x *= -1.0f;
		}
		if (ballPos.y < 0 && ballVelocity.y < 0)
		{
			ballVelocity.y *= -1.0f;
		}
		if (ballPos.y > height && ballVelocity.y > 0)
		{
			scene->registry.destroy(ballEntity);
		}

		bool breakLoop = false;
		for (const auto& blockEntity : blockView) {
			if (breakLoop || ballEntity == blockEntity)
				continue;
			const Vector2& blockPos = blockView.get<Component::Position>(blockEntity).position;
			const Component::CollisionBox& box = blockView.get<Component::CollisionBox>(blockEntity);
			Component::BlockState& blockState = blockView.get<Component::BlockState>(blockEntity);
			if (!(blockState.layer & scene->mask))
				continue;

			if (!Utils::checkCollision(ballPos, ballRadius, blockPos, box)) 
				continue;

			breakLoop = true;
			switch (blockState.type)
			{
			case Component::BlockType::WALL:
				bounceBall(ballPos, ballRadius, ballVelocity, blockPos, box);
				break;
			case Component::BlockType::NORMAL:
				bounceBall(ballPos, ballRadius, ballVelocity, blockPos, box);
				damageBlock(scene, blockState, blockEntity);
				break;
			case Component::BlockType::BALLOON:
				damageBlock(scene, blockState, blockEntity);
				break;
			case Component::BlockType::SPIKES:
				scene->registry.destroy(ballEntity);
				break;
			}
			scene->sounds.playSound(blockState.hitSound);
		}
	}
}
