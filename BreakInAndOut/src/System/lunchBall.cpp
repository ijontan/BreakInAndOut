#include "../../include/Systems.hpp" 
#include <math.h>

static inline float getRadian(float angleInDegree)
{
	return angleInDegree / 180 * PI;
}

void System::launchBall(Scene* scene)
{
	const auto view = scene->registry.view<Component::Position, Component::PaddleState>();
	const auto ballView = scene->registry.view<Component::Position, Component::CircleShape, Component::Velocity>();

	for (const auto& entity : view)
	{
		const Vector2& paddlePosition  = view.get<Component::Position>(entity);
		auto& paddleState  = view.get<Component::PaddleState>(entity);
		if (!paddleState.started)
		{
			for (const auto& entity : ballView)
			{ 
				Vector2& ballPos  =  ballView.get<Component::Position>(entity);
				ballPos = { paddlePosition.x + 100, paddlePosition.y - 11 };
			}
		}
		if (IsKeyDown(KEY_SPACE))
		{
			for (const auto& entity : ballView)
			{ 
				Vector2& ballVelocity  = ballView.get<Component::Velocity>(entity);
				const float magnitude = 10.0f;
				ballVelocity = { paddleState.aimDirection.x * magnitude, paddleState.aimDirection.y * magnitude };
				paddleState.started = true;
			}
		}
		if (IsKeyDown(KEY_X))
		{
			paddleState.angle = std::clamp(paddleState.angle - 1.0f, -45.0f, 45.0f);
			paddleState.aimDirection = { std::sin(getRadian(paddleState.angle)), -std::cos(getRadian(paddleState.angle)) };
		}
		if (IsKeyDown(KEY_C))
		{
			paddleState.angle = std::clamp(paddleState.angle + 1.0f, -45.0f, 45.0f);
			paddleState.aimDirection = { std::sin(getRadian(paddleState.angle)), -std::cos(getRadian(paddleState.angle)) };
		}
	}

}
