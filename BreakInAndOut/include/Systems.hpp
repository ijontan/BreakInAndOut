#pragma once

#include "Scene.hpp"
#include "Component/Position.hpp"
#include "Component/Velocity.hpp"
#include "Component/Shapes.hpp"
#include "Component/CollisionBox.hpp"
#include "Component/BlockState.hpp"
#include "Component/PaddleState.hpp"
#include "Component/Watcher.hpp"
#include "Component/Displacement.hpp"
#include "Component/ui/MouseHitBox.hpp"
#include "Component/ui/Text.hpp"
#include "Component/ui/Container.hpp"
#include "utils/collisionDetection.hpp"
#include "utils/masking.hpp"
#include "utils/bezier.hpp"

namespace System {
	void checkWin(Scene* scene);
	void collision(Scene* scene);
	void draw2D(Scene* scene);
	void integrate(Scene* scene);
	void paddleMovement(Scene* scene);
	void pageTransition(Scene* scene);
	void switchLayer(Scene* scene);
	void handleMouseClick(Scene* scene);
	void edit(Scene* scene);
	void watch(Scene* scene);
	void launchBall(Scene* scene);
	void damagePaddle(Scene* scene);
	void music(Scene* scene);
};
