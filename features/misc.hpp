#pragma once

#include "include.hpp"

namespace misc {

	inline namespace sharedData {
		inline int bhopInAir = (1 << 0);
	};

	void bunnyHop(DWORD_PTR base, int flags);
	void triggerBot(LocalPlayer localPlayer, DWORD_PTR base);
}