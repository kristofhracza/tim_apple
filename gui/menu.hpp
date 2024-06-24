#pragma once

#include "../imgui/imgui.h"

namespace imGuiMenu {
	inline float WIDTH = 650.f;
	inline float HEIGHT = 720.f;

	inline int tabCount = 1;

	inline float areaSeparatorSpace = 8.f;
	inline float textSeparatorSpace = 4.f;
	inline float widthSeparatorInt = WIDTH / 2;
	inline float heightSeparatorInt = HEIGHT / 2 + 20;

	inline ImFont* normalText;
	inline ImFont* titleText;
	inline ImFont* highlightText;
	inline ImFont* espNameText;
	inline ImFont* subTitleText;
	inline ImFont* weaponIcons;


	void menuBar();
	void renderMenu(bool state);
	void setStyle();

	void verticalSplitter(float width, float height);
	void horizontalSplitter(float height);


	void espRender();
	void aimRender();
	void miscRender();
	void aboutMeRender();
	void configRender();
}