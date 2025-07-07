#include "../include/Scene.hpp"
#include "../include/Entities.hpp"
#include "../include/Systems.hpp"
#include "../include/Utils/math.hpp"

Scene::Scene()
{
	for (int i = 0; i < 1000; i++)
	{
		Entity::createBall(this, { Utils::random(0.0f, 1920.0f), Utils::random(0.0f, 1080.0f) }, { Utils::random(-5.0f, 5.0f), Utils::random(-5.0f, 5.0f)}, 10.0f);
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
	integrate(this);

	BeginDrawing();

	ClearBackground(BLACK);

	

	const auto view = registry.view<Component::Position, float>();

	for (const auto& entity : view)
	{
		const Vector2& position = view.get<Component::Position>(entity);
		const float radius = view.get<float>(entity);
		DrawCircleV(position, radius, WHITE);
	}


	EndDrawing();
}
