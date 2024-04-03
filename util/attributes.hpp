#pragma once
#pragma warning (disable: 26495)

#include <cstdint>
#include <string>

#include "Vectors.h"
#include "MemMan.hpp"

#include "../json/jsonOps.hpp"

#include "weaponInfo.hpp"

struct C_UTL_VECTOR
{
	DWORD_PTR count = 0;
	DWORD_PTR data = 0;
};


inline MemoryManagement MemMan;

namespace clientDLL {
	inline nlohmann::json clientDLLOffsets = json::readFromJsonFile(json::clientDLLFile);

	inline nlohmann::json C_BaseEntity_ = clientDLLOffsets["C_BaseEntity"]["classes"]["fields"];
	inline nlohmann::json CCSPlayerController_ = clientDLLOffsets["CCSPlayerController"]["classes"]["fields"];
	inline nlohmann::json C_BasePlayerPawn_ = clientDLLOffsets["C_BasePlayerPawn"]["classes"]["fields"];
	inline nlohmann::json C_CSPlayerPawn_ = clientDLLOffsets["C_CSPlayerPawn"]["classes"]["fields"];
	inline nlohmann::json C_CSPlayerPawnBase_ = clientDLLOffsets["C_CSPlayerPawnBase"]["classes"]["fields"];
	inline nlohmann::json CBaseAnimGraph_ = clientDLLOffsets["CBaseAnimGraph"]["classes"]["fields"];
	inline nlohmann::json C_EconItemView_ = clientDLLOffsets["C_EconItemView"]["classes"]["fields"];
	inline nlohmann::json C_AttributeContainer_ = clientDLLOffsets["C_AttributeContainer"]["classes"]["fields"];
	inline nlohmann::json C_EconEntity_ = clientDLLOffsets["C_EconEntity"]["classes"]["fields"];
	inline nlohmann::json CSkeletonInstance_ = clientDLLOffsets["CSkeletonInstance"]["classes"]["fields"];
	inline nlohmann::json CGameSceneNode_ = clientDLLOffsets["CGameSceneNode"]["classes"]["fields"];
	inline nlohmann::json EntitySpottedState_t_ = clientDLLOffsets["EntitySpottedState_t"]["classes"]["dafieldsta"];
	inline nlohmann::json C_CSGameRules_= clientDLLOffsets["C_CSGameRules"]["classes"]["fields"];
	inline nlohmann::json CCSWeaponBaseVData_ = clientDLLOffsets["CCSWeaponBaseVData"]["classes"]["fields"];
};


namespace offsets {
	inline nlohmann::json clientDLL = json::readFromJsonFile(json::offsetFile)["client.dll"];
};



class CCSPlayerController{
public:
	uintptr_t entityList;
	int id;

	CCSPlayerController(uintptr_t base) {
		entityList = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwEntityList"]);
	}

	uintptr_t listEntry;
	uintptr_t getListEntry();

	uintptr_t value;
	uintptr_t getController();

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
	uintptr_t entityList;

	C_CSPlayerPawn(uintptr_t base) {
		entityList = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwEntityList"]);
	}

	uintptr_t listEntry;
	uintptr_t getListEntry();

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

	uint64_t C_CSWeaponBase;
	uint16_t weaponID;
	std::string weaponName;
	uint16_t getWeaponID();
	std::string getWeaponName();

	int spotted;
	int getEntitySpotted();

	int owner;
	int getOwner();

	// CGameSceneNode
	uintptr_t CGameSceneNode;
	uintptr_t getCGameSceneNode();

};

class CGameSceneNode {
public:
	uintptr_t value;

	uintptr_t boneArray;
	uintptr_t getBoneArray();

	Vector3 origin;
	Vector3 getOrigin();
};


class LocalPlayer {
public:
	uintptr_t localPlayer;
	uintptr_t base;

	LocalPlayer(uintptr_t baseAddy) {
		base = baseAddy;
		localPlayer = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwLocalPlayerController"]);
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

	int spotted;
	int getEntitySpotted();

	bool isScoped;
	bool getIsScoped();
};


// This is unrelated to all the other classes, but this is the most convenient way to share functions between features
class SharedFunctions {
public:
	static bool spottedCheck(C_CSPlayerPawn C_CSPlayerPawn, LocalPlayer localPlayer);
	static bool inGame(DWORD_PTR base);
};