#include "menu.hpp"

#include "../features/entry.hpp"
#include "../util/config.hpp"


void imGuiMenu::setStyle() {
	// Setting styles
	ImGuiStyle* style = &ImGui::GetStyle();

	// Sizes
	style->FramePadding = ImVec2(5,5);
	style->FrameBorderSize = 1.f;
	style->FrameRounding = 0.f;

	style->WindowPadding = ImVec2(6, 6);
	
	style->GrabRounding = 0.f;
	style->GrabMinSize = 20.f;

	style->ButtonTextAlign = ImVec2(0.5, 0.5);

	style->ItemSpacing = ImVec2(9,4);

	// Colour setup
	ImColor darkGrey = ImColor(29, 31, 31, 255);
	ImColor lightGrey = ImColor(38, 42, 43, 255);
	ImColor lightGreyTrans = ImColor(38, 42, 43, 175);

	ImColor darkBlue = ImColor(52, 98, 237, 255);
	ImColor lightBlue = ImColor(78, 139, 246, 255);

	// Colours
	style->Colors[ImGuiCol_FrameBg] = lightGrey;
	style->Colors[ImGuiCol_FrameBgHovered] = darkGrey;
	style->Colors[ImGuiCol_FrameBgActive] = darkGrey;

	style->Colors[ImGuiCol_TitleBgActive] = darkBlue;
	style->Colors[ImGuiCol_TitleBgCollapsed] = lightGreyTrans;

	style->Colors[ImGuiCol_ChildBg] = darkGrey;

	style->Colors[ImGuiCol_MenuBarBg] = lightGrey;
	style->Colors[ImGuiCol_WindowBg] = lightGrey;
	
	style->Colors[ImGuiCol_CheckMark] = darkBlue;

	style->Colors[ImGuiCol_Button] = darkBlue;
	style->Colors[ImGuiCol_ButtonHovered] = lightBlue;

	style->Colors[ImGuiCol_SliderGrab] = darkBlue;
	style->Colors[ImGuiCol_SliderGrabActive] = lightBlue;

	style->Colors[ImGuiCol_ResizeGrip] = darkBlue;
	style->Colors[ImGuiCol_ResizeGripHovered] = lightBlue;

	style->Colors[ImGuiCol_HeaderHovered] = darkBlue;
	style->Colors[ImGuiCol_HeaderActive] = lightBlue;
}


void imGuiMenu::verticalSplitter(float width,float height) {
	ImGui::SameLine();
	ImGui::InvisibleButton("vsplitter", ImVec2(8.0f, height));
	if (ImGui::IsItemActive())
		width += ImGui::GetIO().MouseDelta.x;
	ImGui::SameLine();
}


void imGuiMenu::horizontalSplitter(float height) {
	ImGui::InvisibleButton("hsplitter", ImVec2(-1, 8.0f));
	if (ImGui::IsItemActive())
		height += ImGui::GetIO().MouseDelta.y;
}


void imGuiMenu::espRender() {
	if (tabCount == 1) {

		ImGui::BeginChild("Features", ImVec2(imGuiMenu::widthSeparatorInt, imGuiMenu::heightSeparatorInt), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Attributes");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("ESP toggle", &espConf.state);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Bounding Box", &espConf.boundBox);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Player name", &espConf.isPawnName);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Weapon name", &espConf.isPawnGun);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Health bar", &espConf.isHealthBar);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Skeleton", &espConf.skeleton);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Joints", &espConf.joint);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Distance", &espConf.distance);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Snap lines", &espConf.snapLines);
		ImGui::EndChild();

		verticalSplitter(imGuiMenu::widthSeparatorInt, imGuiMenu::heightSeparatorInt);

		ImGui::BeginChild("Feature options", ImVec2(0, imGuiMenu::heightSeparatorInt), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Feature options");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::subTitleText);
		ImGui::Text("Main options");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Visibility check", &espConf.checkSpotted);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::subTitleText);
		ImGui::Text("Health options");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("HP counter", &espConf.hpCounter);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::subTitleText);
		ImGui::Text("Box options");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::SliderFloat("Width", &espConf.width, 1.f, 5.f);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::SliderFloat("Thickness", &espConf.boundBoxThickness, 1.f, 3.f);
		ImGui::EndChild();

		horizontalSplitter(HEIGHT);

		ImGui::BeginChild("Colours", ImVec2(0, 0), true);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Colours");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit3("Box spotted", (float*)&espConf.spottedColours);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit3("Box not spotted", (float*)&espConf.notSpottedColours);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit3("Atrributes colour", (float*)&espConf.attributeColours);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit3("Skeleton colour", (float*)&espConf.skeletonColours);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::ColorEdit3("Joint colours", (float*)&espConf.jointColours);
		ImGui::EndChild();
	}
}

