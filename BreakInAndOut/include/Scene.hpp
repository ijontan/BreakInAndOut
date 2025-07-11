#pragma once
#include "entt/entt.hpp"
#include "raylib.h"
#include "Component/BlockState.hpp"

namespace Entity {
	struct Entity;
}

namespace Utils {
	class Editor;
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
	std::function<void()> loadPageCallBack = nullptr;
	bool loadingPage = false;
	Utils::Editor* editor = nullptr;

private:
	void gotoMenu();
	void gotoEditor();
	void gotoLevel(int level);
};
