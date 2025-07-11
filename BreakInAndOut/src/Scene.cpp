#include "../include/Scene.hpp"
#include "../include/Entities.hpp"
#include "../include/Systems.hpp"
#include "../include/utils/math.hpp"
#include "../include/utils/Editor.hpp"
#include <iostream>

Scene::Scene()
{
	gotoMenu();

}

Scene::~Scene()
{
	if (editor)
	{
		delete editor;
		editor = nullptr;
	}
}

Entity::Entity Scene::createEntity()
{
	entt::entity entityHandle = registry.create();
	return Entity::Entity(entityHandle, this);
}

void Scene::render()
{
	unloadingPage = false;
	if (loadingPage || unloadingPage)
	{
	}
	else
	{
		System::switchLayer(this);
		System::paddleMovement(this);
		System::collision(this);
		System::integrate(this);
		System::handleMouseClick(this);
		if (editor)
			System::edit(this);
	}


	BeginDrawing();

	ClearBackground(BLACK);
	
	System::draw2D(this);

	EndDrawing();
}

void Scene::gotoMenu()
{
	registry.clear();
	unloadingPage = true;
	if (editor)
	{
		delete editor;
		editor = nullptr;
	}
	
	const float screenWidth = GetScreenWidth();
	const float screenHeight = GetScreenHeight();

	{
		const std::string text = "BreakiN";
		const Color textColor = WHITE;
		const Vector2 position = { 600.0f, 200.0f };
		const int fontSize = 200;
		Entity::createText(this, position, text, textColor, fontSize);
	}

	{
		const Vector2 buttonSize = { 300.0f, 100.0f };
		const Vector2 position = { screenWidth * 0.5f - buttonSize.x * 0.5f, 500 };
		const std::string text = "Start";
		const Color textColor = WHITE;
		const int fontSize = 100;
		const Vector2 padding = { 10.0f, 5.0f };
		const Color boxColor = DARKGRAY;
		const auto onClick = [this]() {
			gotoLevel(1);
		};

		Entity::createButton(this, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}

	{
		const Vector2 buttonSize = { 165.0f, 50.0f };
		const Vector2 position = { screenWidth * 0.5f - buttonSize.x * 0.5f, 620 };
		const std::string text = "Editor";
		const Color textColor = WHITE;
		const int fontSize = 50;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = DARKGRAY;
		const auto onClick = [this]() {
			gotoEditor();
		};

		Entity::createButton(this, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}

	{
		const Vector2 buttonSize = { 105.0f, 50.0f };
		const Vector2 position = { screenWidth * 0.5f - buttonSize.x * 0.5f, 780 };
		const std::string text = "Exit";
		const Color textColor = WHITE;
		const int fontSize = 50;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = DARKGRAY;
		const auto onClick = [this]() {
			gotoMenu();
		};

		Entity::createButton(this, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}

	{
		const float padding = 50.0f;
		const Vector2 position = { padding, padding };
		const Vector2 size = { screenWidth - padding * 2, screenHeight - padding *2 };
		const Color backgroundColor = { 255, 255, 255, 50 };
		Entity::createPanel(this, position, size, backgroundColor);
	}
}

void Scene::gotoEditor()
{
	registry.clear();
	unloadingPage = true;
	if (editor)
		delete editor;
	editor = new Utils::Editor();
	editor->loadFromFile(this);
	
	const float screenWidth = GetScreenWidth();
	const float screenHeight = GetScreenHeight();

	const Vector2 panePosition = { screenWidth  - 400.0f, 0.0f };
	const Vector2 panePadding = { 50.0f, 50.0f };
	{
		const Vector2 buttonSize = { 400.0f - panePadding.x * 2, 50.0f };
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y };
		const std::string text = "Wall";
		const Color textColor = BLACK;
		const int fontSize = 50;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = WHITE;
		const auto onClick = [this]() {
			editor->setType(Component::BlockType::WALL);
		};

		Entity::createButton(this, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}
	{
		const Vector2 buttonSize = { 400.0f - panePadding.x * 2, 50.0f };
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + 70 };
		const std::string text = "Normal";
		const Color textColor = BLACK;
		const int fontSize = 50;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = BLUE;
		const auto onClick = [this]() {
			editor->setType(Component::BlockType::NORMAL);
		};

		Entity::createButton(this, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}
	{
		const Vector2 buttonSize = { 400.0f - panePadding.x * 2, 50.0f };
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + 140 };
		const std::string text = "Balloon";
		const Color textColor = BLACK;
		const int fontSize = 50;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = GREEN;
		const auto onClick = [this]() {
			editor->setType(Component::BlockType::BALLOON);
		};

		Entity::createButton(this, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}
	{
		const Vector2 buttonSize = { 400.0f - panePadding.x * 2, 50.0f };
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + 210 };
		const std::string text = "Spikes";
		const Color textColor = BLACK;
		const int fontSize = 50;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = RED;
		const auto onClick = [this]() {
			editor->setType(Component::BlockType::SPIKES);
		};

		Entity::createButton(this, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}
	{
		const Vector2 buttonSize = { 400.0f - panePadding.x * 2, 50.0f };
		const Vector2 position = { panePosition.x + panePadding.x, panePosition.y + panePadding.y + 400 };
		const std::string text = "Save";
		const Color textColor = BLACK;
		const int fontSize = 50;
		const Vector2 padding = { 5.0f, 3.0f };
		const Color boxColor = WHITE;
		const auto onClick = [this]() {
			editor->saveLevel();
		};

		Entity::createButton(this, position, buttonSize, text, textColor, fontSize, padding, boxColor, onClick);
	}
	{
		const Vector2 size = { 400, screenHeight  };
		const Color backgroundColor = GRAY;
		Entity::createPanel(this, panePosition, size, backgroundColor);
	}
}

void Scene::gotoLevel(int level)
{
	registry.clear();
	unloadingPage = true;
	if (editor)
	{
		delete editor;
		editor = nullptr;
	}
	
	Entity::createPaddle(this, { 860.0f, 1000.0f }, { 200.0f, 20.0f }, LIGHTGRAY);
	Entity::BlockConfigFactory blockConfigFactory;
	for (size_t i = 0; i < 20; i++)
	{
		Entity::createBall(this, { Utils::random(0.0f, 1920.0f), Utils::random(0.0f, 1080.0f) }, { Utils::random(-10.0f, 10.0f), Utils::random(-10.0f, 10.0f)}, 10.0f);
	}

	blockConfigFactory.setType(Component::BlockType::NORMAL);
	blockConfigFactory.setLayer(Component::GhostLayer::REAL);
	for (size_t i = 0; i < 10; i++)
	{
		blockConfigFactory.randomPosition(0.0f, 1920.0f, 0.0f, 1080.0f);
		const Entity::BlockConfig config = blockConfigFactory.createConfig();
		Entity::createBlock(this, config);
	}
	blockConfigFactory.setType(Component::BlockType::WALL);
	blockConfigFactory.setLayer(Component::GhostLayer::ONE);
	for (size_t i = 0; i < 10; i++)
	{
		blockConfigFactory.randomPosition(0.0f, 1920.0f, 0.0f, 1080.0f);
		const Entity::BlockConfig config = blockConfigFactory.createConfig();
		Entity::createBlock(this, config);
	}
	blockConfigFactory.setType(Component::BlockType::BALLOON);
	blockConfigFactory.setLayer(Component::GhostLayer::TWO);
	for (size_t i = 0; i < 10; i++)
	{
		blockConfigFactory.randomPosition(0.0f, 1920.0f, 0.0f, 1080.0f);
		const Entity::BlockConfig config = blockConfigFactory.createConfig();
		Entity::createBlock(this, config);
	}
	blockConfigFactory.setType(Component::BlockType::SPIKES);
	blockConfigFactory.setLayer(Component::GhostLayer::THREE);
	for (size_t i = 0; i < 10; i++)
	{
		blockConfigFactory.randomPosition(0.0f, 1920.0f, 0.0f, 1080.0f);
		const Entity::BlockConfig config = blockConfigFactory.createConfig();
		Entity::createBlock(this, config);
	}
}
