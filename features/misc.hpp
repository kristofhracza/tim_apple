#pragma once

#include "include.hpp"

#include "../util/config.hpp"

namespace misc {

	inline namespace sharedData {
		inline int bhopInAir = (1 << 0);
	};

	void bunnyHop(DWORD_PTR base, int flags);
}