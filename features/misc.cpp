#include "misc.hpp"


void misc::bunnyHop(DWORD_PTR base, int flags) {
	if (GetAsyncKeyState(VK_SPACE) && flags & bhopInAir) {
		MemMan.WriteMem<int>(base + offsets::clientDLL["dwForceJump"]["value"], 65537);
	}
	else {
		MemMan.WriteMem<int>(base + offsets::clientDLL["dwForceJump"]["value"], 256);
	}
}


void misc::triggerBot(LocalPlayer localPlayer,DWORD_PTR base) {
	int crossHairEntity = MemMan.ReadMem<int>(localPlayer.getPlayerPawn() + clientDLL::C_CSPlayerPawnBase_["m_iIDEntIndex"]["value"]);
	if (!crossHairEntity) return;
	
	C_CSPlayerPawn crossHairPawn(base);
	crossHairPawn.getPlayerPawnByCrossHairID(crossHairEntity);

	bool isValidEntity = (crossHairEntity != -1 && crossHairPawn.getPawnHealth() > 0 && crossHairPawn.getPawnHealth() <= 100);

	if (miscConf.isHot) {
		if (GetAsyncKeyState(miscConf.hotKeyMap[miscConf.hotKey[miscConf.hotSelect]])) {
			if (isValidEntity) {
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			};
		}
	}
	else {
		if (isValidEntity) {
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		};
	}
}