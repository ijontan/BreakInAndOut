#include "../../include/Systems.hpp" 
#include "../../include/utils/Level.hpp"


void System::music(Scene* scene)
{
	const float startTime = 1.70f;
	static float time = startTime;
	if (!scene->level || scene->level->isCustom || scene->level->getName() != "menu")
	{
		time = startTime;
		return;
	}

	time += GetFrameTime();
	if (time >= 6.0f)
	{
		{
			const Vector2 position = { 770.0f, 1000.0f };
			const Vector2 velocity = { -6.73f, -6.73f };
			const float radius = 10.0f;
			Entity::createBall(scene, position, velocity, radius);
		}
		time = 0.0f;
	}

}
