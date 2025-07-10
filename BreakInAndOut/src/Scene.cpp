#include "../include/Scene.hpp"
#include "../include/Entities.hpp"
#include "../include/Systems.hpp"
#include "../include/Utils/math.hpp"

Scene::Scene()
{
	Entity::createPaddle(this, { 860.0f, 1000.0f }, { 200.0f, 20.0f }, LIGHTGRAY);
	for (size_t i = 0; i < 20; i++)
	{
		Entity::createBall(this, { Utils::random(0.0f, 1920.0f), Utils::random(0.0f, 1080.0f) }, { Utils::random(-10.0f, 10.0f), Utils::random(-10.0f, 10.0f)}, 10.0f);
	}
	for (size_t i = 0; i < 1000; i++)
	{
		Entity::createBlock(this, { Utils::random(0.0f, 1920.0f), Utils::random(0.0f, 1080.0f) }, { 100.0f, 50.0f }, BLUE, 
			Component::NORMAL, Component::GhostLayer::ONE);
	}
	for (size_t i = 0; i < 10; i++)
	{
		Entity::createBlock(this, { Utils::random(0.0f, 1920.0f), Utils::random(0.0f, 1080.0f) }, { 100.0f, 50.0f }, LIGHTGRAY, 
			Component::WALL, Component::GhostLayer::ONE);
	}
	for (size_t i = 0; i < 10; i++)
	{
		Entity::createBlock(this, { Utils::random(0.0f, 1920.0f), Utils::random(0.0f, 1080.0f) }, { 100.0f, 50.0f }, LIGHTGRAY, 
			Component::WALL, Component::GhostLayer::TWO);
	}
	for (size_t i = 0; i < 10; i++)
	{
		Entity::createBlock(this, { Utils::random(0.0f, 1920.0f), Utils::random(0.0f, 1080.0f) }, { 100.0f, 50.0f }, GREEN, 
			Component::BALLOON, Component::GhostLayer::THREE);
	}
	for (size_t i = 0; i < 10; i++)
	{
		Entity::createBlock(this, { Utils::random(0.0f, 1920.0f), Utils::random(0.0f, 1080.0f) }, { 100.0f, 50.0f }, RED, 
			Component::SPIKES, Component::GhostLayer::FOUR);
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
	System::switchLayer(this);
	System::paddleMovement(this);
	System::collision(this);
	System::integrate(this);

	BeginDrawing();

	ClearBackground(BLACK);

	System::draw2D(this);

	EndDrawing();
}
