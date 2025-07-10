#pragma once
#include "entt/entt.hpp"
#include "raylib.h"
#include "Component/BlockState.hpp"

namespace Entity {
	struct Entity;
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
};
