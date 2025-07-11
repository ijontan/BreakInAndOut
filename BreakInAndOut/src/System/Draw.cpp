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
	const float stepTime = 1.0f / 0.1f * GetFrameTime();
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

static void drawText(Scene* scene)
{
	const auto view = scene->registry.view<Component::Text>();
	for (const auto& entity : view)
	{
		const Component::Text& text = view.get<Component::Text>(entity);
		text.draw();
	}
}

static void drawContainer(Scene* scene)
{
	const auto view = scene->registry.view<Component::Container>();
	for (const auto& entity : view)
	{
		const Component::Container& container = view.get<Component::Container>(entity);
		container.draw();
	}
}

static void drawHitBox(Scene* scene)
{
	const auto view = scene->registry.view<Component::MouseHitBox>();
	for (const auto& entity : view)
	{
		const Component::MouseHitBox& hitBox = view.get<Component::MouseHitBox>(entity);
		if (hitBox.isMouseOver())
		{
			DrawRectangleLinesEx({ hitBox.position.x, hitBox.position.y, hitBox.size.x, hitBox.size.y }, 2, RED);
		}
	}
}

void System::draw2D(Scene* scene)
{
	drawRectangle(scene);
	drawCircle(scene);
	drawContainer(scene);
	drawHitBox(scene);
	drawText(scene);
	//drawCollisionBox(scene);
}
