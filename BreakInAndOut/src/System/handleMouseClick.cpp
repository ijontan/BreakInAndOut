#include "../../include/Systems.hpp"

void System::handleMouseClick(Scene* scene)
{
	const auto view = scene->registry.view<Component::MouseHitBox>();
	for (const auto& entity : view)
	{
		if (scene->unloadingPage)
			return;
		Component::MouseHitBox& hitBox = view.get<Component::MouseHitBox>(entity);
		hitBox.checkClick();
		hitBox.checkOnHoverEnter();
		hitBox.checkOnHoverLeave();
	}
}