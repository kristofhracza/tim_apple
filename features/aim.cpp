#include "aim.hpp"

#include "random"
#include "windows.h"
#include <iostream>

#include "../util/config.hpp"

#include <iostream>

using namespace std;

void aim::aimBot(LocalPlayer localPlayer, Vector3 baseViewAngles, uintptr_t enemyPlayer, uintptr_t boneArray, MemoryManagement::moduleData client) {
	Vector3 aimPos;
	Vector3 newAngle;
	Vector3 angle;

	if (lockedPlayer != 0 && lockedPlayer != enemyPlayer) return;
	if (enemyPlayer == localPlayer.getPlayerPawn()) {
		lockedPlayer = 0;
		return;
	}

	aimPos = MemMan.ReadMem<Vector3>(boneArray + aimConf.boneMap[aimConf.bones[aimConf.boneSelect]] * 32);
	angle = CalculateAngle(localPlayer.eyepos, aimPos, localPlayer.viewAngles);
	newAngle = calculateBestAngle(angle, aimConf.fov);

	newAngle.x = (newAngle.x / (0.022f * aimConf.sens)) / aimConf.smoothing;
	newAngle.y = (newAngle.y / (0.022f * aimConf.sens)) / aimConf.smoothing;

	if (newAngle.IsZero()) {
		lockedPlayer = 0;
		return;
	}
	
	if (aimConf.isHotAim) {
		if (GetAsyncKeyState(aimConf.hotKeyMap[aimConf.hotKey[aimConf.hotSelectAim]])) {
			aim::moveMouseToLocation(newAngle);
		}
	}
	else {
		aim::moveMouseToLocation(newAngle);
	}

	lockedPlayer = enemyPlayer;
}

void aim::moveMouseToLocation(Vector3 pos) {
	if (pos.x == 0.f && pos.y == 0.f && pos.z == 0.f) return;

	auto new_x = -pos.y;
	auto new_y = pos.x;

	mouse_event(MOUSEEVENTF_MOVE, new_x, new_y, 0, 0);
}

void aim::recoilControl(LocalPlayer localPlayer, DWORD_PTR baseViewAnglesAddy) {
	localPlayer.getAimPunchCache();
	localPlayer.getViewAngles();

	static Vector3 oldAngles = { 0, 0, 0 };
	Vector3 newAngles = { 0, 0, 0 };

	if (localPlayer.getShotsFired() == 54587654) return; // Spectator check

	if (localPlayer.getShotsFired() > 1) {
		Vector3 aimPunch = MemMan.ReadMem<Vector3>(localPlayer.getPlayerPawn() + clientDLL::C_CSPlayerPawn_["m_aimPunchAngle"]);
		newAngles.x = (aimPunch.x - oldAngles.x) * 2.f / (0.022f * aimConf.sens);
		newAngles.y = (aimPunch.y - oldAngles.y) * 2.f / (0.022f * aimConf.sens);

		aim::moveMouseToLocation(newAngles * -1);

		oldAngles = aimPunch;
	}
	else {
		oldAngles = { 0, 0, 0 };
	}
}

bool clicked = false;

const int trigger_cooldown()
{
	return (int) (((rand() % 50)/100) + 0.15F);
}

void aim::triggerBot(LocalPlayer localPlayer, DWORD_PTR base) {
	int crossHairEntity = MemMan.ReadMem<int>(localPlayer.getPlayerPawn() + clientDLL::C_CSPlayerPawnBase_["m_iIDEntIndex"]);
	int localPlayerHealth = MemMan.ReadMem<int>(localPlayer.getPlayerPawn() + clientDLL::C_BaseEntity_["m_iHealth"]);
	if (!crossHairEntity) return;

	C_CSPlayerPawn crossHairPawn(base);
	CCSPlayerController crossHairEntityController(base);

	crossHairPawn.getPlayerPawnByCrossHairID(crossHairEntity);
	crossHairEntityController.value = crossHairPawn.playerPawn;

	bool isValidEntity = (crossHairEntity != -1 && crossHairPawn.getPawnHealth() > 0 && crossHairPawn.getPawnHealth() <= 100 && crossHairEntityController.getPawnTeam() != localPlayer.getTeam());
	bool isDeathMatchEntity = (crossHairEntity != -1 && crossHairPawn.getPawnHealth() > 0 && crossHairPawn.getPawnHealth() <= 100 && miscConf.deathmatchMode);

	if (localPlayerHealth > 100 || localPlayerHealth <= 0) return;

	if (aimConf.isHotTrigger) {
		if (GetAsyncKeyState(aimConf.hotKeyMap[aimConf.hotKey[aimConf.hotSelectTrigger]])) {
			if (isValidEntity || isDeathMatchEntity) {
				if (!clicked)
				{
					clicked = true;
					const int t = trigger_cooldown();
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(t/2);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					Sleep(t/2);
					clicked = false;
				}
			};
		}
	}
	else {
		if (isValidEntity || isDeathMatchEntity)
		{
			if (!clicked)
			{
				clicked = true;
				const int t = trigger_cooldown();
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				Sleep(t / 2);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				Sleep(t / 2);
				clicked = false;
			}
		};
	}
}