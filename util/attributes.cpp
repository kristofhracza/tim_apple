#include "attributes.hpp"



uintptr_t CCSPlayerController::getListEntry() {
	listEntry = MemMan.ReadMem<uintptr_t>(entityList + (0x8 * (id & 0x7FFF) >> 9) + 0x10);
	return listEntry;
}

uintptr_t CCSPlayerController::getController() {
	value = MemMan.ReadMem<uintptr_t>(listEntry + 0x78 * (id & 0x1FF));
	return value;
}

int CCSPlayerController::getPawnHealth() {
	pawnHealth = MemMan.ReadMem<int>(value + clientDLL::CCSPlayerController_["m_iPawnHealth"]);
	return pawnHealth;
}

std::uint32_t CCSPlayerController::getC_CSPlayerPawn() {
	C_CSPlayerPawn_ = MemMan.ReadMem<std::uint32_t>(value + clientDLL::CCSPlayerController_["m_hPlayerPawn"]);
	return C_CSPlayerPawn_;
}

uintptr_t CCSPlayerController::getPawnTeam() {
	pawnTeam = MemMan.ReadMem<uintptr_t>(value + clientDLL::C_BaseEntity_["m_iTeamNum"]);
	return pawnTeam;
}

std::string CCSPlayerController::getPawnName() {
	pawnNameAddress = MemMan.ReadMem<uintptr_t>(value + clientDLL::CCSPlayerController_["m_sSanitizedPlayerName"]);
	if (pawnNameAddress) {
		char buf[MAX_PATH] = {};
		MemMan.ReadRawMem(pawnNameAddress, buf, MAX_PATH);
		pawnName = std::string(buf);
	}
	else {
		pawnName = "Unknown";
	}
	return pawnName;
}



uintptr_t C_CSPlayerPawn::getListEntry() {
	listEntry = MemMan.ReadMem<uintptr_t>(entityList + 0x8 * ((value & 0x7FFF) >> 9) + 0x10);
	return listEntry;
}

uintptr_t C_CSPlayerPawn::getPlayerPawn() {
	playerPawn = MemMan.ReadMem<uintptr_t>(listEntry + 0x78 * (value & 0x1FF));
	return playerPawn;
}

uintptr_t C_CSPlayerPawn::getPlayerPawnByCrossHairID(int crossHairEntity) {
	uintptr_t crosshairEntityEntry = MemMan.ReadMem<uintptr_t>(entityList + 0x8 * (crossHairEntity >> 9) + 0x10);
	playerPawn = MemMan.ReadMem<uintptr_t>(crosshairEntityEntry + 0x78 * (crossHairEntity & 0x1FF));
	return playerPawn;
}

Vector3 C_CSPlayerPawn::getOrigin() {
	origin = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BasePlayerPawn_["m_vOldOrigin"]);
	return origin;
}

Vector3 C_CSPlayerPawn::getCameraPos() {
	cameraPos = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_vecLastClipCameraPos"]);
	return cameraPos;
}

uintptr_t C_CSPlayerPawn::getCGameSceneNode() {
	CGameSceneNode = MemMan.ReadMem<uintptr_t>(playerPawn + clientDLL::C_BaseEntity_["m_pGameSceneNode"]);
	return CGameSceneNode;
}

Vector3 C_CSPlayerPawn::getViewAngles() {
	viewAngles = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_angEyeAngles"]);
	return viewAngles;
}

Vector3 C_CSPlayerPawn::getPosition() {
	position = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::CBaseAnimGraph_["m_vLastSlopeCheckPos"]);
	return position;
}

uint16_t C_CSPlayerPawn::getWeaponID() {
	C_CSWeaponBase = MemMan.ReadMem<uint64_t>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_pClippingWeapon"]);
	weaponID = MemMan.ReadMem<uint16_t>(C_CSWeaponBase + clientDLL::C_EconItemView_["m_iItemDefinitionIndex"] + clientDLL::C_AttributeContainer_["m_Item"] + clientDLL::C_EconEntity_["m_AttributeManager"]);
	return weaponID;
}

std::string C_CSPlayerPawn::getWeaponName() {
	C_CSWeaponBase = MemMan.ReadMem<uint64_t>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_pClippingWeapon"]);
	uint64_t weaponData = MemMan.ReadMem<uint64_t>(C_CSWeaponBase + clientDLL::C_BaseEntity_["m_nSubclassID"] + 0x8);
	uint64_t weaponNameAddress = MemMan.ReadMem<uint64_t>(weaponData + clientDLL::CCSWeaponBaseVData_["m_szName"]);

	if (!weaponNameAddress) {
		weaponName = "NULL";
	}
	else {
		char buf[MAX_PATH] = {};
		MemMan.ReadRawMem(weaponNameAddress, buf, MAX_PATH);
		weaponName = std::string(buf);
		if (weaponName.compare(0, 7, "weapon_") == 0) {
			weaponName = weaponName.substr(7, weaponName.length());
		}
	}
	return weaponName;
}

