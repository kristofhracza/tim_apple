#include "esp.hpp"

#include <filesystem>

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
	ImColor headColour = ImColor(espConf.headColours[0], espConf.headColours[1], espConf.headColours[2]);
	for (int i = 0; i < sizeof(boneConnections) / sizeof(boneConnections[0]); i++) {
		int bone1 = boneConnections[i].bone1;
		int bone2 = boneConnections[i].bone2;

		Vector3 VectorBone1 = MemMan.ReadMem<Vector3>(boneArray + bone1 * 32);
		Vector3 VectorBone2 = MemMan.ReadMem<Vector3>(boneArray + bone2 * 32);

		Vector3 b1 = VectorBone1.worldToScreen(viewMatrix);
		Vector3 b2 = VectorBone2.worldToScreen(viewMatrix);

		if (espConf.head) {
			Vector3 headBone = MemMan.ReadMem<Vector3>(boneArray + bones::head * 32);
			Vector3 headBonePos = headBone.worldToScreen(viewMatrix);
			ImGui::GetBackgroundDrawList()->AddCircle({ headBonePos.x,headBonePos.y }, 40.f/(distance == 0 ? 1 : distance), headColour);
		}

		if (espConf.joint) ImGui::GetBackgroundDrawList()->AddCircleFilled({ b1.x, b1.y }, getJointSize(5.f, distance), jointColour);

		Render::Line(b1.x, b1.y, b2.x, b2.y, skeletonColour, 1.5);
	}
}


void esp::makeName(std::string name) {
	ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
	auto [horizontalOffset, verticalOffset] =  getTextOffsets(textSize.x,textSize.y, 2.f);

	ImGui::GetBackgroundDrawList()->AddText(imGuiMenu::espNameText, getFontSize(normalESPText, distance), {sharedData::headPosToScreen.x - horizontalOffset, sharedData::headPosToScreen.y - verticalOffset}, ImColor(espConf.attributeColours[0], espConf.attributeColours[1], espConf.attributeColours[2]), name.c_str());
}


void esp::makeWeaponname() {
	std::string name;
	if (strcmp(sharedData::weaponName.c_str(), "") == 0 || !std::filesystem::exists(timAppleSystem::weaponIconsTTF)) {
		name = getWeaponFromID(sharedData::weaponID);
		ImVec2 textSize = ImGui::CalcTextSize(name.c_str());

		auto [horizontalOffset, verticalOffset] = getTextOffsets(textSize.x, textSize.y, 2.f, (sharedData::height + 15.f));

		ImGui::GetBackgroundDrawList()->AddText(imGuiMenu::espNameText, getFontSize(normalESPText, distance), { sharedData::headPosToScreen.x - horizontalOffset, sharedData::headPosToScreen.y - verticalOffset }, ImColor(espConf.attributeColours[0], espConf.attributeColours[1], espConf.attributeColours[2]), name.c_str());
	}
	else {
		name = gunIcon(weaponName);
		ImVec2 textSize = ImGui::CalcTextSize(name.c_str());

		auto [horizontalOffset, verticalOffset] = getTextOffsets(textSize.x, textSize.y, 2.f, (sharedData::height + 15.f));

		ImGui::GetBackgroundDrawList()->AddText(imGuiMenu::weaponIcons, getFontSize(normalESPText, distance), { sharedData::headPosToScreen.x - horizontalOffset - textSize.x, sharedData::headPosToScreen.y - verticalOffset }, ImColor(espConf.attributeColours[0], espConf.attributeColours[1], espConf.attributeColours[2]), name.c_str());
	}
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
			ImColor filledBoxcolour;
			isSpotted == true ? filledBoxcolour = ImColor(espConf.spottedColours[0], espConf.spottedColours[1], espConf.spottedColours[2], espConf.filledBoxAlpha) : filledBoxcolour = ImColor(espConf.notSpottedColours[0], espConf.notSpottedColours[1], espConf.notSpottedColours[2], espConf.filledBoxAlpha);

			if (!espConf.gradient) ImGui::GetBackgroundDrawList()->AddRect({ headPosToScreen.x - width, headPosToScreen.y }, { headPosToScreen.x + width, originalPosToScreen.y }, ImColor(espConf.cornerColours[0], espConf.cornerColours[1], espConf.cornerColours[2], 1.f), 0.f, 0.f, espConf.boundBoxThickness);
			else Drawing::DrawGradientLine({ headPosToScreen.x - width, headPosToScreen.y }, { headPosToScreen.x + width, originalPosToScreen.y }, ImColor(espConf.cornerColours[0], espConf.cornerColours[1], espConf.cornerColours[2], 1.f), ImColor(espConf.cornerGradient[0], espConf.cornerGradient[1], espConf.cornerGradient[2], 1.f), espConf.boundBoxThickness);
			if (espConf.filledBox) ImGui::GetBackgroundDrawList()->AddRectFilled({ headPosToScreen.x - width, headPosToScreen.y }, { headPosToScreen.x + width, originalPosToScreen.y }, filledBoxcolour, 0.f, 0.f);
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