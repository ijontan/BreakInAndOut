#pragma once
#include "Entity.hpp"
#include "Component/Position.hpp"
#include "Component/Velocity.hpp"
#include "Component/Shapes.hpp"
#include "Component/CollisionBox.hpp"
#include "Component/BlockState.hpp"
#include "Component/PaddleState.hpp"
#include "Component/Displacement.hpp"
#include "Component/ui/MouseHitBox.hpp"
#include "Component/ui/Text.hpp"
#include "Component/ui/Container.hpp"
#include "utils/masking.hpp"
#include "utils/math.hpp"
#include "utils/Sounds.hpp"
#include <functional>



namespace Entity {
	struct Entity;

	Entity createBall(Scene* scene, Vector2 position, Vector2 velocity, float radius);

	struct BlockConfig
	{
		Vector2 position = { 0.0f, 0.0f };
		Vector2 size = { 0.0f, 0.0f };
		Color color = WHITE;
		Component::BlockType type = Component::BlockType::NORMAL;
		Component::GhostLayer layer = Component::GhostLayer::REAL;
		Utils::Notes hitSound = Utils::Notes::C3;
		int health = 1;
		BlockConfig() = default;
		BlockConfig(Vector2 position, Vector2 size, Color color, Component::BlockType type, Component::GhostLayer layer, Utils::Notes hitSound)
			: position(position), size(size), color(color), type(type), layer(layer), hitSound(hitSound), health(1) {}
	};

	class BlockConfigFactory
	{
	private:

		Vector2 defaultSize = { 100.0f, 50.0f };
		Vector2 position = { 0.0f, 0.0f };
		Component::GhostLayer layer = Component::GhostLayer::REAL;
		Component::BlockType type = Component::BlockType::WALL;
		Utils::Notes hitSound = Utils::Notes::C3;
		Color color = LIGHTGRAY;
	public:
		BlockConfig	createConfig(){
			return BlockConfig(position, defaultSize, color, type, layer, hitSound);
		}
		void setPosition(Vector2 pos) { position = pos; }
		void setType(Component::BlockType type) { 
			this->type = type;
			switch (type)
			{
			case Component::BlockType::NORMAL:
				color = BLUE;
				break;
			case Component::BlockType::WALL:
				color = LIGHTGRAY;
				break;
			case Component::BlockType::BALLOON:
				color = GREEN;
				break;
			case Component::BlockType::SPIKES:
				color = RED;
				break;
			}
		}
		void setLayer(Component::GhostLayer layer) { this->layer = layer; }
		void setSound(Utils::Notes hitSound) { this->hitSound = hitSound; }
		Utils::Notes& getSound() { return hitSound; }
		Component::BlockType& getType() { return type; }
		void randomPosition(float minX, float maxX, float minY, float maxY)
		{
			position.x = Utils::random(minX, maxX);
			position.y = Utils::random(minY, maxY);
		}
	};

	Entity createBlock(Scene* scene, const BlockConfig& config);
	Entity createPaddle(Scene* scene, Vector2 position, Vector2 size, Color color = WHITE);

	// ui
	Entity createButton(Scene* scene, Vector2 position, Vector2 size, const std::string& text, Color textColor, int fontSize, Vector2 padding, Color boxColor, std::function<void()> onClick);
	Entity createPanel(Scene* scene, Vector2 position, Vector2 size, Color color);
	Entity createText(Scene* scene, Vector2 position, const std::string& text, Color color, int fontSize);
	Entity createTextButton(Scene* scene, Vector2 position, Vector2 size, std::string text, Color textColor, std::function<void()> onClick);
};
