#pragma once
#include <functional>

namespace Component {
	struct Watcher {
		std::function<void()> action;
	};
}