void imGuiMenu::aimRender() {
	if (tabCount == 2) {

		ImGui::BeginChild("Aimbot", ImVec2(imGuiMenu::widthSeparatorInt, imGuiMenu::heightSeparatorInt), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Aimbot");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Aimbot", &aimConf.state);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Fov circle", &aimConf.fovCircle);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Visibility check", &aimConf.checkSpotted);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::SliderFloat("FOV", &aimConf.fov, 1.f, 25.f);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::SliderFloat("Smoothing", &aimConf.smoothing, 1.f, 5.f);
		ImGui::EndChild();

		verticalSplitter(imGuiMenu::widthSeparatorInt, imGuiMenu::heightSeparatorInt);

		ImGui::BeginChild("Misc", ImVec2(0, imGuiMenu::heightSeparatorInt), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Miscellaneous aim functions");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Recoil Control", &aimConf.rcs);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Trigger Bot", &aimConf.trigger);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Trigger bot hot key", &aimConf.isHotTrigger);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		if (aimConf.isHotTrigger) {
			if (ImGui::BeginCombo("Hot key", aimConf.hotKey[aimConf.hotSelectTrigger].c_str())) {
				for (int i = 0; i < aimConf.hotKey.size(); ++i) {
					const bool isSelected = (aimConf.hotTrigger == i);

					if (ImGui::Selectable(aimConf.hotKey[i].c_str(), isSelected)) {
						aimConf.hotSelectTrigger = i;
					}

					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
		}
		ImGui::EndChild();

		horizontalSplitter(HEIGHT);

		ImGui::BeginChild("Hitboxes", ImVec2(0, 0), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Hitboxes");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		if (ImGui::BeginCombo("Hit box", aimConf.bones[aimConf.boneSelect].c_str())) {
			for (int i = 0; i < aimConf.bones.size(); ++i) {
				const bool isSelected = (aimConf.bone == i);

				if (ImGui::Selectable(aimConf.bones[i].c_str(), isSelected)) {
					aimConf.boneSelect = i;
				}

				if (isSelected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Aim bot hot key", &aimConf.isHotAim);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		if (aimConf.isHotAim) {
			if (ImGui::BeginCombo("Hot key", aimConf.hotKey[aimConf.hotSelectAim].c_str())) {
				for (int i = 0; i < aimConf.hotKey.size(); ++i) {
					const bool isSelected = (aimConf.hotAim == i);

					if (ImGui::Selectable(aimConf.hotKey[i].c_str(), isSelected)) {
						aimConf.hotSelectAim = i;
					}

					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
		}
		ImGui::EndChild();
	}
}

void imGuiMenu::miscRender() {
	if (tabCount == 3) {
		ImGui::BeginChild("Movement", ImVec2(0, imGuiMenu::heightSeparatorInt), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Movement");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Bunny hop", &miscConf.bunnyHop);
		ImGui::EndChild();

		horizontalSplitter(HEIGHT);

		ImGui::BeginChild("Visual", ImVec2(0, 0), true);
		ImGui::PushFont(imGuiMenu::titleText);
		ImGui::Text("Visual");
		ImGui::PopFont();
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Anti flash", &miscConf.flash);
		ImGui::Dummy(ImVec2(0.0f, textSeparatorSpace));
		ImGui::Checkbox("Dropped Item ESP", &miscConf.itemESP);
		ImGui::EndChild();
	}
}

void imGuiMenu::menuBar() {
	ImGui::BeginMenuBar();

	if (ImGui::MenuItem("ESP")) {
		tabCount = 1;
	}

	if (ImGui::MenuItem("Aim")) {
		tabCount = 2;
	}

	if (ImGui::MenuItem("Misc")) {
		tabCount = 3;
	}

	ImGui::EndMenuBar();
}


void imGuiMenu::renderMenu(bool state) {
	ImGui::PushFont(normalText);
	ImGui::SetNextWindowSize({WIDTH,HEIGHT}, ImGuiCond_FirstUseEver);
	ImGui::Begin("Tim Apple", &state, ImGuiWindowFlags_MenuBar);
	
	// Config
	setStyle();
	menuBar();

	// Menus
	espRender();
	aimRender();
	miscRender();

	ImGui::PopFont();
	ImGui::End();
}