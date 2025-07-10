#include "../../include/Systems.hpp"
#include <iostream>
#include <bitset>

static void drawCircle(Scene* scene)
{
	const auto view = scene->registry.view<Component::Position, Component::CircleShape>();

	for (const auto& entity : view)
	{
		const Vector2& position = view.get<Component::Position>(entity);
		const Component::CircleShape circle = view.get<Component::CircleShape>(entity);
		circle.draw(position);
	}
}

static void drawRectangle(Scene* scene)
{
	const float stepTime = 1 / 0.1 * GetFrameTime();
	const auto view = scene->registry.view<Component::Position, Component::RectangleShape, Component::BlockState>();
	for (const auto& entity : view)
	{
		const Vector2& position = view.get<Component::Position>(entity);
		const Component::RectangleShape& rectangle = view.get<Component::RectangleShape>(entity);
		Component::BlockState& blockState = view.get<Component::BlockState>(entity);

		if (!Utils::isBitSet(scene->mask, blockState.layer))
		{
			Color color = rectangle.color;
			color.a = static_cast<unsigned char>(Utils::linearInterpolation(blockState.startOpacity, blockState.targetOpacity, blockState.t));
			rectangle.draw(position, color);
			blockState.step(stepTime);
		}
	}
	for (const auto& entity : view)
	{
		const Vector2& position = view.get<Component::Position>(entity);
		const Component::RectangleShape& rectangle = view.get<Component::RectangleShape>(entity);
		Component::BlockState& blockState = view.get<Component::BlockState>(entity);

		if (!Utils::isBitSet(scene->mask, blockState.layer))
			continue;

		Color color = rectangle.color;
		color.a = static_cast<unsigned char>(Utils::linearInterpolation(blockState.startOpacity, blockState.targetOpacity, blockState.t));
		rectangle.draw(position, color);
		blockState.step(stepTime);
		if (blockState.t >= 1.0f)
			rectangle.drawOutline(position, 2, WHITE);
	}
}

static void drawCollisionBox(Scene* scene)
{
	const auto view = scene->registry.view<Component::Position, Component::CollisionBox>();
	for (const auto& entity : view)
	{
		const Vector2& position = view.get<Component::Position>(entity);
		const Component::CollisionBox rectangle = view.get<Component::CollisionBox>(entity);
		Rectangle rect = { position.x, position.y, rectangle.size.x, rectangle.size.y};

		DrawRectangleLinesEx(rect, 2, BLUE);
	}
}

void System::draw2D(Scene* scene)
{
	drawRectangle(scene);
	drawCircle(scene);
	//drawCollisionBox(scene);
}
