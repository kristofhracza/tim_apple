#include "misc.hpp"


void misc::bunnyHop(DWORD_PTR base, int flags) {
	if (GetAsyncKeyState(VK_SPACE) && flags & bhopInAir) {
		MemMan.WriteMem<int>(base + offsets::clientDLL["dwForceJump"]["value"], 65537);
	}
	else {
		MemMan.WriteMem<int>(base + offsets::clientDLL["dwForceJump"]["value"], 256);
	}
}

void misc::droppedItem(C_CSPlayerPawn C_CSPlayerPawn, CGameSceneNode CGameSceneNode, view_matrix_t viewMatrix) {
	for (int i = 65; i < 1024; i++) {
		// Entity
		C_CSPlayerPawn.value = i;
		C_CSPlayerPawn.getListEntry();
		if (C_CSPlayerPawn.listEntry == 0) continue;
		C_CSPlayerPawn.getPlayerPawn();
		if (C_CSPlayerPawn.getOwner() != -1) continue;

		// Entity name
		uintptr_t entity = MemMan.ReadMem<uintptr_t>(C_CSPlayerPawn.playerPawn + 0x10);
		uintptr_t designerNameAddy = MemMan.ReadMem<uintptr_t>(entity + 0x20);

		char designerNameBuffer[MAX_PATH]{}; 
		MemMan.ReadRawMem(designerNameAddy, designerNameBuffer, MAX_PATH);

		std::string name = std::string(designerNameBuffer);

		if (strstr(name.c_str(), "weapon_")) name.erase(0, 7);
		else if (strstr(name.c_str(), "_projectile")) name.erase(name.length() - 11, 11);
		else if (strstr(name.c_str(), "baseanimgraph")) name = "defuse kit";
		else continue;

		// Origin position of entity
		CGameSceneNode.value = C_CSPlayerPawn.getCGameSceneNode();
		CGameSceneNode.getOrigin();
		CGameSceneNode.origin = CGameSceneNode.origin.worldToScreen(viewMatrix);

		// Drawing
		if (CGameSceneNode.origin.z >= 0.01f) {
			ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
			auto [horizontalOffset, verticalOffset] = getTextOffsets(textSize.x, textSize.y, 2.f);

			ImFont* gunText = {};
			if (std::filesystem::exists(timAppleSystem::weaponIconsTTF)) {
				gunText = imGuiMenu::weaponIcons;
				name = gunIcon(name);
			}
			else gunText = imGuiMenu::espNameText;

			ImGui::GetBackgroundDrawList()->AddText(gunText, 12, { CGameSceneNode.origin.x - horizontalOffset, CGameSceneNode.origin.y - verticalOffset }, ImColor(espConf.attributeColours[0], espConf.attributeColours[1], espConf.attributeColours[2]), name.c_str());
		}
	}
}
