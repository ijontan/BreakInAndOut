#include "../../include/Systems.hpp"
#include <iostream>
#include <bitset>
#include <raymath.h>

static void drawArrow(Scene* scene)
{
	const auto view = scene->registry.view<Component::Position, Component::RectangleShape, Component::PaddleState>();

	for (const auto& entity : view)
	{
		const Vector2& position = view.get<Component::Position>(entity);
		const auto& paddleState = view.get<Component::PaddleState>(entity);

		if (paddleState.started)
			continue;
		for (int i = 1; i < 8; ++i)
		{
			const float distance = i * 15.0f;
			const Vector2 direction = { paddleState.aimDirection.x * distance, paddleState.aimDirection.y * distance };
			const Vector2 finalPos = { position.x + 100 + direction.x, position.y - 11 + direction.y };
			const float size = 2;
			DrawCircle(static_cast<int>(finalPos.x), static_cast<int>(finalPos.y), size, WHITE);
		}
	}
}

static void drawCircle(Scene* scene)
{
	const auto view = scene->registry.view<Component::Position, Component::CircleShape, Component::Displacement>();

	for (const auto& entity : view)
	{
		const Vector2& position = view.get<Component::Position>(entity);
		const Component::CircleShape& circle = view.get<Component::CircleShape>(entity);
		const Vector2& displacement = view.get<Component::Displacement>(entity);
		circle.draw(Vector2Add(position, displacement));
	}
}

static void drawRectangle(Scene* scene)
{
	const float stepTime = 1.0f / 0.1f * GetFrameTime();
	const auto view = scene->registry.view<Component::Position, Component::RectangleShape, Component::BlockState, Component::Displacement>();
	for (const auto& entity : view)
	{
		const Vector2& position = view.get<Component::Position>(entity);
		const Component::RectangleShape& rectangle = view.get<Component::RectangleShape>(entity);
		const Vector2& displacement = view.get<Component::Displacement>(entity);
		Component::BlockState& blockState = view.get<Component::BlockState>(entity);

		if (!Utils::isBitSet(scene->mask, blockState.layer))
		{
			Color color = rectangle.color;
			color.a = static_cast<unsigned char>(Utils::linearInterpolation(blockState.startOpacity, blockState.targetOpacity, blockState.t));
			rectangle.draw(Vector2Add(position, displacement), color);
			blockState.step(stepTime);
		}
	}
	for (const auto& entity : view)
	{
		const Vector2& position = view.get<Component::Position>(entity);
		const Component::RectangleShape& rectangle = view.get<Component::RectangleShape>(entity);
		const Vector2& displacement = view.get<Component::Displacement>(entity);
		Component::BlockState& blockState = view.get<Component::BlockState>(entity);

		if (!Utils::isBitSet(scene->mask, blockState.layer))
			continue;

		Color color = rectangle.color;
		color.a = static_cast<unsigned char>(Utils::linearInterpolation(blockState.startOpacity, blockState.targetOpacity, blockState.t));
		rectangle.draw(Vector2Add(position, displacement), color);
		blockState.step(stepTime);
		if (blockState.t >= 1.0f)
			rectangle.drawOutline(Vector2Add(position, displacement), 2, WHITE);
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

static void drawText(Scene* scene)
{
	const auto view = scene->registry.view<Component::Text, Component::Displacement>();
	for (const auto& entity : view)
	{
		const Component::Text& text = view.get<Component::Text>(entity);
		const Vector2& displacement = view.get<Component::Displacement>(entity);
		text.draw(displacement);
	}
}

static void drawContainer(Scene* scene)
{
	const auto view = scene->registry.view<Component::Container, Component::Displacement>();
	for (const auto& entity : view)
	{
		const Component::Container& container = view.get<Component::Container>(entity);
		const Vector2& displacement = view.get<Component::Displacement>(entity);
		container.draw(displacement);
	}
}

void System::draw2D(Scene* scene)
{
	drawRectangle(scene);
	drawCircle(scene);
	drawContainer(scene);
	drawText(scene);
	//drawCollisionBox(scene);
	if (scene->unloadingPage || scene->loadingPage)
		return;
	drawArrow(scene);
}
