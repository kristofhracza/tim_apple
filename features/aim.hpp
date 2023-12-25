#pragma once

#include "include.hpp"

#include "../util/config.hpp"
#include "../gui/overlay.hpp"


namespace aim {
	void aimBot(LocalPlayer localPlayer, Vector3 baseViewAngles,DWORD_PTR baseViewAnglesAddy,uintptr_t boneArray);
	void recoilControl(LocalPlayer localPlayer, DWORD_PTR baseViewAnglesAddy);
	void triggerBot(LocalPlayer localPlayer, DWORD_PTR base);

	inline uintptr_t lockedPlayer = 0;
}
