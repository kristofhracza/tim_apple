#pragma once

#include "include.hpp"

#include "../util/config.hpp"
#include "../gui/overlay.hpp"


namespace aim {
	Vector3 recoilControl(LocalPlayer localPlayer, bool move);
	void aimBot(LocalPlayer localPlayer, Vector3 baseViewAngles, uintptr_t enemyPlayer, uintptr_t boneArray, MemoryManagement::moduleData client);
	void moveMouseToLocation(Vector3 pos);
	void triggerBot(LocalPlayer localPlayer, DWORD_PTR base);

	uintptr_t lockedPlayer = 0;
}
