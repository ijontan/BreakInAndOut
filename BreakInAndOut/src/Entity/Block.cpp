#include "../../include/Entities.hpp"

namespace Entity {
	Entity createBlock(Scene* scene, Vector2 position, Vector2 size, Color color)
	{
		Entity block = scene->createEntity();
		block.addComponent<Component::Position>(position);
		block.addComponent<Component::RectangleShape>(size, color);
		block.addComponent<Component::CollisionBox>(size);
		return block;
	}
};