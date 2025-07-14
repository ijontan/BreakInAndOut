
#include "../../include/UI.hpp"
#include "../../include/entities.hpp"
#include "../../include/utils/Editor.hpp"
#include "../../include/Component/Watcher.hpp"
#include <string>
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

void UI::selectCustomLevel(Scene* scene) {

	const float screenWidth = GetScreenWidth();
	const float screenHeight = GetScreenHeight();

	const Vector2 panePosition = { screenWidth  - 400.0f, 0.0f };
	const Vector2 panePadding = { 50.0f, 50.0f };

	int i = 0;
	createDir(CUSTOM_LEVEL_PATH);
	for (const auto& entry : std::filesystem::directory_iterator(CUSTOM_LEVEL_PATH))
	{
		if (!entry.is_regular_file() || entry.path().extension().string() != LEVEL_FILE_EXTENSION)
			continue;
		std::string fileName = entry.path().filename().string();

		// remove extension
		const auto indexOfDot = fileName.find_last_of(".");
		fileName = fileName.substr(0, indexOfDot);

		
		const Vector2 position = { panePadding.x, panePadding.y + 60 * i};
		{
			const Vector2 textPosition = { position.x + 10, position.y + 10 };
			const Color color = WHITE;
			const float fontSize = 30;
			Entity::createText(scene, textPosition, fileName, color, fontSize);
		}
		{
			const Vector2 buttonSize = { 100.0f, 30.0f };
			const Vector2 buttonPosition = { screenWidth - 410 - buttonSize.x - panePadding.x, position.y + 10 };
			const std::string text = "Edit";
			const Color textColor = BLACK;
			const int fontSize = 30;
			const Vector2 padding = { 5.0f, 3.0f };
			const Color boxColor = GREEN;
			const auto onClick = [scene, fileName]() {
				scene->gotoEditor(fileName);
			};
			Entity::createButton(scene, buttonPosition, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
		}
		{
			const Vector2 buttonSize = { 100.0f, 30.0f };
			const Vector2 buttonPosition = { screenWidth - 510 - buttonSize.x - panePadding.x, position.y + 10 };
			const std::string text = "Play";
			const Color textColor = BLACK;
			const int fontSize = 30;
			const Vector2 padding = { 5.0f, 3.0f };
			const Color boxColor = WHITE;
			const auto onClick = [scene, fileName]() {
				scene->gotoLevel(fileName, true);
			};
			Entity::createButton(scene, buttonPosition, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
		}
		{
			const Vector2 size = { screenWidth - 400 - panePadding.x * 2, 50 };
			const Color backgroundColor = DARKGRAY;
			Entity::createPanel(scene, position, size, backgroundColor);
		}
		++i;
	}

	// new Custom button
	{
		const Vector2 buttonSize = { (400.0f - panePadding.x * 2), 30.0f };
		const Vector2 position = { panePosition.x + panePadding.x, screenHeight - panePadding.y - buttonSize.y - 40.0f};
		const std::string text = "Create New";
		const Color textColor = BLACK;
		const int fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = GREEN;
		const auto onClick = [scene]() {
			scene->gotoEditor("");
		};
		Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}

	// new Custom button
	{
		const Vector2 buttonSize = { (400.0f - panePadding.x * 2), 30.0f };
		const Vector2 position = { panePosition.x + panePadding.x, screenHeight - panePadding.y - buttonSize.y};
		const std::string text = "Return";
		const Color textColor = BLACK;
		const int fontSize = 30;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = RED;
		const auto onClick = [scene]() {
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
