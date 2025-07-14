#include "../include/Scene.hpp"
#include "../include/Entities.hpp"
#include "../include/Systems.hpp"
#include "../include/utils/math.hpp"
#include "../include/utils/Editor.hpp"
#include "../include/UI.hpp"
#include <iostream>
#include <string>


const std::vector<std::string> Scene::storyLevelsOrders = { "1","2","3","4","5","6","7","8" };

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
	if (loadingPage || unloadingPage)
	{
		System::pageTransition(this);
	}
	else
	{
		System::checkWin(this);
		System::damagePaddle(this);
		System::launchBall(this);
		System::switchLayer(this);
		System::paddleMovement(this);
		System::collision(this);
		if (timeBeforeNextStage == 0.0f)
			System::integrate(this);
		System::handleMouseClick(this);
		if (editor)
			System::edit(this);
		System::watch(this);
	}
	System::music(this);


	BeginDrawing();

	ClearBackground(BLACK);
	
	System::draw2D(this);

	EndDrawing();
}

void Scene::gotoMenu()
{
	unloadingPage = true;
	loadPageCallBack = [this]() {
		registry.clear();
		clean();
		level = new Utils::Level("menu", false);
		level->loadFile();
		level->setupLevel(this);
		{
			const Vector2 position = { 1200.0f, 900.0f };
			const Vector2 velocity = { -6.6f, 0.0f };
			const float radius = 10.0f;
			Entity::createBall(this, position, velocity, radius);
		}
		UI::mainMenu(this);
		};
}

void Scene::gotoEditor(const std::string fileName)
{
	unloadingPage = true;
	loadPageCallBack = [this, fileName]() {
		registry.clear();
		clean();
		std::cout << "Editing: " << fileName << std::endl;
		editor = new Utils::Editor(fileName);
		editor->loadFromFile(this);
		mask = Component::GhostLayer::REAL;
		UI::editPanel(this);
		};
}

static void generateTutorialText(Scene* scene, const std::string& fileName)
{
	std::string text;
	if (fileName == "1")
		text = "Use left/right arrow key to move paddle. And Space bar to shot the ball.";
	else if (fileName == "2")
		text = "Use X/C to aim the ball";
	else if (fileName == "3")
		text = "Let's try another one";
	else if (fileName == "4")
		text = "Use number key 1 - 7 to hit blocks in different dimension.";
	else if (fileName == "5")
		text = "Hmm.. how do I get there?";
	else if (fileName == "6")
		text = "You are on your own now.";

	const Vector2 position = { 50.0f, 50.0f};
	const Color color = WHITE;
	const int fontSize = 30;
	Entity::createText(scene, position, text, color, fontSize);
}

void Scene::gotoLevel(const std::string fileName, bool isCustom)
{
	unloadingPage = true;
	loadPageCallBack = [this, fileName, isCustom]() {
		const float screenWidth = static_cast<float>(GetScreenWidth());
		registry.clear();
		clean();
		std::cout << "Playing level: " << fileName << ", isCustom: " << isCustom << std::endl;
		level = new Utils::Level(fileName, isCustom);
		level->loadFile();
		level->setupLevel(this);
		{
			const Vector2 size = { 200.0f, 20.0f };
			const Vector2 position = { (screenWidth - 400.0f) * 0.5f - size.x * 0.5f, 1000.0f };
			const Color color = LIGHTGRAY;
			Entity::createPaddle(this, position, size, color);
		}
		{
			const Vector2 position = { 0.0f, 0.0f };
			const Vector2 velocity = { 0.0f, 0.0f };
			const float radius = 10.0f;
			Entity::createBall(this, position, velocity, radius);
		}
		UI::levelPanel(this);
		if (!isCustom)
			generateTutorialText(this, fileName);
		};
}

void Scene::gotoCustoms()
{
	unloadingPage = true;
	loadPageCallBack = [this]() {
		registry.clear();
		clean();
		UI::selectCustomLevel(this);
		};
}

void Scene::clean() 
{
	if (editor)
	{
		delete editor;
		editor = nullptr;
	}
	if (level)
	{
		delete level;
		level = nullptr;
	}
	timeBeforeNextStage = 0.0f;
	mask = Component::GhostLayer::REAL | Component::GhostLayer::ONE;
}
