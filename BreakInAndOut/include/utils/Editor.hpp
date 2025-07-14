#pragma once
#include "../Component/BlockState.hpp"
#include "../Entities.hpp"
#include "../Entity.hpp"
#include "Level.hpp"
#include <optional>
#include <string>

namespace Utils
{
	class Editor
	{
	private:
		Entity::BlockConfigFactory blockConfigFactory;
		std::optional<Entity::Entity> selectedBlock;

		
		std::vector<Entity::Entity> blocks;
		Utils::Level level;

	public:
		Editor(const std::string& fileName) : level(fileName, true) {}
		bool editingName = false;

		void loadFromFile(Scene* scene);
		void setType(Component::BlockType type);
		void setLayer(Component::GhostLayer layer);
		void setPosition(Vector2 pos);
		void setHitSound(Utils::Notes hitSound);
		void createBlock(Scene* scene);
		void selectBlock(Entity::Entity entity);
		void unselectBlock();
		void deleteSelectedBlock(Scene *scene);
		void saveLevel();
		void updateName(const std::string& updatedName);
		std::string& getLevelName();
		Utils::Notes& getHitSound();
		Component::BlockType& getBlockType();
	};
};