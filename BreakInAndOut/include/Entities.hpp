#pragma once
#include "Entity.hpp"
#include "Scene.hpp"
#include "Component/Position.hpp"
#include "Component/Velocity.hpp"
#include "Component/Shapes.hpp"
#include "Component/CollisionBox.hpp"

namespace Entity {
	Entity createBall(Scene* scene, Vector2 position, Vector2 velocity, float radius);
	Entity createBlock(Scene* scene, Vector2 position, Vector2 size, Color color = WHITE);
};
