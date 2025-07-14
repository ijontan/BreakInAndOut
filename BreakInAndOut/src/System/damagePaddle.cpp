#include "../../include/Systems.hpp"
#include "../../include/entities.hpp"

void System::damagePaddle(Scene* scene)
{
	const auto ballView = scene->registry.view<Component::Position, Component::CircleShape, Component::Velocity>();
	const auto paddleView = scene->registry.view<Component::PaddleState>();


	for (const auto entity : paddleView)
	{
		auto& paddleState = paddleView.get<Component::PaddleState>(entity);
		if (paddleState.health == 0)
			return;
		bool found = false;
		for (const auto entity : ballView)
		{
			found = true;
		}
		if (found)
			break;
		paddleState.health--;
		if (paddleState.health == 0)
		{
			{
				const std::string text = "YOU LOSE!!";
				const Color textColor = WHITE;
				const Vector2 position = { 300.0f, 200.0f };
				const int fontSize = 150;
				Entity::createText(scene, position, text, textColor, fontSize);
			}

			return;
		}
		paddleState.started = 0;
		Entity::createBall(scene, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 10);
	}
}
