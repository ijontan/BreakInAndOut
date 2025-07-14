#include "../../include/UI.hpp"
#include "../../include/entities.hpp"
#include "../../include/utils/Editor.hpp"
#include "../../include/Component/Watcher.hpp"
#include <string>

void UI::editPanel(Scene* scene) {

	const float screenWidth = GetScreenWidth();
	const float screenHeight = GetScreenHeight();

	const Vector2 panePosition = { screenWidth  - 400.0f, 0.0f };
	const Vector2 panePadding = { 50.0f, 50.0f };

	float yPosition = 0;

	// add text
	{
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition};
		const std::string text = "Editing level:";
		const Color color = BLACK;
		const float fontSize = 30;
		Entity::createText(scene, position, text, color, fontSize);
		yPosition += fontSize;
	}

	// input field for custom level name
	{
		yPosition += 5.0f;
		const Vector2 buttonSize = { 400.0f - panePadding.x * 2, 40.0f };
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition };
		yPosition += buttonSize.y;
		const std::string text = "(empty)";
		const Color textColor = BLACK;
		const float fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = WHITE;
		const auto onClick = [scene]() {
			scene->editor->editingName = true;
		};
		Entity::Entity levelName = Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
		levelName.addComponent<Component::Watcher>(Component::Watcher{
			[scene, levelName]() {
				auto& text = levelName.getComponent<Component::Text>();
				std::string name = scene->editor->getLevelName();
				text.text = name;

				if (!scene->editor->editingName)
					return;
				auto& container = levelName.getComponent<Component::Container>();
				container.borderColor = GREEN;
				int key = GetCharPressed();
				bool keyPressed = false;

				while (key > 0)
				{
					if (key >= 32 && key <= 125)
					{
						name = name + static_cast<char>(key);
						keyPressed = true;
					}
					key = GetCharPressed();
				}

				if (IsKeyPressed(KEY_BACKSPACE) && name.size() > 0)
				{
					name.pop_back();
					keyPressed = true;
				}

				if (keyPressed)
				{
					scene->editor->updateName(name);
					text.text = name;
				}

				if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
				{
					scene->editor->editingName = false;
					container.borderColor = { 0, 0, 0, 0 };
					if (IsKeyPressed(KEY_ENTER))
						scene->editor->saveLevel();
				}
			},
		});
	}

	yPosition += 20.0f;
	// add text
	{
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition};
		const std::string text = "Select Sound:";
		const Color color = BLACK;
		const float fontSize = 20;
		Entity::createText(scene, position, text, color, fontSize);
		yPosition += fontSize;
	}

	yPosition += 10.0f;

	// select Sounds
	for (int i = 0; i < static_cast<int>(Utils::Notes::B3) + 1; ++i)
	{
		const Utils::Notes note = static_cast<Utils::Notes>(i);
		const Vector2 buttonSize = { 45.0f , 35.0f };
		const Vector2 position = { panePosition.x + panePadding.x + i * 50.0f - 20, panePosition.y + panePadding.y + yPosition };
		const std::string text = Utils::Sounds::getTextOfNote(note);
		const Color textColor = BLACK;
		const int fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = WHITE;
		const auto onClick = [scene, note]() {
			if (scene->editor)
				scene->editor->setHitSound(note);
			scene->sounds.playSound(note);
		};

		Entity::Entity button = Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
		button.addComponent<Component::Watcher>(Component::Watcher{
			[scene, button, note]() {
				auto& container = button.getComponent<Component::Container>();
				if (scene->editor && scene->editor->getHitSound() == note)
					container.borderColor = GREEN;
				else
					container.borderColor = { 0, 0, 0, 0 };
			},
		});
	}
	yPosition += 40.0f;
	for (int i = static_cast<int>(Utils::Notes::C4); i < static_cast<int>(Utils::Notes::B4) + 1; ++i)
	{
		const Utils::Notes note = static_cast<Utils::Notes>(i);
		const Vector2 buttonSize = { 45.0f , 35.0f };
		const Vector2 position = { panePosition.x + panePadding.x + (i - 7) * 50.0f - 20, panePosition.y + panePadding.y + yPosition };
		const std::string text = Utils::Sounds::getTextOfNote(note);
		const Color textColor = BLACK;
		const int fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = WHITE;
		const auto onClick = [scene, note]() {
			if (scene->editor)
				scene->editor->setHitSound(note);
			scene->sounds.playSound(note);
		};

		Entity::Entity button = Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
		button.addComponent<Component::Watcher>(Component::Watcher{
			[scene, button, note]() {
				auto& container = button.getComponent<Component::Container>();
				if (scene->editor && scene->editor->getHitSound() == note)
					container.borderColor = GREEN;
				else
					container.borderColor = { 0, 0, 0, 0 };
			},
		});
	}
	yPosition += 60.0f;

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

	yPosition += 70.0f;
	// select block type
	{
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition};
		const std::string text = "Select Block Type:";
		const Color color = BLACK;
		const float fontSize = 20;
		Entity::createText(scene, position, text, color, fontSize);
		yPosition += fontSize;
	}
	yPosition += 10.0f;
	{
		const Vector2 buttonSize = { 400.0f - panePadding.x * 2, 30.0f };
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition };
		const std::string text = "Wall";
		const Color textColor = BLACK;
		const int fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = WHITE;
		const auto onClick = [scene]() {
			if (scene->editor)
				scene->editor->setType(Component::BlockType::WALL);
		};
		Entity::Entity button = Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
		button.addComponent<Component::Watcher>(Component::Watcher{
			[scene, button]() {
				auto& container = button.getComponent<Component::Container>();
				if (scene->editor && scene->editor->getBlockType() == Component::BlockType::WALL)
					container.borderColor = GREEN;
				else
					container.borderColor = { 0, 0, 0, 0 };
			},
		});
	}
	yPosition += 35.0f;
	{
		const Vector2 buttonSize = { 400.0f - panePadding.x * 2, 30.0f };
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition };
		const std::string text = "Normal";
		const Color textColor = BLACK;
		const int fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = BLUE;
		const auto onClick = [scene]() {
			if (scene->editor)
				scene->editor->setType(Component::BlockType::NORMAL);
		};
		Entity::Entity button = Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
		button.addComponent<Component::Watcher>(Component::Watcher{
			[scene, button]() {
				auto& container = button.getComponent<Component::Container>();
				if (scene->editor && scene->editor->getBlockType() == Component::BlockType::NORMAL)
					container.borderColor = GREEN;
				else
					container.borderColor = { 0, 0, 0, 0 };
			},
		});
	}
	yPosition += 35.0f;
	{
		const Vector2 buttonSize = { 400.0f - panePadding.x * 2, 30.0f };
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition };
		const std::string text = "Balloon";
		const Color textColor = BLACK;
		const int fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = GREEN;
		const auto onClick = [scene]() {
			if (scene->editor)
				scene->editor->setType(Component::BlockType::BALLOON);
		};
		Entity::Entity button = Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
		button.addComponent<Component::Watcher>(Component::Watcher{
			[scene, button]() {
				auto& container = button.getComponent<Component::Container>();
				if (scene->editor && scene->editor->getBlockType() == Component::BlockType::BALLOON)
					container.borderColor = GREEN;
				else
					container.borderColor = { 0, 0, 0, 0 };
			},
		});
	}
	yPosition += 35.0f;
	{
		const Vector2 buttonSize = { 400.0f - panePadding.x * 2, 30.0f };
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition };
		const std::string text = "Spikes";
		const Color textColor = BLACK;
		const int fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = RED;
		const auto onClick = [scene]() {
			if (scene->editor)
				scene->editor->setType(Component::BlockType::SPIKES);
		};
		Entity::Entity button = Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
		button.addComponent<Component::Watcher>(Component::Watcher{
			[scene, button]() {
				auto& container = button.getComponent<Component::Container>();
				if (scene->editor && scene->editor->getBlockType() == Component::BlockType::SPIKES)
					container.borderColor = GREEN;
				else
					container.borderColor = { 0, 0, 0, 0 };
			},
		});
	}
	yPosition += 50.0f;
	{
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + yPosition};
		const std::string text = "Total no. of breakable:";
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

	// save button
	{
		const Vector2 buttonSize = { (400.0f - panePadding.x * 2) / 2, 30.0f };
		const Vector2 position = { panePosition.x + panePadding.x, screenHeight - panePadding.y - buttonSize.y};
		const std::string text = "Save";
		const Color textColor = BLACK;
		const int fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = GREEN;
		const auto onClick = [scene]() {
			if (scene->editor)
				scene->editor->saveLevel();

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
			scene->gotoCustoms();
		};

		Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}
	{
		const Vector2 size = { 400, screenHeight  };
		const Color backgroundColor = GRAY;
		Entity::createPanel(scene, panePosition, size, backgroundColor);
	}
}