int C_CSPlayerPawn::getPawnHealth() {
	pawnHealth = MemMan.ReadMem<int>(playerPawn + clientDLL::C_BaseEntity_["m_iHealth"]);
	return pawnHealth;
}

uintptr_t C_CSPlayerPawn::getPawnTeam() {
	pawnTeam = MemMan.ReadMem<uintptr_t>(value + clientDLL::C_BaseEntity_["m_iTeamNum"]);
	return pawnTeam;
}

int C_CSPlayerPawn::getEntitySpotted() {
	spotted = MemMan.ReadMem<DWORD_PTR>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_entitySpottedState"] + clientDLL::EntitySpottedState_t_["m_bSpottedByMask"]);
	return spotted;
}

int C_CSPlayerPawn::getOwner() {
	owner = MemMan.ReadMem<DWORD_PTR>(playerPawn + clientDLL::C_BaseEntity_["m_hOwnerEntity"]);
	return owner;
}




uintptr_t LocalPlayer::getPlayerPawn() {
	playerPawn = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwLocalPlayerPawn"]);
	return playerPawn;
}

uintptr_t LocalPlayer::getTeam() {
	team = MemMan.ReadMem<uintptr_t>(localPlayer + clientDLL::C_BaseEntity_["m_iTeamNum"]);
	return team;
}

Vector3 LocalPlayer::getCameraPos() {
	cameraPos = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_vecLastClipCameraPos"]);
	return cameraPos;
}

Vector3 LocalPlayer::getViewAngles() {
	viewAngles = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BasePlayerPawn_["v_angle"]);
	return viewAngles;
}

Vector3 LocalPlayer::getPosition() {
	position = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::CBaseAnimGraph_["m_vLastSlopeCheckPos"]);
	return position;
}

Vector3 LocalPlayer::getOrigin() {
	origin = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BasePlayerPawn_["m_vOldOrigin"]);
	return origin;
}

int LocalPlayer::getFlags() {
	flags = MemMan.ReadMem<int>(playerPawn + clientDLL::C_BaseEntity_["m_fFlags"]);
	return flags;
}

C_UTL_VECTOR LocalPlayer::getAimPunchCache() {
	aimPunchCache = MemMan.ReadMem<C_UTL_VECTOR>(playerPawn + clientDLL::C_CSPlayerPawn_["m_aimPunchCache"]);
	return aimPunchCache;
}

Vector2 LocalPlayer::getAimPunchAngle() {
	aimPunchAngle = MemMan.ReadMem<Vector2>(playerPawn + clientDLL::C_CSPlayerPawn_["m_aimPunchAngle"]);
	return aimPunchAngle;
}

int LocalPlayer::getShotsFired() {
	shotsFired = MemMan.ReadMem<int>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_iShotsFired"]);
	return shotsFired;
}

void LocalPlayer::noFlash() {
	MemMan.WriteMem<float>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_flFlashDuration"], 0.f);
}

int LocalPlayer::getEntitySpotted() {
	spotted = MemMan.ReadMem<DWORD_PTR>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_entitySpottedState"] + clientDLL::EntitySpottedState_t_["m_bSpottedByMask"]);
	return spotted;
}

bool LocalPlayer::getIsScoped() {
	isScoped = MemMan.ReadMem<DWORD_PTR>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_bIsScoped"]);
	return isScoped;
}



uintptr_t CGameSceneNode::getBoneArray() {
	boneArray = MemMan.ReadMem<uintptr_t>(value + clientDLL::CSkeletonInstance_["m_modelState"] + clientDLL::CGameSceneNode_["m_vecOrigin"]);
	return boneArray;
}

Vector3 CGameSceneNode::getOrigin() {
	origin = MemMan.ReadMem<Vector3>(value + clientDLL::CGameSceneNode_["m_vecAbsOrigin"]);
	return origin;
}



bool SharedFunctions::spottedCheck(C_CSPlayerPawn C_CSPlayerPawn, LocalPlayer localPlayer) {
	if (C_CSPlayerPawn.getEntitySpotted() & (1 << (localPlayer.playerPawn)) || localPlayer.getEntitySpotted() & (1 << (C_CSPlayerPawn.playerPawn))) return 1;
	return 0;
}

bool SharedFunctions::inGame(DWORD_PTR base) {
	uintptr_t gameRules = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwGameRules"]);

	bool warmup = MemMan.ReadMem<bool>(gameRules + clientDLL::C_CSGameRules_["m_bWarmupPeriod"]);
	bool match = MemMan.ReadMem<bool>(gameRules + clientDLL::C_CSGameRules_["m_bHasMatchStarted"]);
	bool freeze = MemMan.ReadMem<bool>(gameRules + clientDLL::C_CSGameRules_["m_bFreezePeriod"]);

	return match;
}