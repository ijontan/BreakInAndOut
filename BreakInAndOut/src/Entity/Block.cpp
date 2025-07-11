#include "../../include/Entities.hpp"
#include "../../include/Entity.hpp"
#include <iostream>

namespace Entity {
	Entity createBlock(Scene* scene, const BlockConfig& config)
	{
		Entity block = scene->createEntity();
		block.addComponent<Component::Position>(config.position);
		block.addComponent<Component::RectangleShape>(config.size, config.color);
		block.addComponent<Component::CollisionBox>(config.size);
		Component::BlockState blockState(config.type, config.layer);
		blockState.setColorTransition(scene->mask, 0);
		block.addComponent<Component::BlockState>(blockState);
		return block;
	}
};