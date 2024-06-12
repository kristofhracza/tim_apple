#pragma once
#include "imgui.h"

namespace Render {
	void DrawRect(int x, int y, int w, int h, ImColor color, int thick) {
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0, thick);
	}

	void Line(float x1, float y1, float x2, float y2, ImColor color, float thick) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color, thick);
	}
}