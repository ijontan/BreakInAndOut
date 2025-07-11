#pragma once
#include "../Component/BlockState.hpp"
#include "../Entities.hpp"
#include "../Entity.hpp"
#include "Level.hpp"
#include <optional>

namespace Utils
{
	class Editor
	{
	private:
		Entity::BlockConfigFactory blockConfigFactory;
		std::optional<Entity::Entity> selectedBlock;

		
		std::vector<Entity::Entity> blocks;
		Utils::Level level = Utils::Level("test.lvl");

	public:
		void loadFromFile(Scene* scene);
		void setType(Component::BlockType type);
		void setLayer(Component::GhostLayer layer);
		void setPosition(Vector2 pos);
		void createBlock(Scene* scene);
		void selectBlock(Entity::Entity entity);
		void unselectBlock();
		void deleteSelectedBlock(Scene *scene);
		void saveLevel();
	};
};