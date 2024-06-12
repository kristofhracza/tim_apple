#include "aim.hpp"

void aim::aimBot(LocalPlayer localPlayer, Vector3 baseViewAngles, DWORD_PTR baseViewAnglesAddy, uintptr_t boneArray) {
	Vector3 aimPos;
	Vector3 newAngle;
	Vector3 angle;

	aimPos = MemMan.ReadMem<Vector3>(boneArray + aimConf.boneMap[aimConf.bones[aimConf.boneSelect]] * 32);
	angle = CalculateAngle(localPlayer.cameraPos, aimPos, localPlayer.viewAngles);
	newAngle = calculateBestAngle(angle, aimConf.fov);
	newAngle = clampAngles(newAngle);

	newAngle.x = newAngle.x / aimConf.smoothing;
	newAngle.y = newAngle.y / aimConf.smoothing;

	if (newAngle.IsZero()) {
		lockedPlayer = 0;
		return;
	}
	
	if (aimConf.isHotAim) {
		if (GetAsyncKeyState(aimConf.hotKeyMap[aimConf.hotKey[aimConf.hotSelectAim]])) {
			MemMan.WriteMem<Vector3>(baseViewAnglesAddy, baseViewAngles + newAngle);
		}
	}
	else {
		MemMan.WriteMem<Vector3>(baseViewAnglesAddy, baseViewAngles + newAngle);
	}
}

void aim::recoilControl(LocalPlayer localPlayer, DWORD_PTR baseViewAnglesAddy) {
	localPlayer.getAimPunchCache();
	localPlayer.getViewAngles();

	static Vector3 oldPunch;
	Vector3 aimPunchAngle = MemMan.ReadMem<Vector3>(localPlayer.aimPunchCache.data + (localPlayer.aimPunchCache.count - 1) * sizeof(Vector3));

	if (localPlayer.getShotsFired() > 1) {

		Vector3 recoilVector = {
			localPlayer.viewAngles.x + oldPunch.x - aimPunchAngle.x * 2.f,
			localPlayer.viewAngles.y + oldPunch.y - aimPunchAngle.y * 2.f
		};
		recoilVector = clampAngles(recoilVector);

		MemMan.WriteMem<Vector3>(baseViewAnglesAddy, recoilVector);
	}
	oldPunch.x = aimPunchAngle.x * 2.f;
	oldPunch.y = aimPunchAngle.y * 2.f;
}


void aim::triggerBot(LocalPlayer localPlayer, DWORD_PTR base) {
	int crossHairEntity = MemMan.ReadMem<int>(localPlayer.getPlayerPawn() + clientDLL::C_CSPlayerPawnBase_["m_iIDEntIndex"]);
	if (!crossHairEntity) return;

	C_CSPlayerPawn crossHairPawn(base);
	CCSPlayerController crossHairEntityController(base);

	crossHairPawn.getPlayerPawnByCrossHairID(crossHairEntity);
	crossHairEntityController.value = crossHairPawn.playerPawn;

	bool isValidEntity = (crossHairEntity != -1 && crossHairPawn.getPawnHealth() > 0 && crossHairPawn.getPawnHealth() <= 100 && crossHairEntityController.getPawnTeam() != localPlayer.getTeam());

	if (aimConf.isHotTrigger) {
		if (GetAsyncKeyState(aimConf.hotKeyMap[aimConf.hotKey[aimConf.hotSelectTrigger]])) {
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