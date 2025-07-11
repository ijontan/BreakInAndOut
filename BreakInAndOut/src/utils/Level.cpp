#include "../../include/utils/Level.hpp"
#include <fstream>
#include <iostream>

namespace Utils {
	void Level::addBlockConfig(const Entity::BlockConfig& blockConfig)
	{
		blocks.push_back(blockConfig);
	}

	void Level::updateBlockConfig(int index, const Entity::BlockConfig& blockConfig)
	{
		if (index < 0 || index >= blocks.size())
			return;
		blocks[index] = blockConfig;
	}

	void Level::updateBlockConfigPosition(int index, const Vector2& position)
	{
		if (index < 0 || index >= blocks.size())
			return;
		blocks[index].position = position;
		std::cout << "Block config updated at index: " << index << " with position: (" 
			<< position.x << ", " << position.y << ")" << std::endl;
	}

	void Level::removeBlockConfig(int index)
	{
		if (index < 0 || index >= blocks.size())
			return;
		blocks.erase(blocks.begin() + index);
		std::cout << "Block config removed at index: " << index << std::endl;
	}

	std::vector<Entity::Entity> Level::setupLevel(Scene *scene)
	{
		std::vector<Entity::Entity> entities;
		entities.reserve(blocks.size());
		for (const auto& block : blocks)
		{
			Entity::Entity blockEntity = Entity::createBlock(scene, block);
			blockEntity.addComponent<Component::MouseHitBox>(
				blockEntity.getComponent<Component::Position>().position,
				blockEntity.getComponent<Component::RectangleShape>().size,
				[]() {}
			);
			entities.push_back(blockEntity);
		}
		for (auto& entity : entities)
		{
			entt::entity id = entity;
			std::cout << "Entity created with ID: " << static_cast<unsigned long>(id) << std::endl;
		}
		return entities;
	}

	void Level::loadFile() {
		std::ifstream file(fileName, std::ios::binary);
		if (!file.is_open())
			return;

		size_t blockCount = 0;
		file.read(reinterpret_cast<char*>(&blockCount), sizeof(blockCount));

		blocks.resize(blockCount);
		file.read(reinterpret_cast<char*>(blocks.data()), blockCount * sizeof(Entity::BlockConfig));
		file.close();
	}
	void Level::saveFile()
	{
		std::ofstream file(fileName, std::ios::binary);
		if (!file.is_open())
			return;

		size_t blockCount = blocks.size();
		file.write(reinterpret_cast<const char*>(&blockCount), sizeof(blockCount));
		file.write(reinterpret_cast<const char*>(blocks.data()), blockCount * sizeof(Entity::BlockConfig));
		file.close();
	}
}