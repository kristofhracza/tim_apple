#include "esp.hpp"


void esp::makeHealthBar(float health) {
	int healthBarYOffset = ((int)(sharedData::height * health * 0.01f));

	float red = (255.f - (health * 2.55f)) - 100.f;
	float green = (health * 2.55f) / 100.f;

	ImGui::GetBackgroundDrawList()->AddRectFilled({ sharedData::headPosToScreen.x - (sharedData::width + 2.f), sharedData::originalPosToScreen.y - sharedData::height}, { sharedData::headPosToScreen.x - (sharedData::width + 4.5f), sharedData::originalPosToScreen.y }, ImColor(0.f, 0.f, 0.f, 0.3f));
	ImGui::GetBackgroundDrawList()->AddRectFilled({ sharedData::headPosToScreen.x - (sharedData::width + 2.f), sharedData::originalPosToScreen.y - healthBarYOffset }, { sharedData::headPosToScreen.x - (sharedData::width + 4.5f), sharedData::originalPosToScreen.y }, ImColor(red, green, 0.f, 1.f));
	if (espConf.hpCounter) {
		ImGui::GetBackgroundDrawList()->AddText(imGuiMenu::espNameText, getFontSize(sideESPText,distance), {sharedData::headPosToScreen.x - (sharedData::width + 10.f), sharedData::originalPosToScreen.y - healthBarYOffset - 12.f}, ImColor(espConf.attributeColours[0], espConf.attributeColours[1], espConf.attributeColours[2]), std::to_string((int)health).c_str());
	}
}


void esp::makeSkeleton(view_matrix_t viewMatrix, uintptr_t boneArray) {
	ImColor skeletonColour = ImColor(espConf.skeletonColours[0], espConf.skeletonColours[1], espConf.skeletonColours[2]);
	ImColor jointColour = ImColor(espConf.jointColours[0], espConf.jointColours[1], espConf.jointColours[2]);
	Vector3 previous, current;

	if (espConf.joint) {
		Vector3 headBone = MemMan.ReadMem<Vector3>(boneArray + 6 * 32);
		Vector3 headBonePos = headBone.worldToScreen(viewMatrix);
		ImGui::GetBackgroundDrawList()->AddCircleFilled({ headBonePos.x,headBonePos.y }, getJointSize(5.f, distance), jointColour);
	}

	for (std::vector<int> currentGroup : boneGroups::allGroups) {
		previous = { 0.f,0.f,0.f };

		for (int currentBone : currentGroup) {
			current = MemMan.ReadMem<Vector3>(boneArray + currentBone * 32);

			if (previous.IsZero()) {
				previous = current;
				continue;
			}

			Vector3 currentScreenPos = current.worldToScreen(viewMatrix);
			Vector3 previousScreenPos = previous.worldToScreen(viewMatrix);

			ImGui::GetBackgroundDrawList()->AddLine({ previousScreenPos.x,previousScreenPos.y }, { currentScreenPos.x,currentScreenPos.y }, skeletonColour,1.5f);

			if (espConf.joint) ImGui::GetBackgroundDrawList()->AddCircleFilled({ currentScreenPos.x,currentScreenPos.y }, getJointSize(5.f, distance), jointColour);

			previous = current;
		}
	}
}
 

void esp::makeName(std::string name) {
	ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
	auto [horizontalOffset, verticalOffset] =  getTextOffsets(textSize.x,textSize.y, 2.f);

	ImGui::GetBackgroundDrawList()->AddText(imGuiMenu::espNameText, getFontSize(normalESPText, distance), {sharedData::headPosToScreen.x - horizontalOffset, sharedData::headPosToScreen.y - verticalOffset}, ImColor(espConf.attributeColours[0], espConf.attributeColours[1], espConf.attributeColours[2]), name.c_str());
}


void esp::makeWeaponname() {
	std::string name = getWeaponFromID(weaponID);
	ImVec2 textSize = ImGui::CalcTextSize(name.c_str());

	auto [horizontalOffset, verticalOffset] = getTextOffsets(textSize.x, textSize.y, 2.f, (sharedData::height + 15.f));

	ImGui::GetBackgroundDrawList()->AddText(imGuiMenu::espNameText, getFontSize(normalESPText, distance), { sharedData::headPosToScreen.x - horizontalOffset, sharedData::headPosToScreen.y - verticalOffset }, ImColor(espConf.attributeColours[0], espConf.attributeColours[1], espConf.attributeColours[2]), name.c_str());
}

void esp::makeDistance() {
	std::string distanceText = std::format("[{} m]", std::to_string(sharedData::distance));
	ImVec2 textSize = ImGui::CalcTextSize(distanceText.c_str());

	auto [horizontalOffset, verticalOffset] = getTextOffsets(textSize.x, textSize.y, 2.f);

	ImGui::GetBackgroundDrawList()->AddText(imGuiMenu::espNameText, getFontSize(sideESPText, distance), { sharedData::headPosToScreen.x - horizontalOffset, sharedData::headPosToScreen.y - verticalOffset - 12}, ImColor(espConf.attributeColours[0], espConf.attributeColours[1], espConf.attributeColours[2]), distanceText.c_str());
}


void esp::boundingBox(Vector3 origin, view_matrix_t viewMatrix, std::string name, int health, uintptr_t boneArray, bool isSpotted) {
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
	width = width / 10.f;
	sharedData::height = height;
	sharedData::width = width;

	if (originalPosToScreen.z >= 0.01f) {
		if (espConf.boundBox) {
			ImColor colour;
			isSpotted == true ? colour = ImColor(espConf.spottedColours[0], espConf.spottedColours[1], espConf.spottedColours[2]) : colour = ImColor(espConf.notSpottedColours[0], espConf.notSpottedColours[1], espConf.notSpottedColours[2]);

			ImGui::GetBackgroundDrawList()->AddRect({ headPosToScreen.x - width, headPosToScreen.y }, { headPosToScreen.x + width, originalPosToScreen.y }, colour, 0.f, 0.f, espConf.boundBoxThickness);
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
			ImGui::GetBackgroundDrawList()->AddLine({ headPosToScreen.x - (width / 2.f), originalPosToScreen.y }, { (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) }, ImColor(1.0f, 1.0f, 1.0f, 1.0f));
		}

		if (espConf.distance) {
			makeDistance();
		}
	}
}