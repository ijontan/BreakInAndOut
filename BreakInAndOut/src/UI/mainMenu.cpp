#include "../../include/UI.hpp"
#include "../../include/entities.hpp"

void UI::mainMenu(Scene* scene) 
{
	
	const float screenWidth = static_cast<float>(GetScreenWidth());
	const float screenHeight = static_cast<float>(GetScreenHeight());

	{
		const std::string text = "BreakiN";
		const Color textColor = WHITE;
		const Vector2 position = { 600.0f, 200.0f };
		const int fontSize = 200;
		Entity::createText(scene, position, text, textColor, fontSize);
	}

	{
		const Vector2 buttonSize = { 300.0f, 100.0f };
		const Vector2 position = { screenWidth * 0.5f - buttonSize.x * 0.5f, 500 };
		const std::string text = "Start";
		const Color textColor = WHITE;
		const int fontSize = 100;
		const Vector2 padding = { 10.0f, 5.0f };
		const Color boxColor = DARKGRAY;
		const auto onClick = [scene]() {
			scene->gotoLevel("1", false);
		};

		Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}

	{
		const Vector2 buttonSize = { 180.0f, 50.0f };
		const Vector2 position = { screenWidth * 0.5f - buttonSize.x * 0.5f, 620 };
		const std::string text = "Custom";
		const Color textColor = WHITE;
		const int fontSize = 50;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = DARKGRAY;
		const auto onClick = [scene]() {
			scene->gotoCustoms();
		};

		Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}

	{
		const Vector2 buttonSize = { 105.0f, 50.0f };
		const Vector2 position = { screenWidth * 0.5f - buttonSize.x * 0.5f, 780 };
		const std::string text = "Exit";
		const Color textColor = WHITE;
		const int fontSize = 50;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = DARKGRAY;
		const auto onClick = [scene]() {
			scene->shouldClose = true;
		};

		Entity::createButton(scene, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}

	{
		const float padding = 50.0f;
		const Vector2 position = { padding, padding };
		const Vector2 size = { screenWidth - padding * 2, screenHeight - padding *2 };
		const Color backgroundColor = { 50, 50, 50, 220 };
		Entity::createPanel(scene, position, size, backgroundColor);
	}

}