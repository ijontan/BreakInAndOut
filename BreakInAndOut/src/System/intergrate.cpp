#include "../../include/Systems.hpp"

void System::integrate(Scene* scene)
{
	const auto view = scene->registry.view<Component::Position, Component::Velocity>();
	const auto delta = GetFrameTime() * 60;

	for (const auto& entity : view)
	{
		Vector2& position = view.get<Component::Position>(entity);
		Vector2& velocity = view.get<Component::Velocity>(entity);

		position.x += velocity.x * delta;
		position.y += velocity.y * delta;
	}
}
