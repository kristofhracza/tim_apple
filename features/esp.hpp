#pragma once

#include <string>
#include <format>

#include "../gui/overlay.hpp"
#include "../gui/menu.hpp"

#include "../util/MemMan.hpp"
#include "../util/attributes.hpp"
#include "../util/config.hpp"
#include "../util/Vectors.h"

#include "../util/utilFunctions.hpp"
#include "../util/weaponInfo.hpp"

namespace esp {
	inline namespace sharedData {
		inline float width, height;
		inline Vector3 headPos, origin, headPosToScreen, originalPosToScreen;
		inline Vector3 localOrigin;
		inline Vector3 entityOrigin;
		inline uint64_t weaponID;
		inline int distance;
	};

	inline float normalESPText = 15.f;
	inline float sideESPText = 13.f;

	void makeHealthBar(float health);
	void makeSkeleton(view_matrix_t viewMatrix, uintptr_t boneArray);
	void makeName(std::string name);
	void makeWeaponname();
	void makeDistance();

	void boundingBox(Vector3 origin, view_matrix_t viewMatrix, std::string name, int health, uintptr_t boneArray,bool isSpotted = false);
}