#include "../../../include/Entities.hpp"
#include "../../../include/Entity.hpp"

namespace Entity {
	Entity createPanel(Scene* scene, Vector2 position, Vector2 size, Color color)
	{
		Entity panel = scene->createEntity();
		panel.addComponent<Component::Container>(position, size, color);
		panel.addComponent<Component::Displacement>(position);
		return panel;
	}
}
