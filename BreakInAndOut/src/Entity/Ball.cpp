#include "../../include/Scene.hpp"
#include "../../include/Entities.hpp"
#include "../../include/Entity.hpp"

namespace Entity{
	Entity createBall(Scene* scene, Vector2 position, Vector2 velocity, float radius)
	{
		Entity ball = scene->createEntity();
		ball.addComponent<Component::Position>(position);
		ball.addComponent<Component::Velocity>(velocity);
		ball.addComponent<Component::CircleShape>(radius);
		return ball;
	}
};