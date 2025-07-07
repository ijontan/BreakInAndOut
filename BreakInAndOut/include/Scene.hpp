#pragma once
#include "entt/entt.hpp"
#include "raylib.h"

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
};
