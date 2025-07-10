#include "../../include/Systems.hpp"
#include <iostream>

namespace System
{
	void switchLayer(Scene* scene)
	{
		bool switched = false;
		if (IsKeyPressed(KEY_ONE))
		{
			scene->mask = Component::GhostLayer::REAL | Component::GhostLayer::ONE;
			switched = true;
		}
		if (IsKeyPressed(KEY_TWO))
		{ 
			scene->mask = Component::GhostLayer::REAL | Component::GhostLayer::TWO;
			switched = true;
		}
		if (IsKeyPressed(KEY_THREE))
		{
			scene->mask = Component::GhostLayer::REAL | Component::GhostLayer::THREE;
			switched = true;
		}
		if (IsKeyPressed(KEY_FOUR))
		{ 
			scene->mask = Component::GhostLayer::REAL | Component::GhostLayer::FOUR;
			switched = true;
		}
		if (IsKeyPressed(KEY_FIVE))
		{
			scene->mask = Component::GhostLayer::REAL | Component::GhostLayer::FIVE;
			switched = true;
		}
		if (IsKeyPressed(KEY_SIX))
		{
			scene->mask = Component::GhostLayer::REAL | Component::GhostLayer::SIX;
			switched = true;
		}
		if (IsKeyPressed(KEY_SEVEN))
		{
			scene->mask = Component::GhostLayer::REAL | Component::GhostLayer::SEVEN;
			switched = true;
		}
		if (!switched)
			return;

		const auto view = scene->registry.view<Component::BlockState, Component::RectangleShape>();

		for (const auto& entity : view)
		{
			Component::BlockState& blockState = view.get<Component::BlockState>(entity);
			const Component::RectangleShape& rectangleShape = view.get<Component::RectangleShape>(entity);
			blockState.startOpacity = static_cast<unsigned char>(Utils::linearInterpolation(blockState.startOpacity, blockState.targetOpacity, blockState.t));
			if (!Utils::isBitSet(scene->mask, blockState.layer))
			{
				int layerIndex = Utils::getBitIndex(blockState.layer);
				int selectedLayer = Utils::getBitIndex(Utils::clearBit(scene->mask, Component::GhostLayer::REAL));
				auto diff = std::abs(layerIndex - selectedLayer);
				blockState.targetOpacity = std::clamp(70 - diff * 20, 0, 255);
			}
			else
			{
				blockState.targetOpacity = 255;
			}
			blockState.t = 0.0f;
		}
	}
} // namespace System