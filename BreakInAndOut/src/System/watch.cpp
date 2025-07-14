#include "../../include/Systems.hpp"

void System::watch(Scene* scene)
{
	const auto view = scene->registry.view<Component::Watcher>();
	for (const auto& entity : view)
	{
		const auto& watcher = view.get<Component::Watcher>(entity);
		if (watcher.action)
			watcher.action();
	}
}