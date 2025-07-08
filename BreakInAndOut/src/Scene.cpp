#include "../include/Scene.hpp"
#include "../include/Entities.hpp"
#include "../include/Systems.hpp"
#include "../include/Utils/math.hpp"

Scene::Scene()
{
	for (size_t i = 0; i < 20; i++)
	{
	Entity::createBall(this, { Utils::random(0.0f, 1920.0f), Utils::random(0.0f, 1080.0f) }, { Utils::random(-10.0f, 10.0f), Utils::random(-10.0f, 10.0f)}, 10.0f);
	}
	for (size_t i = 0; i < 20; i++)
	{
		Entity::createBlock(this, { Utils::random(0.0f, 1920.0f), Utils::random(0.0f, 1080.0f) }, { 100.0f, 50.0f }, WHITE);
	}
}

Scene::~Scene()
{
}

Entity::Entity Scene::createEntity()
{
	entt::entity entityHandle = registry.create();
	return Entity::Entity(entityHandle, this);
}

void Scene::render()
{
	System::collision(this);
	System::integrate(this);

	BeginDrawing();

	ClearBackground(BLACK);

	System::draw2D(this);

	EndDrawing();
}
