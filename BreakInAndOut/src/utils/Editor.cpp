#include "../../include/utils/Editor.hpp"
#include <iostream>

namespace Utils
{
	void Editor::loadFromFile(Scene* scene)
	{
		level.loadFile();
		blocks = level.setupLevel(scene);
	}

	void Editor::setType(Component::BlockType type)
	{
		blockConfigFactory.setType(type);
	}

	void Editor::setLayer(Component::GhostLayer layer)
	{
		blockConfigFactory.setLayer(layer);
		if (selectedBlock.has_value())
			selectedBlock->getComponent<Component::BlockState>().layer = layer;
	}

	void Editor::setPosition(Vector2 pos)
	{
		if (selectedBlock.has_value())
		{
			const auto& rectangleShape = selectedBlock->getComponent<Component::RectangleShape>();
			pos = { pos.x - rectangleShape.size.x / 2, pos.y - rectangleShape.size.y / 2 };
			pos = { static_cast<float>(Utils::snapToNearest(pos.x, 10)), static_cast<float>(Utils::snapToNearest(pos.y, 10)) };
			selectedBlock->getComponent<Component::Position>().position = pos;
			selectedBlock->getComponent<Component::MouseHitBox>().position = pos;
			int index = 0;
			for (auto& block : blocks)
			{
				if (block == selectedBlock.value())
				{
					level.updateBlockConfigPosition(index, pos);
					break;
				}
				index++;
			}
		}
		blockConfigFactory.setPosition(pos);
	}

	void Editor::setHitSound(Utils::Notes hitSound)
	{
		blockConfigFactory.setSound(hitSound);
	}

	void Editor::createBlock(Scene* scene)
	{
		Entity::BlockConfig config = blockConfigFactory.createConfig();
		Entity::Entity block = Entity::createBlock(scene, config);
		block.addComponent<Component::MouseHitBox>(
			block.getComponent<Component::Position>().position,
			block.getComponent<Component::RectangleShape>().size,
			[]() {}
		);
		selectedBlock.emplace(block);
		blocks.push_back(block);
		level.addBlockConfig(config);
		scene->sounds.playSound(config.hitSound);
	}

	void Editor::selectBlock(Entity::Entity entity) 
	{
		selectedBlock = entity;
	}

	void Editor::unselectBlock() 
	{
		selectedBlock.reset();
	}

	void Editor::deleteSelectedBlock(Scene* scene)
	{
		if (!selectedBlock.has_value())
			return;
		int index = 0;
		for (auto& block : blocks)
		{
			if (block == selectedBlock.value())
			{
				level.removeBlockConfig(index);
				blocks.erase(blocks.begin() + index);
				break;
			}
			index++;
		}
		scene->registry.destroy(selectedBlock.value());
		unselectBlock();
	}

	void Editor::saveLevel()
	{
		level.saveFile();
		std::cout << "Level saved successfully." << std::endl;
	}

	void Editor::updateName(const std::string& updatedName)
	{
		level.updateName(updatedName);
	}

	std::string& Editor::getLevelName() 
	{
		return level.getName();
	}

	Utils::Notes& Editor::getHitSound()
	{
		return blockConfigFactory.getSound();
	}

	Component::BlockType& Editor::getBlockType()
	{
		return blockConfigFactory.getType();
	}
}
