#include "attributes.hpp"


uintptr_t Classes::getListEntry(int id) {
	listEntry = MemMan.ReadMem<uintptr_t>(entity_list + (8 * (id & 0x7FFF) >> 9) + 16);
	return listEntry;
}

uintptr_t Classes::getCCSPlayerControllerBase(int id) {
	CCSPlayerController_ = MemMan.ReadMem<uintptr_t>(listEntry + 120 * (id & 0x1FF));
	return CCSPlayerController_;
}




int CCSPlayerController::getPawnHealth() {
	pawnHealth = MemMan.ReadMem<int>(value + m_iPawnHealth);
	return pawnHealth;
}

std::uint32_t CCSPlayerController::getC_CSPlayerPawn() {
	C_CSPlayerPawn_ = MemMan.ReadMem<std::uint32_t>(value + m_hPlayerPawn);
	return C_CSPlayerPawn_;
}

uintptr_t CCSPlayerController::getPawnTeam() {
	pawnTeam = MemMan.ReadMem<uintptr_t>(value + m_iTeamNum);
	return pawnTeam;
}

std::string CCSPlayerController::getPawnName() {
	pawnNameAddress = MemMan.ReadMem<uintptr_t>(value + m_sSanitizedPlayerName);
	if (pawnNameAddress) {
		char buf[256] = {};
		MemMan.ReadRawMem(pawnNameAddress, buf, sizeof(buf));
		pawnName = std::string(buf);
	}
	else {
		pawnName = "Unknown";
	}
	return pawnName;
}




uintptr_t C_CSPlayerPawn::getPlayerPawn() {
	playerPawn = MemMan.ReadMem<uintptr_t>(listEntry + 120 * (value & 0x1FF));
	return playerPawn;
}

Vector3 C_CSPlayerPawn::getOrigin() {
	origin = MemMan.ReadMem<Vector3>(playerPawn + m_vOldOrigin);
	return origin;
}

Vector3 C_CSPlayerPawn::getCameraPos() {
	cameraPos = MemMan.ReadMem<Vector3>(playerPawn + m_vecLastClipCameraPos);
	return cameraPos;
}

uintptr_t C_CSPlayerPawn::getCGameSceneNode() {
	CGameSceneNode = MemMan.ReadMem<uintptr_t>(playerPawn + m_pGameSceneNode);
	return CGameSceneNode;
}

Vector3 C_CSPlayerPawn::getViewAngles() {
	viewAngles = MemMan.ReadMem<Vector3>(playerPawn + m_angEyeAngles);
	return viewAngles;
}

Vector3 C_CSPlayerPawn::getPosition() {
	position = MemMan.ReadMem<Vector3>(playerPawn + m_vLastSlopeCheckPos);
	return position;
}

uint16_t C_CSPlayerPawn::getWeaponID() {
	C_CSWeaponBase = MemMan.ReadMem<uint64_t>(playerPawn + m_pClippingWeapon);
	weaponID = MemMan.ReadMem<uint16_t>(C_CSWeaponBase + m_iItemDefinitionIndex + m_Item + m_AttributeManager);
	return weaponID;
}

int C_CSPlayerPawn::getPawnHealth() {
	pawnHealth = MemMan.ReadMem<int>(playerPawn + m_iHealth);
	return pawnHealth;
}

uintptr_t C_CSPlayerPawn::getPawnTeam() {
	pawnTeam = MemMan.ReadMem<uintptr_t>(value + m_iTeamNum);
	return pawnTeam;
}

DWORD_PTR C_CSPlayerPawn::getEntitySpotted() {
	spotted = MemMan.ReadMem<DWORD_PTR>(value + m_bSpottedByMask);
	return spotted;
}



uintptr_t LocalPlayer::getPlayerPawn() {
	playerPawn = MemMan.ReadMem<uintptr_t>(moduleData.base + dwLocalPlayerPawn);
	return playerPawn;
}

uintptr_t LocalPlayer::getTeam() {
	team = MemMan.ReadMem<uintptr_t>(localPlayer + m_iTeamNum);
	return team;
}

Vector3 LocalPlayer::getCameraPos() {
	cameraPos = MemMan.ReadMem<Vector3>(playerPawn + m_vecLastClipCameraPos);
	return cameraPos;
}

Vector3 LocalPlayer::getViewAngles() {
	viewAngles = MemMan.ReadMem<Vector3>(playerPawn + v_angle);
	return viewAngles;
}

Vector3 LocalPlayer::getPosition() {
	position = MemMan.ReadMem<Vector3>(playerPawn + m_vLastSlopeCheckPos);
	return position;
}

Vector3 LocalPlayer::getOrigin() {
	origin = MemMan.ReadMem<Vector3>(playerPawn + m_vOldOrigin);
	return origin;
}

int LocalPlayer::getFlags() {
	flags = MemMan.ReadMem<int>(playerPawn + m_fFlags);
	return flags;
}

C_UTL_VECTOR LocalPlayer::getAimPunchCache() {
	aimPunchCache = MemMan.ReadMem<C_UTL_VECTOR>(playerPawn + m_aimPunchCache);
	return aimPunchCache;
}

Vector2 LocalPlayer::getAimPunchAngle() {
	aimPunchAngle = MemMan.ReadMem<Vector2>(playerPawn + m_aimPunchAngle);
	return aimPunchAngle;
}

int LocalPlayer::getShotsFired() {
	shotsFired = MemMan.ReadMem<int>(playerPawn + m_iShotsFired);
	return shotsFired;
}

void LocalPlayer::noFlash() {
	MemMan.WriteMem<float>(playerPawn + m_flFlashDuration, 0.f);
}




uintptr_t CGameSceneNode::getBoneArray() {
	boneArray = MemMan.ReadMem<uintptr_t>(value + m_modelState + m_vecOrigin);
	return boneArray;
}