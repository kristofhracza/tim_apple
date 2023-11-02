#include "aim.hpp"

void aim::aimBot(LocalPlayer localPlayer, Vector3 baseViewAngles, DWORD_PTR baseViewAnglesAddy, uintptr_t boneArray) {
	Vector3 aimPos;
	Vector3 newAngle;

	aimPos = MemMan.ReadMem<Vector3>(boneArray + aimConf.boneMap[aimConf.bones[aimConf.boneSelect]] * 32);
	Vector3 angle = CalculateAngle(localPlayer.cameraPos, aimPos, localPlayer.viewAngles);
	newAngle = calculateBestAngle(angle, aimConf.fov);
	newAngle = clampAngles(newAngle);

	newAngle.x = newAngle.x / aimConf.smoothing;
	newAngle.y = newAngle.y / aimConf.smoothing;

	if (newAngle.IsZero()) {
		return;
	}

	if (aimConf.isHot) {
		if (GetAsyncKeyState(aimConf.hotKeyMap[aimConf.hotKey[aimConf.hotSelect]])) {
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