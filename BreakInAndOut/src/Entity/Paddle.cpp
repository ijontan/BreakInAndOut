#include "../../include/Entities.hpp"
#include "../../include/Entity.hpp"

namespace Entity {
	Entity createPaddle(Scene* scene, Vector2 position, Vector2 size, Color color)
	{
		std::vector<Entity> bodies;

		Entity paddle = scene->createEntity();
		paddle.addComponent<Component::Position>(position);
		paddle.addComponent<Component::Velocity>(Vector2{ 0.0f, 0.0f });
		paddle.addComponent<Component::RectangleShape>(size, color);
		paddle.addComponent<Component::CollisionBox>(size);
		paddle.addComponent<Component::PaddleState>();
		paddle.addComponent<Component::BlockState>(Component::BlockType::WALL, Component::GhostLayer::REAL, Utils::Notes::C3);
		paddle.addComponent<Component::Displacement>(position);
		return paddle;
	}
};
