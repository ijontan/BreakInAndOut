#pragma once
#include "Scene.hpp"
#include <utility>

namespace Entity {
	struct Entity
	{
		Entity() = default;
		Entity(entt::entity handle, Scene* scene) : entityHandle(handle), scene(scene)
		{
		}

		template <typename T, typename... Arg>
		T& addComponent(Arg &&...args) const
		{
			return scene->registry.emplace<T>(entityHandle, std::forward<Arg>(args)...);
		}

		template <typename T>
		T& getComponent() const 
		{
			return scene->registry.get<T>(entityHandle);
		}

		template <typename T>
		void removeComponent() const 
		{
			return scene->registry.remove<T>(entityHandle);
		}

		operator entt::entity()
		{
			return entityHandle;
		}

		operator entt::entity() const
		{
			return entityHandle;
		}

	private:
		entt::entity entityHandle{ 0 };
		Scene* scene = nullptr;
	};
};
