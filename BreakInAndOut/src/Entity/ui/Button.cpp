#include "../../../include/Entities.hpp"
#include "../../../include/Entity.hpp"
#include <iostream>

namespace Entity{
	Entity createButton(Scene* scene, Vector2 position, Vector2 size, const std::string& text, Color textColor, int fontSize, Vector2 padding, Color boxColor, std::function<void()> onClick) 
	{
		Entity button = scene->createEntity();
		button.addComponent<Component::MouseHitBox>(position, size, onClick, 
			[button]() {
				Component::Container& container = button.getComponent<Component::Container>();
				container.backgroundColor.a = 255;
			},
			[button]() {
				Component::Container& container = button.getComponent<Component::Container>();
				container.backgroundColor.a = 100;
			}
		);
		boxColor.a = 100;
		button.addComponent<Component::Container>(position, size, boxColor, Color{ 0, 0, 0, 0 });
		position.x += padding.x;
		position.y += padding.y;
		button.addComponent<Component::Text>(position, text, textColor, fontSize);
		button.addComponent<Component::Displacement>(position);
		return button;
	}
}
