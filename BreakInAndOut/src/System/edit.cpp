#include "../../include/Systems.hpp"
#include "../../include/utils/Editor.hpp"
#include <iostream>
#include <cmath>

void System::edit(Scene* scene)
{
	const auto screenWidth = GetScreenWidth();
	const auto screenHeight = GetScreenHeight();

	const auto view = scene->registry.view<Component::MouseHitBox, Component::BlockState>();
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		const auto mousePos = GetMousePosition();
		if (mousePos.x > screenWidth - 400)
			return;
		bool found = false;
		for (const auto& entity : view)
		{
			const Component::MouseHitBox& hitBox = view.get<Component::MouseHitBox>(entity);
			const Component::BlockState& blockState = view.get<Component::BlockState>(entity);
			if (hitBox.isMouseOver() && Utils::isBitSet(scene->mask, blockState.layer))
			{
				scene->editor->selectBlock(Entity::Entity(entity, scene));
				found = true;
				scene->sounds.playSound(blockState.hitSound);
				break;
			}
		}
		if (!found)
			scene->editor->createBlock(scene);
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		auto mousePos = GetMousePosition();
		mousePos = { std::clamp(mousePos.x, 0.0f ,screenWidth - 400.0f), std::clamp(mousePos.y, 0.0f , static_cast<float>(screenHeight))};
		scene->editor->setPosition(mousePos);
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		scene->editor->unselectBlock();
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		bool found = false;
		for (const auto& entity : view)
		{
			const Component::MouseHitBox& hitBox = view.get<Component::MouseHitBox>(entity);
			const Component::BlockState& blockState = view.get<Component::BlockState>(entity);
			if (hitBox.isMouseOver() && Utils::isBitSet(scene->mask, blockState.layer))
			{
				scene->editor->selectBlock(Entity::Entity(entity, scene));
				found = true;
				break;
			}
		}
		if (found)
			scene->editor->deleteSelectedBlock(scene);
	}
}
