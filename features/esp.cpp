#include "esp.hpp"

#include "../util/utilFunctions.hpp"
#include "../util/weaponInfo.hpp"

void esp::makeHealthBar(float health) {
	float healthRed = (float)(health * -0.01 + 1);
	float healthGreen = (float)(health * 0.01);

	ImGui::GetBackgroundDrawList()->AddRectFilled({ sharedData::headPosToScreen.x - (sharedData::width + 2), sharedData::originalPosToScreen.y - sharedData::height}, { sharedData::headPosToScreen.x - (sharedData::width + 5.5f), sharedData::originalPosToScreen.y }, ImColor(0.f, 0.f, 0.f, 0.3f));
	if (espConf.hpCounter) {
		ImGui::GetBackgroundDrawList()->AddText({ sharedData::headPosToScreen.x - (sharedData::width + 10) + 1, sharedData::originalPosToScreen.y - (((int)(sharedData::height * health * 0.01f))) - 12 + 1 }, ImColor(1.0f, 1.0f, 1.0f, 1.0f) & IM_COL32_A_MASK, std::to_string((int)health).c_str());
		ImGui::GetBackgroundDrawList()->AddText({ sharedData::headPosToScreen.x - (sharedData::width + 10), sharedData::originalPosToScreen.y - (((int)(sharedData::height * health * 0.01f))) - 12 }, ImColor(1.0f, 1.0f, 1.0f, 1.0f), std::to_string((int)health).c_str());
	}
	ImGui::GetBackgroundDrawList()->AddRectFilled({ sharedData::headPosToScreen.x - (sharedData::width + 2), sharedData::originalPosToScreen.y - ((int)(sharedData::height * health * 0.01f)) }, { sharedData::headPosToScreen.x - (sharedData::width + 5.5f), sharedData::originalPosToScreen.y }, ImColor(healthRed, healthGreen, 0.f, 1.f));
}


void esp::makeSkeleton(view_matrix_t viewMatrix, uintptr_t boneArray) {
	ImColor skeletonColour = ImColor(espConf.skeletonColours[0], espConf.skeletonColours[1], espConf.skeletonColours[2]);
	Vector3 previous, current;

	for (std::vector<int> currentGroup : boneGroups::allGroups) {
		previous = { 0,0,0 };

		for (int currentBone : currentGroup) {
			current = MemMan.ReadMem<Vector3>(boneArray + currentBone * 32);

			if (previous.IsZero()) {
				previous = current;
				continue;
			}

			Vector3 currentScreenPos = current.worldToScreen(viewMatrix);
			Vector3 previousScreenPos = previous.worldToScreen(viewMatrix);

			ImGui::GetBackgroundDrawList()->AddLine({ previousScreenPos.x,previousScreenPos.y }, { currentScreenPos.x,currentScreenPos.y }, skeletonColour,1.f);

			previous = current;
		}
	}
}
 

void esp::makeName(std::string name) {
	ImVec2 textSize = ImGui::CalcTextSize(name.c_str());

	float horizontalOffset = textSize.x / 2.f;
	float verticalOffset = textSize.y;

	ImGui::GetBackgroundDrawList()->AddText({ sharedData::headPosToScreen.x - horizontalOffset + 1, sharedData::headPosToScreen.y - verticalOffset + 1 }, ImColor(1.0f, 1.0f, 1.0f, 1.0f) & IM_COL32_A_MASK, name.c_str());
	ImGui::GetBackgroundDrawList()->AddText({ sharedData::headPosToScreen.x - horizontalOffset, sharedData::headPosToScreen.y - verticalOffset }, ImColor(1.0f, 1.0f, 1.0f, 1.0f), name.c_str());
}


void esp::makeWeaponname() {
	std::string name = getWeaponFromID(weaponID);

	ImVec2 textSize = ImGui::CalcTextSize(name.c_str());

	float horizontalOffset = textSize.x / 2.f;
	float verticalOffset = textSize.y - (sharedData::height + 15);

	ImGui::GetBackgroundDrawList()->AddText({ sharedData::headPosToScreen.x - horizontalOffset + 1, sharedData::headPosToScreen.y - verticalOffset + 1 }, ImColor(1.0f, 1.0f, 1.0f, 1.0f) & IM_COL32_A_MASK, name.c_str());
	ImGui::GetBackgroundDrawList()->AddText({ sharedData::headPosToScreen.x - horizontalOffset, sharedData::headPosToScreen.y - verticalOffset }, ImColor(1.0f, 1.0f, 1.0f, 1.0f), name.c_str());
}

void esp::makeDistance() {
	ImVec2 textSize = ImGui::CalcTextSize(std::to_string(sharedData::distance).c_str());

	float horizontalOffset = textSize.x / 2.f;
	float verticalOffset = textSize.y;

	ImGui::GetBackgroundDrawList()->AddText({ sharedData::headPosToScreen.x - horizontalOffset + 1, sharedData::headPosToScreen.y - verticalOffset - 12  + 1}, ImColor(1.0f, 1.0f, 1.0f, 1.0f) & IM_COL32_A_MASK, std::to_string(sharedData::distance).c_str());
	ImGui::GetBackgroundDrawList()->AddText({ sharedData::headPosToScreen.x - horizontalOffset, sharedData::headPosToScreen.y - verticalOffset - 12}, ImColor(1.0f, 1.0f, 1.0f, 1.0f), std::to_string(sharedData::distance).c_str());
}


void esp::boundingBox(Vector3 origin, view_matrix_t viewMatrix, std::string name, int health, uintptr_t boneArray) {
	if (origin.IsZero()) return;

	Vector3 originalPosToScreen = origin.worldToScreen(viewMatrix);
	sharedData::originalPosToScreen = originalPosToScreen;
	sharedData::origin = origin;

	Vector3 headPos;
	headPos.x = origin.x;
	headPos.y = origin.y;
	headPos.z = origin.z + 75.f;
	sharedData::headPos = headPos;

	Vector3 headPosToScreen = headPos.worldToScreen(viewMatrix);
	sharedData::headPosToScreen = headPosToScreen;

	float height = originalPosToScreen.y - headPosToScreen.y;
	float width = height * espConf.width;
	width = width / 10;
	sharedData::height = height;
	sharedData::width = width;

	if (originalPosToScreen.z >= 0.01f) {
		if (espConf.boundBox) {
			ImGui::GetBackgroundDrawList()->AddRect({ headPosToScreen.x - width, headPosToScreen.y }, { headPosToScreen.x + width, originalPosToScreen.y }, ImColor(espConf.colours[0], espConf.colours[1], espConf.colours[2]), 0, 0, 2.f);
		}
		
		if (espConf.isHealthBar) {
			makeHealthBar(health);
		}

		if (espConf.isPawnName) {
			makeName(name.c_str());
		}

		if (espConf.isPawnGun) {
			makeWeaponname();
		}

		if (espConf.skeleton) {
			makeSkeleton(viewMatrix, boneArray);
		}

		if (espConf.snapLines) {
			ImGui::GetBackgroundDrawList()->AddLine({ headPosToScreen.x - (width / 2), originalPosToScreen.y }, { (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) }, ImColor(1.0f, 1.0f, 1.0f, 1.0f));
		}

		if (espConf.distance) {
			makeDistance();
		}
	}
}