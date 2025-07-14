#include "../../include/Systems.hpp"
#include "../../include/Entities.hpp"
#include "../../include/utils/Level.hpp"

void System::checkWin(Scene* scene)
{
	if (!scene->level || (scene->level && scene->level->getName() == "menu"))
		return;
	const auto view = scene->registry.view<Component::BlockState>();
	int count = 0;
	for (const auto& entity : view)
	{
		auto& blockState = view.get<Component::BlockState>(entity);
		switch (blockState.type)
		{
		case Component::BlockType::NORMAL:
		case Component::BlockType::BALLOON:
			++count;
			break;
		}
	}
	if (count != 0)
		return;

	{
		const std::string text = "YOU WON!!";
		const Color textColor = WHITE;
		const Vector2 position = { 300.0f, 200.0f };
		const int fontSize = 150;
		Entity::createText(scene, position, text, textColor, fontSize);
	}

	scene->timeBeforeNextStage += GetFrameTime();
	if (scene->timeBeforeNextStage >= 5.0f)
	{
		if (scene->level && scene->level->isCustom)
		{
			scene->gotoCustoms();
		}
		else if (scene->level)
		{
			auto it = std::find(scene->storyLevelsOrders.begin(), scene->storyLevelsOrders.end(), scene->level->getName());
			if (it != scene->storyLevelsOrders.end() && ++it != scene->storyLevelsOrders.end() )
			{
				scene->gotoLevel(*(++it), false);
			}
			else
			{
				scene->gotoMenu();
			}
		}
	}
}
