#include "../../include/Systems.hpp"
#include "../../include/utils/Editor.hpp"
#include <iostream>

void System::switchLayer(Scene* scene)
{
	bool switched = false;
	if (IsKeyPressed(KEY_R) && scene->editor)
	{
		scene->mask = Component::GhostLayer::REAL;
		switched = true;
	}
	if (IsKeyPressed(KEY_ONE))
	{
		scene->mask = Component::GhostLayer::ONE;
		switched = true;
	}
	if (IsKeyPressed(KEY_TWO))
	{ 
		scene->mask = Component::GhostLayer::TWO;
		switched = true;
	}
	if (IsKeyPressed(KEY_THREE))
	{
		scene->mask = Component::GhostLayer::THREE;
		switched = true;
	}
	if (IsKeyPressed(KEY_FOUR))
	{ 
		scene->mask = Component::GhostLayer::FOUR;
		switched = true;
	}
	if (IsKeyPressed(KEY_FIVE))
	{
		scene->mask = Component::GhostLayer::FIVE;
		switched = true;
	}
	if (IsKeyPressed(KEY_SIX))
	{
		scene->mask = Component::GhostLayer::SIX;
		switched = true;
	}
	if (IsKeyPressed(KEY_SEVEN))
	{
		scene->mask = Component::GhostLayer::SEVEN;
		switched = true;
	}
	if (!switched)
		return;

	if (!scene->editor)
		scene->mask |= Component::GhostLayer::REAL;
	else
		scene->editor->setLayer(static_cast<Component::GhostLayer>(scene->mask));

	const auto view = scene->registry.view<Component::BlockState, Component::RectangleShape>();

	for (const auto& entity : view)
	{
		Component::BlockState& blockState = view.get<Component::BlockState>(entity);
		const Component::RectangleShape& rectangleShape = view.get<Component::RectangleShape>(entity);
		const auto newStartOpacity = static_cast<unsigned char>(Utils::linearInterpolation(blockState.startOpacity, blockState.targetOpacity, blockState.t));
		blockState.setColorTransition(scene->mask, newStartOpacity);
	}
}