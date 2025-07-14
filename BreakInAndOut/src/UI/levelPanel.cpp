#include "../../include/UI.hpp"
#include "../../include/entities.hpp"
#include "../../include/utils/Editor.hpp"
#include "../../include/Component/Watcher.hpp"
#include <string>

void UI::levelPanel(Scene* scene) {

	const float screenWidth = GetScreenWidth();
	const float screenHeight = GetScreenHeight();

	const Vector2 panePosition = { screenWidth  - 400.0f, 0.0f };
	const Vector2 panePadding = { 50.0f, 50.0f };

	float yPosition = 0;

	// add text
	{
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition};
		const std::string text = "Level:";
		const Color color = BLACK;
		const float fontSize = 30;
		Entity::createText(scene, position, text, color, fontSize);
		yPosition += fontSize;
	}
	// level name
	{
		yPosition += 5.0f;
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition};
		const std::string text = scene->level->getName();
		const Color color = BLACK;
		const float fontSize = 30;
		Entity::createText(scene, position, text, color, fontSize);
		yPosition += fontSize;
	}

	yPosition += 20.0f;
	// display layer
	{
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition};
		const std::string text = "Layer:";
		const Color color = BLACK;
		const float fontSize = 20;
		Entity::createText(scene, position, text, color, fontSize);
		yPosition += fontSize;
	}
	yPosition += 10.0f;
	for (size_t i = 0; i < 8; i++)
	{
		const Vector2 buttonSize = { 37.0f, 40.0f };
		const Vector2 position = { panePosition.x + panePadding.x + i * 37 , panePosition.y + panePadding.y + yPosition};
		const std::string text = std::to_string(i);
		const Color textColor = BLACK;
		const int fontSize = 40;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = WHITE;
		const auto onClick = []() {
		};

		Entity::Entity button = Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
		button.addComponent<Component::Watcher>(Component::Watcher{
			[scene, button, i]() {
				auto& container = button.getComponent<Component::Container>();
				if (Utils::isBitSet(scene->mask, 1 << i))
					container.backgroundColor = WHITE;
				else
					container.backgroundColor = LIGHTGRAY;
			},
		});
	}
	yPosition += 50.0f;
	{
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition};
		const std::string text = "Remaining:";
		const Color color = BLACK;
		const float fontSize = 20;
		Entity::createText(scene, position, text, color, fontSize);
		yPosition += fontSize;
	}
	yPosition += 10.0f;
	{
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition};
		const std::string text = "0";
		const Color color = BLACK;
		const float fontSize = 100;
		Entity::Entity displayText = Entity::createText(scene, position, text, color, fontSize);
		displayText.addComponent<Component::Watcher>(Component::Watcher{
			[scene, displayText]() {
				auto& text = displayText.getComponent<Component::Text>();
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
				text.text = std::to_string(count);
			},
		});
		yPosition += fontSize;
	}

	// restart button
	{
		const Vector2 buttonSize = { (400.0f - panePadding.x * 2) / 2, 30.0f };
		const Vector2 position = { panePosition.x + panePadding.x, screenHeight - panePadding.y - buttonSize.y};
		const std::string text = "Restart";
		const Color textColor = BLACK;
		const int fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = GREEN;
		const auto onClick = [scene]() {
			const std::string fileName = scene->level->getName();
			const bool isCustom = scene->level->isCustom;
			scene->gotoLevel(fileName, isCustom);
		};

		Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}
	// exit button
	{
		const Vector2 buttonSize = { (400.0f - panePadding.x * 2) / 2, 30.0f };
		const Vector2 position = { panePosition.x + panePadding.x + (400.0f - panePadding.x * 2) / 2, screenHeight - panePadding.y - buttonSize.y};
		const std::string text = "Exit";
		const Color textColor = BLACK;
		const int fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = RED;
		const auto onClick = [scene]() {
			if (scene->level && scene->level->isCustom)
				scene->gotoCustoms();
			else
				scene->gotoMenu();
		};

		Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}
	{
		const Vector2 size = { 400, screenHeight  };
		const Color backgroundColor = GRAY;
		Entity::createPanel(scene, panePosition, size, backgroundColor);
	}
}
