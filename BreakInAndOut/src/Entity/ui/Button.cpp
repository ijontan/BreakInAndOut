#include "../../../include/Entities.hpp"
#include "../../../include/Entity.hpp"

namespace Entity{
	Entity createButton(Scene* scene, Vector2 position, Vector2 size, const std::string& text, Color textColor, int fontSize, Vector2 padding, Color boxColor, std::function<void()> onClick) 
	{
		Entity button = scene->createEntity();
		button.addComponent<Component::MouseHitBox>(position, size, onClick);
		button.addComponent<Component::Container>(position, size, boxColor);
		position.x += padding.x;
		position.y += padding.y;
		button.addComponent<Component::Text>(position, text, textColor, fontSize);
		return button;
	}
}
