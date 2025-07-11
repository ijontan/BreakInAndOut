#pragma once
#include "../Entities.hpp"
#include <vector>

namespace Utils{

	class Level {
	private:
		std::string fileName;
		std::vector<Entity::BlockConfig> blocks;

	public:
		Level(const std::string& fileName) : fileName(fileName) {}
		void addBlockConfig(const Entity::BlockConfig& blockConfig);
		void updateBlockConfig(int index, const Entity::BlockConfig& blockConfig);
		void updateBlockConfigPosition(int index, const Vector2& pos);
		void removeBlockConfig(int index);
		std::vector<Entity::Entity> setupLevel(Scene* scene);
		void loadFile();
		void saveFile();
	};
}
