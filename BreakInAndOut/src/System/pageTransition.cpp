#include "../../include/Systems.hpp"
#include <iostream>
#include <bitset>

void System::pageTransition(Scene* scene) 
{
	static float t = 0.0f;

	const auto view = scene->registry.view<Component::Displacement>();

	if (t >= 1.0f)
	{
		if (scene->unloadingPage)
		{
			if (scene->loadPageCallBack)
				scene->loadPageCallBack();
			scene->loadPageCallBack = nullptr;
			scene->loadingPage = true;
			scene->unloadingPage = false;
		}
		else if (scene->loadingPage)
		{
			scene->loadingPage = false;
			for (const auto& entity : view)
			{
				auto& displacement = view.get<Component::Displacement>(entity);
				displacement.displacement = { 0, 0 };
			}
		}
		t = 0.0f;
	}

	float value = 0.0f;
	if (scene->loadingPage)
		value = 1.0f - t;
	else if (scene->unloadingPage)
		value = t;
	else 
		return;

	float magnitude = Utils::bezierCubic(0.0f, 0.0f, 0.1f, 1.0f, value);
	for (const auto& entity : view)
	{
		auto& displacement = view.get<Component::Displacement>(entity);
		displacement.displacement = Vector2Scale(displacement.from, magnitude);
	}

	t += GetFrameTime() * 2;
}
