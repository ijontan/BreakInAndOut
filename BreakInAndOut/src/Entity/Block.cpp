#include "../../include/Entities.hpp"
#include <iostream>

namespace Entity {
	Entity createBlock(Scene* scene, Vector2 position, Vector2 size, Color color, Component::BlockType type, Component::GhostLayer layer)
	{
		Entity block = scene->createEntity();
		block.addComponent<Component::Position>(position);
		block.addComponent<Component::RectangleShape>(size, color);
		block.addComponent<Component::CollisionBox>(size);
		const Component::BlockState blockState(type, layer);
		std::cout << "Creating block with layer: " << static_cast<int>(layer) << std::endl;
		std::cout << "layer: " << static_cast<int>(blockState.layer) << std::endl;
		block.addComponent<Component::BlockState>(blockState);
		return block;
	}
};