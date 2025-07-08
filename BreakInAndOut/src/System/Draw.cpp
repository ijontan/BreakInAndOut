#include "../../include/Systems.hpp"

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
	const auto view = scene->registry.view<Component::Position, Component::RectangleShape>();
	for (const auto& entity : view)
	{
		const Vector2& position = view.get<Component::Position>(entity);
		const Component::RectangleShape rectangle = view.get<Component::RectangleShape>(entity);
		rectangle.draw(position);
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
	drawCollisionBox(scene);
}
