#include "entry.hpp"

void mainLoop(bool state, MemoryManagement::moduleData client) {
	// Classes
	CCSPlayerController		CCSPlayerController(client.base);
	C_CSPlayerPawn			C_CSPlayerPawn(client.base);
	CGameSceneNode			CGameSceneNode;
	LocalPlayer				localPlayer(client.base);
	C_C4					C_C4(client.base);


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

	// Fov
	if (miscConf.fovCheck) fov::setFov(miscConf.fov, localPlayer);

	// Tigger
	if (aimConf.trigger) aim::triggerBot(localPlayer, client.base);


	// Main loop
	for (int i = 0; i < 64; i++) {

		// Player controller
		CCSPlayerController.id = i;
		CCSPlayerController.getListEntry();
		if (!CCSPlayerController.listEntry) continue;
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
		if ((C_CSPlayerPawn.pawnHealth <= 0 || C_CSPlayerPawn.pawnHealth > 100) || strcmp(CCSPlayerController.pawnName.c_str(), "DemoRecorder") == 0) continue;
		if (localPlayer.getTeam() == CCSPlayerController.getPawnTeam() && !miscConf.deathmatchMode) continue;


		// Game scene node
		CGameSceneNode.value = C_CSPlayerPawn.getCGameSceneNode();

		// ESP
		if (espConf.state) {

			if (C_CSPlayerPawn.getPlayerPawn() == localPlayer.getPlayerPawn()) continue;

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

		// C4 ESP
		if (espConf.c4State) {

			CGameSceneNode.value = C_C4.getCGameSceneNode();
			CGameSceneNode.getOrigin();

			esp::drawC4(CGameSceneNode.origin, viewMatrix, localPlayer, C_C4.isPlanted());
		}

		// Aim
		if (aimConf.state) {

			if (C_CSPlayerPawn.getPlayerPawn() == localPlayer.getPlayerPawn()) continue;
			
			// Player lock
			if (aimConf.playerLock) {
				if (aim::lockedPlayer != C_CSPlayerPawn.playerPawn && aim::lockedPlayer != 0) continue;
				if (aim::preferredAimbot == 0) aim::preferredAimbot = doPreferred(C_CSPlayerPawn, CGameSceneNode, localPlayer, aim::preferredAimbot, viewMatrix, aimConf.aimModeMap[aimConf.aimModes[aimConf.aimMode]], client).playerPawn;;
			}
			else {
				aim::preferredAimbot = doPreferred(C_CSPlayerPawn, CGameSceneNode, localPlayer, aim::preferredAimbot, viewMatrix, aimConf.aimModeMap[aimConf.aimModes[aimConf.aimMode]], client).playerPawn;
			}

			C_CSPlayerPawn.playerPawn = aim::preferredAimbot;

			if (C_CSPlayerPawn.getPawnHealth() <= 0 || C_CSPlayerPawn.pawnHealth > 100) {
				aim::preferredAimbot = 0;
				std::cout << "Player dead, switching" << std::endl;
				continue;
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

C_CSPlayerPawn doPreferred(C_CSPlayerPawn C_CSPlayerPawn_, CGameSceneNode CGameSceneNode, LocalPlayer localPlayer, uintptr_t preferredTarget, view_matrix_t viewMatrix, int mode, MemoryManagement::moduleData client) {
	C_CSPlayerPawn target(client.base);
	if (preferredTarget == 0) return C_CSPlayerPawn_;
	target.playerPawn = preferredTarget;

	if (target.getPawnHealth() <= 0 || target.pawnHealth > 100)
		return C_CSPlayerPawn_;

	switch (mode) {
	case 0: {
		if (utils::getDistance(localPlayer.getOrigin(), target.getOrigin()) >
			utils::getDistance(localPlayer.getOrigin(), C_CSPlayerPawn_.getOrigin()))
			return C_CSPlayerPawn_;
		else return target;
	}
	case 1: {
		// C_CSPlayerPawn_ (Next player in entity list)
		Vector3 newOrigin = C_CSPlayerPawn_.getOrigin();
		Vector3 newOriginalPosToScreen = newOrigin.worldToScreen(viewMatrix);

		Vector3 newHeadPos = MemMan.ReadMem<Vector3>(CGameSceneNode.getBoneArray() + aimConf.boneMap[aimConf.bones[aimConf.boneSelect]] * 32);

		Vector3 newHeadPosToScreen = newHeadPos.worldToScreen(viewMatrix);

		// preferredAimbot (Last potential target)
		CGameSceneNode.value = target.getCGameSceneNode();

		Vector3 oldOrigin = target.getOrigin();
		Vector3 oldOriginalPosToScreen = oldOrigin.worldToScreen(viewMatrix);

		Vector3 oldHeadPos = MemMan.ReadMem<Vector3>(CGameSceneNode.getBoneArray() + aimConf.boneMap[aimConf.bones[aimConf.boneSelect]] * 32);

		Vector3 oldHeadPosToScreen = oldHeadPos.worldToScreen(viewMatrix);

		if (utils::getDistance({ oldHeadPosToScreen.x, oldHeadPosToScreen.y }, { (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) / 2 }) >
			utils::getDistance({ newHeadPosToScreen.x, newHeadPosToScreen.y }, { (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) / 2 }))
			return C_CSPlayerPawn_;
		else return target;
	}
	case 2: {
		// C_CSPlayerPawn_ (Next player in entity list)
		Vector3 newOrigin = C_CSPlayerPawn_.getOrigin();
		Vector3 newOriginalPosToScreen = newOrigin.worldToScreen(viewMatrix);

		Vector3 newHeadPos = MemMan.ReadMem<Vector3>(CGameSceneNode.getBoneArray() + aimConf.boneMap[aimConf.bones[aimConf.boneSelect]] * 32);

		Vector3 newHeadPosToScreen = newHeadPos.worldToScreen(viewMatrix);

		// preferredAimbot (Last potential target)
		CGameSceneNode.value = target.getCGameSceneNode();

		Vector3 oldOrigin = target.getOrigin();
		Vector3 oldOriginalPosToScreen = oldOrigin.worldToScreen(viewMatrix);

		Vector3 oldHeadPos = MemMan.ReadMem<Vector3>(CGameSceneNode.getBoneArray() + aimConf.boneMap[aimConf.bones[aimConf.boneSelect]] * 32);

		Vector3 oldHeadPosToScreen = oldHeadPos.worldToScreen(viewMatrix);

		if (utils::getDistance({ oldHeadPosToScreen.x, oldHeadPosToScreen.y }, { (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) / 2 }) >
			utils::getDistance({ newHeadPosToScreen.x, newHeadPosToScreen.y }, { (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) / 2 }))
			return target;
		else return C_CSPlayerPawn_;
	}
	case 3: {
		return C_CSPlayerPawn_;
	}
	default: return C_CSPlayerPawn_;
	}
}