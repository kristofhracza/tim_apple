#include "../imgui/imgui.h"

namespace imGuiMenu {
	inline float WIDTH = 700.f;
	inline float HEIGHT = 650.f;

	inline int tabCount = 1;

	inline float areaSeparatorSpace = 8.f;
	inline float textSeparatorSpace = 4.f;
	inline float widthSeparatorInt = WIDTH / 2;
	inline float heightSeparatorInt = HEIGHT / 2 + 20;

	inline ImFont* normalText;
	inline ImFont* titleText;
	inline ImFont* highlightText;

	void menuBar();
	void renderMenu(bool state);
	void setStyle();

	void verticalSplitter(float width, float height);
	void horizontalSplitter(float height);


	void espRender();
	void aimRender();
	void miscRender();
}