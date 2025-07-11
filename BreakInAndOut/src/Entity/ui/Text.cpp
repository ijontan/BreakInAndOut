#include "../../../include/Entities.hpp"
#include "../../../include/Entity.hpp"

namespace Entity {
	Entity createText(Scene* scene, Vector2 position, const std::string& text, Color color, int fontSize)
	{
		Entity textEntity = scene->createEntity();
		textEntity.addComponent<Component::Position>(position);
		textEntity.addComponent<Component::Text>(position, text, color, fontSize);
		return textEntity;
	}
}