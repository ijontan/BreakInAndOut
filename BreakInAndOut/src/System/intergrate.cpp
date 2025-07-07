
#include "../../include/Systems.hpp"

void integrate(Scene* scene)
{
	const auto view = scene->registry.view<Component::Position, Component::Velocity>();
	const auto delta = GetFrameTime() * 60;
	const auto width = GetScreenWidth();
	const auto height = GetScreenHeight();

	for (const auto& entity : view)
	{
		Vector2& position = view.get<Component::Position>(entity);
		Vector2& velocity = view.get<Component::Velocity>(entity);

		position.x += velocity.x * delta;
		position.y += velocity.y * delta;

		if (position.x < 0 || position.x > width)
		{
			velocity.x *= -1.0f;
		}
		if (position.y < 0 || position.y > height)
		{
			velocity.y *= -1.0f;
		}
	}
}
