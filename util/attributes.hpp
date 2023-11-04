#pragma once
#pragma warning (disable: 26495)

#include <cstdint>
#include <string>

#include "Vectors.h"
#include "MemMan.hpp"

#include "../json/jsonOps.hpp"

struct C_UTL_VECTOR
{
	DWORD_PTR count = 0;
	DWORD_PTR data = 0;
};


inline MemoryManagement MemMan;

namespace clientDLL {
	inline nlohmann::json clientDLLOffsets = json::readFromJsonFile(json::clientDLLFile);

	inline nlohmann::json C_BaseEntity_ = clientDLLOffsets["C_BaseEntity"]["data"];
	inline nlohmann::json CCSPlayerController_ = clientDLLOffsets["CCSPlayerController"]["data"];
	inline nlohmann::json C_BasePlayerPawn_ = clientDLLOffsets["C_BasePlayerPawn"]["data"];
	inline nlohmann::json C_CSPlayerPawn_ = clientDLLOffsets["C_CSPlayerPawn"]["data"];
	inline nlohmann::json C_CSPlayerPawnBase_ = clientDLLOffsets["C_CSPlayerPawnBase"]["data"];
	inline nlohmann::json CBaseAnimGraph_ = clientDLLOffsets["CBaseAnimGraph"]["data"];
	inline nlohmann::json C_EconItemView_ = clientDLLOffsets["C_EconItemView"]["data"];
	inline nlohmann::json C_AttributeContainer_ = clientDLLOffsets["C_AttributeContainer"]["data"];
	inline nlohmann::json C_EconEntity_ = clientDLLOffsets["C_EconEntity"]["data"];
	inline nlohmann::json CSkeletonInstance_ = clientDLLOffsets["CSkeletonInstance"]["data"];
	inline nlohmann::json CGameSceneNode_ = clientDLLOffsets["CGameSceneNode"]["data"];
};


namespace offsets {
	inline nlohmann::json clientDLL = json::readFromJsonFile(json::offsetFile)["client_dll"]["data"];
};


class Classes {
public:
	MemoryManagement::moduleData moduleData;
	uintptr_t entity_list;

	Classes(MemoryManagement::moduleData module) {
		moduleData = module;
		entity_list = MemMan.ReadMem<uintptr_t>(moduleData.base + offsets::clientDLL["dwEntityList"]["value"]);
	}

	uintptr_t listEntry;
	uintptr_t getListEntry(int id);
	
	// CCSPlayerController
	uintptr_t CCSPlayerController_;
	uintptr_t getCCSPlayerControllerBase(int id);
};


class CCSPlayerController{
public:
	uintptr_t value;

	CCSPlayerController(uintptr_t playerController) {
		value = playerController;
	}

	int pawnHealth;
	int getPawnHealth();

	uintptr_t pawnTeam;
	uintptr_t getPawnTeam();

	uintptr_t pawnNameAddress;
	std::string pawnName;
	std::string getPawnName();

	// C_CSPlayerPawn
	std::uint32_t C_CSPlayerPawn_;
	std::uint32_t getC_CSPlayerPawn();
};


class C_CSPlayerPawn {
public:
	std::uint32_t value;

	uintptr_t entity_list;
	uintptr_t listEntry;
	uintptr_t moduleBase;
	
	C_CSPlayerPawn(uintptr_t base) {
		moduleBase = base;
		entity_list = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwEntityList"]["value"]);
		listEntry = MemMan.ReadMem<uintptr_t>(entity_list + static_cast<uintptr_t>(0x8) * ((value & 0x7FFF) >> 9) + 16);
	}

	uintptr_t playerPawn;
	uintptr_t getPlayerPawn();
	uintptr_t getPlayerPawnByCrossHairID(int crossHairEntity);

	Vector3 origin;
	Vector3 getOrigin();

	Vector3 cameraPos;
	Vector3 getCameraPos();

	Vector3 viewAngles;
	Vector3 getViewAngles();

	Vector3 position;
	Vector3 getPosition();

	int pawnHealth;
	int getPawnHealth();

	uintptr_t pawnTeam;
	uintptr_t getPawnTeam();


	/*
	TODO: Define classes to properly get weapon data
		C_CSWeaponBase (look at offsets for inheritance)
		uint16_t getC_CSWeaponBase();
		uint16_t C_CSWeaponBase;
	*/
	uint64_t C_CSWeaponBase;
	uint16_t weaponID;
	uint16_t getWeaponID();

	DWORD_PTR spotted;
	DWORD_PTR getEntitySpotted();

	// CGameSceneNode
	uintptr_t CGameSceneNode;
	uintptr_t getCGameSceneNode();

};

class CGameSceneNode {
public:
	uintptr_t value;

	uintptr_t boneArray;
	uintptr_t getBoneArray();
};


class LocalPlayer {
public:
	MemoryManagement::moduleData moduleData;
	uintptr_t localPlayer;

	LocalPlayer(MemoryManagement::moduleData module) {
		moduleData = module;
		localPlayer = MemMan.ReadMem<uintptr_t>(moduleData.base + offsets::clientDLL["dwLocalPlayerController"]["value"]);
	}

	uintptr_t playerPawn;
	uintptr_t getPlayerPawn();

	uintptr_t team;
	uintptr_t getTeam();

	Vector3 cameraPos;
	Vector3 getCameraPos();

	Vector3 origin;
	Vector3 getOrigin();

	Vector3 viewAngles;
	Vector3 getViewAngles();

	Vector3 position;
	Vector3 getPosition();

	int flags;
	int getFlags();

	C_UTL_VECTOR aimPunchCache;
	C_UTL_VECTOR getAimPunchCache();

	Vector2 aimPunchAngle;
	Vector2 getAimPunchAngle();

	int shotsFired;
	int getShotsFired();

	void noFlash();
};