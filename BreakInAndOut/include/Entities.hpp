#pragma once
#include "Entity.hpp"
#include "Scene.hpp"
#include "Component/Position.hpp"
#include "Component/Velocity.hpp"

namespace Entity {
	Entity createBall(Scene* scene, Vector2 position, Vector2 velocity, float radius);
};
