#include "../../include/utils/Level.hpp"
#include <fstream>
#include <cstdio>
#include <iostream>
#include <filesystem>

static void createDir(char const* path)
{
	std::filesystem::path customLevelPath = path;
	try {
		if (std::filesystem::create_directories(customLevelPath))
			std::cout << "created directory: " <<  path << std::endl;
		else 
			std::cout << "failed to create directory: " << path << std::endl;
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Filesystem error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "error: " << e.what() << std::endl;
	}
}

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
	}

	void Level::removeBlockConfig(int index)
	{
		if (index < 0 || index >= blocks.size())
			return;
		blocks.erase(blocks.begin() + index);
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
		if (fileName.empty())
			return;
		const std::string path = isCustom ? CUSTOM_LEVEL_PATH : LEVEL_PATH;
		createDir(path.c_str());

		std::ifstream file(path + fileName + LEVEL_FILE_EXTENSION, std::ios::binary);
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
		const std::string path = isCustom ? CUSTOM_LEVEL_PATH : LEVEL_PATH;
		createDir(path.c_str());

		if (newName.has_value())
		{
			std::remove(fileName.c_str());
			fileName = newName.value();
			newName.reset();
		}

		std::ofstream file(path + fileName + LEVEL_FILE_EXTENSION, std::ios::binary);
		if (!file.is_open())
			return;

		size_t blockCount = blocks.size();
		file.write(reinterpret_cast<const char*>(&blockCount), sizeof(blockCount));
		file.write(reinterpret_cast<const char*>(blocks.data()), blockCount * sizeof(Entity::BlockConfig));
		file.close();
	}

	void Level::updateName(const std::string& updatedName)
	{
		newName = updatedName;
	}

	std::string& Level::getName()
	{
		return newName.has_value() ? newName.value() : fileName;
	}
}