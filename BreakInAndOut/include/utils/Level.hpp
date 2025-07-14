#pragma once
#include "../Entities.hpp"
#include <vector>
#include <optional>

#define LEVEL_FILE_EXTENSION ".lvl"
#define LEVEL_PATH "levels/story/"
#define CUSTOM_LEVEL_PATH "levels/custom/"

namespace Utils{

	class Level {
	private:
		std::string fileName;
		std::optional<std::string> newName;
		std::vector<Entity::BlockConfig> blocks;

	public:
		bool isCustom = false;

		Level(const std::string& fileName, bool isCustom) : fileName(fileName), isCustom(isCustom) {}
		void addBlockConfig(const Entity::BlockConfig& blockConfig);
		void updateBlockConfig(int index, const Entity::BlockConfig& blockConfig);
		void updateBlockConfigPosition(int index, const Vector2& pos);
		void removeBlockConfig(int index);
		std::vector<Entity::Entity> setupLevel(Scene* scene);
		void loadFile();
		void saveFile();
		void updateName(const std::string& updatedName);
		std::string& getName();
	};
}
