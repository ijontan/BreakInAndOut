#pragma once
#include "entt/entt.hpp"
#include "raylib.h"
#include "Component/BlockState.hpp"
#include "utils/Sounds.hpp"

namespace Entity {
	struct Entity;
}

namespace Utils {
	class Editor;
	class Level;
}

class Scene
{
public:
	Scene();
	~Scene(void);

	Entity::Entity createEntity();
	void render();

	entt::registry registry;

	unsigned char mask = Component::GhostLayer::REAL | Component::GhostLayer::ONE;
	bool unloadingPage = false;
	bool loadingPage = false;
	bool shouldClose = false;
	std::function<void()> loadPageCallBack = nullptr;
	Utils::Editor* editor = nullptr;
	Utils::Sounds sounds;
	Utils::Level* level = nullptr;
	float timeBeforeNextStage = 0.0f;

	static const std::vector<std::string> storyLevelsOrders;
	void gotoMenu();
	void gotoEditor(const std::string fileName);
	void gotoLevel(const std::string fileName, bool isCustom);
	void gotoCustoms();
	void clean();
};
