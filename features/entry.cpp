#include "esp.hpp"
#include "aim.hpp"
#include "misc.hpp"

#include "../util/config.hpp"
#include "../util/utilFunctions.hpp"

void mainLoop(bool state, MemoryManagement::moduleData client) {
	// Classes
	CCSPlayerController		CCSPlayerController(client.base);
	C_CSPlayerPawn			C_CSPlayerPawn(client.base);
	CGameSceneNode			CGameSceneNode;
	LocalPlayer				localPlayer(client.base);


	// Shared variables (between features)
	view_matrix_t viewMatrix = MemMan.ReadMem<view_matrix_t>(client.base + offsets::clientDLL["dwViewMatrix"]);
	Vector3 baseViewAngles = MemMan.ReadMem<Vector3>(client.base + offsets::clientDLL["dwViewAngles"]);
	DWORD_PTR baseViewAnglesAddy = client.base + offsets::clientDLL["dwViewAngles"];
	uintptr_t entityList = MemMan.ReadMem<uintptr_t>(client.base + offsets::clientDLL["dwEntityList"]);


	// NOTE: Cheats that only need local player / visuals that don't relate to gameplay
	localPlayer.getPlayerPawn();
	// Aimbot FOV circle
	if (aimConf.fovCircle) {
		ImVec2 p = ImGui::GetWindowPos();
		float screenMidX = GetSystemMetrics(SM_CXSCREEN) / 2.f;
		float screenMidY = GetSystemMetrics(SM_CYSCREEN) / 2.f;

		ImGui::GetBackgroundDrawList()->AddCircle({ screenMidX ,screenMidY }, (aimConf.fov * 10), ImColor(1.f, 1.f, 1.f, 1.f), 0, 1.f);
	}
	// Recoil control
	if (aimConf.rcs) aim::recoilControl(localPlayer, baseViewAnglesAddy);

	// Bunny hop
	if (miscConf.bunnyHop) misc::bunnyHop(client.base, localPlayer.getFlags());

	// Flash
	if (miscConf.flash) localPlayer.noFlash();

	// Tigger
	if (aimConf.trigger) aim::triggerBot(localPlayer, client.base);


	// Main loop
	for (int i = 0; i < 64; i++) {

		// Player controller
		CCSPlayerController.id = i;
		CCSPlayerController.getListEntry();
		CCSPlayerController.getController();
		if (CCSPlayerController.value == 0) continue;
		CCSPlayerController.getPawnName();

		// Player pawn
		C_CSPlayerPawn.value = CCSPlayerController.getC_CSPlayerPawn();
		C_CSPlayerPawn.getListEntry();
		C_CSPlayerPawn.getPlayerPawn();
		C_CSPlayerPawn.getPawnHealth();

		// Checks
		if (aim::lockedPlayer == C_CSPlayerPawn.playerPawn && (C_CSPlayerPawn.pawnHealth <= 0 || (aimConf.checkSpotted && !C_CSPlayerPawn.getEntitySpotted()))) aim::lockedPlayer = 0;
		if ((C_CSPlayerPawn.pawnHealth <= 0 || C_CSPlayerPawn.pawnHealth > 100) || (localPlayer.getTeam() == CCSPlayerController.getPawnTeam() && !miscConf.deathmatchMode) || strcmp(CCSPlayerController.pawnName.c_str(), "DemoRecorder") == 0) continue;


		// Game scene node
		CGameSceneNode.value = C_CSPlayerPawn.getCGameSceneNode();

		// ESP
		if (espConf.state) {

			if (CCSPlayerController.getC_CSPlayerPawn() == localPlayer.getPlayerPawn()) continue;

			esp::sharedData::weaponID = C_CSPlayerPawn.getWeaponID();
			esp::sharedData::weaponName = C_CSPlayerPawn.getWeaponName();
			esp::sharedData::localOrigin = localPlayer.getOrigin();
			esp::sharedData::entityOrigin = C_CSPlayerPawn.getOrigin();
			esp::sharedData::distance = (int)(utils::getDistance(esp::sharedData::localOrigin, esp::sharedData::entityOrigin)) / 100;

			C_CSPlayerPawn.getOrigin();
			CGameSceneNode.getBoneArray();

			if (espConf.checkSpotted) {
				if (SharedFunctions::spottedCheck(C_CSPlayerPawn, localPlayer)) {
					esp::boundingBox(C_CSPlayerPawn.origin, viewMatrix, CCSPlayerController.pawnName, C_CSPlayerPawn.pawnHealth, CGameSceneNode.boneArray,true);
				}
			}
			else {
				esp::boundingBox(C_CSPlayerPawn.origin, viewMatrix, CCSPlayerController.pawnName, C_CSPlayerPawn.pawnHealth, CGameSceneNode.boneArray,SharedFunctions::spottedCheck(C_CSPlayerPawn, localPlayer));
			}
		}

		// Aim
		if (aimConf.state) {

			// Player lock
			if (aimConf.playerLock) {
				if (aim::lockedPlayer != C_CSPlayerPawn.playerPawn && aim::lockedPlayer != 0) continue;
			}

			CGameSceneNode.value = C_CSPlayerPawn.getCGameSceneNode();
			CGameSceneNode.getBoneArray();

			localPlayer.getCameraPos();
			localPlayer.getEyePos();
			localPlayer.getViewAngles();

			if (aimConf.checkSpotted) {
				if (SharedFunctions::spottedCheck(C_CSPlayerPawn, localPlayer)) {
					aim::aimBot(localPlayer, baseViewAngles, C_CSPlayerPawn.playerPawn, CGameSceneNode.boneArray, client);
				}
			}
			else {
				aim::aimBot(localPlayer, baseViewAngles, C_CSPlayerPawn.playerPawn, CGameSceneNode.boneArray, client);
			}
		}
	}

	// Dropped Item
	if (miscConf.itemESP) misc::droppedItem(C_CSPlayerPawn, CGameSceneNode,viewMatrix);
}