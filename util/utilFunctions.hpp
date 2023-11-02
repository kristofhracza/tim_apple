#pragma once

#include <string>

#include "Vectors.h"

inline namespace utils {
	// https://www.unknowncheats.me/forum/dayz-sa/129893-calculate-distance-meters.html
	// https://www.unknowncheats.me/forum/general-programming-and-reversing/478087-calculate-size-esp-boxes-based-distance.html
	inline float getDistance(Vector3 from, Vector3 to) {
		return sqrt(pow(to.x - from.x, 2) + pow(to.y - from.y, 2) + pow(to.z - from.z, 2));
	};

	inline std::wstring getExePath() {
		TCHAR buffer[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
		return std::wstring(buffer).substr(0, pos);
	}
}