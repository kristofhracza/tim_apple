#pragma once
#include "imgui.h"

inline namespace Render {
	inline void DrawRect(int x, int y, int w, int h, ImColor color, int thick) {
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0, thick);
	}

	inline void Line(float x1, float y1, float x2, float y2, ImColor color, float thick) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color, thick);
	}

	inline void DrawGradientLine(ImVec2 start, ImVec2 end, ImColor start_color, ImColor end_color, float thickness) {
		ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(ImVec2(start.x, start.y + thickness), ImVec2(end.x, start.y), start_color, start_color, start_color, start_color);
		ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(ImVec2(start.x - thickness, start.y), ImVec2(start.x, end.y), start_color, start_color, end_color, end_color);
		ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(ImVec2(end.x - thickness, start.y), ImVec2(end.x, end.y), start_color, start_color, end_color, end_color);
		ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(ImVec2(end.x, end.y + thickness), ImVec2(start.x, end.y), end_color, end_color, end_color, end_color);
	}
}