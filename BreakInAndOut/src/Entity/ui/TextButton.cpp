#include "../../../include/Entities.hpp"
#include "../../../include/Entity.hpp"

namespace Entity {
	Entity createTextButton(Scene* scene, Vector2 position, Vector2 size, std::string text, Color textColor, std::function<void()> onClick)
	{
		Entity button = scene->createEntity();
		button.addComponent<Component::MouseHitBox>(position, size, onClick);
		button.addComponent<Component::Text>(position, text, textColor, 20);
		button.addComponent<Component::Displacement>(position);
		return button;
	}
}
