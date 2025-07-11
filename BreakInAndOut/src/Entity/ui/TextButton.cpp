#include "../../../include/Entities.hpp"
#include "../../../include/Entity.hpp"

namespace Entity {
	Entity createTextButton(Scene* scene, Vector2 position, Vector2 size, std::string text, Color textColor, std::function<void()> onClick)
	{
		Entity panel = scene->createEntity();
		panel.addComponent<Component::MouseHitBox>(position, size, onClick);
		panel.addComponent<Component::Text>(position, text, textColor, 20);
		return panel;
	}
}
