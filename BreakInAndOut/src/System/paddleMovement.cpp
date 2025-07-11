#include "../../include/Systems.hpp"

void System::paddleMovement(Scene* scene)
{
	const auto screenWidth = GetScreenWidth();

	const auto paddleView = scene->registry.view<Component::Position, Component::PaddleState, Component::Velocity, Component::RectangleShape>();
	for (auto entity : paddleView)
	{
		const auto& position = paddleView.get<Component::Position>(entity).position;
		const auto& paddleState = paddleView.get<Component::PaddleState>(entity);
		const auto& rectangleShape = paddleView.get<Component::RectangleShape>(entity);
		auto& velocity = paddleView.get<Component::Velocity>(entity).velocity;
		if (IsKeyDown(KEY_LEFT) && position.x > 0)
		{
			velocity.x = -10.0f;
		}
		else if (IsKeyDown(KEY_RIGHT) && position.x + rectangleShape.size.x < screenWidth)
		{
			velocity.x = 10.0f;
		}
		else
		{
			velocity.x = 0.0f;
		}
	}
}