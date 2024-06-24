#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <Windows.h>

#include "../imgui/imgui.h"
#include "Vectors.h"

inline namespace utils {
	// https://www.unknowncheats.me/forum/dayz-sa/129893-calculate-distance-meters.html
	// https://www.unknowncheats.me/forum/general-programming-and-reversing/478087-calculate-size-esp-boxes-based-distance.html
	inline float getDistance(Vector3 from, Vector3 to) {
		return sqrt(pow(to.x - from.x, 2) + pow(to.y - from.y, 2) + pow(to.z - from.z, 2));
	};

	inline std::wstring getExePath() {
		WCHAR buffer[MAX_PATH] = { 0 };
		GetModuleFileNameW(NULL, buffer, MAX_PATH);
		std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
		return std::wstring(buffer).substr(0, pos);
	}

	inline namespace espF {
		inline float fixFontSize(float size) {
			int returnSize = 1;

			if (size > 4.f) returnSize = 4.f;
			if (size < 1.f) returnSize = 1.f;

			return returnSize;
		}

		// This is with size being 5 !!!
		inline float fixJointSize(float size) {
			int returnSize = 1;

			if (size > 3.f) returnSize = 3.f;
			if (size > 7.f) returnSize = 4.f;
			if (size < 1.f) returnSize = 2.f;

			return returnSize;
		}

		inline float getFontSize(float fontSize,int distance) {
			return (fontSize - utils::fixFontSize(distance));
		}

		inline float getJointSize(float joinSize, int distance) {
			return (joinSize - utils::fixJointSize(distance));
		}

		inline std::tuple<float,float> getTextOffsets(float x,float y, float horizontalDivide,float verticalDivide = 1) {
			float horizontalOffset = x / horizontalDivide;
			float verticalOffset = y - verticalDivide;

			std::tuple<float,float> coords = { horizontalOffset, verticalOffset };
			return coords;
		}
	}
}