#pragma once

#include "Scene.hpp"
#include "Component/Position.hpp"
#include "Component/Velocity.hpp"
#include "Component/Shapes.hpp"
#include "Utils/collisionDetection.hpp"

namespace System {
	void collision(Scene* scene);
	void draw2D(Scene* scene);
	void integrate(Scene* scene);
};
