#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "../json/jsonOps.hpp"

struct espConfig {
	bool state;
	bool checkSpotted;

	bool boundBox = true;
	bool gradient;
	bool filledBox = true;
	float filledBoxAlpha = 0.2f;
	float boundBoxThickness = 1.5f;
	float spottedColours[3] = { 0.f,1.f,0.75f };
	float notSpottedColours[3] = { 0.f,1.f,0.75f };
	float cornerColours[3] = { 1.f,1.f,1.f };
	float cornerGradient[3] = { 1.f,1.f,1.f };
	float width = 2.5f;

	bool isPawnName;
	std::string pawnName;

	bool isPawnGun;
	std::string pawnGun;

	bool isHealthBar = true;
	bool hpCounter;
	float health[3];

	float attributeColours[3] = { 1.f,1.f,1.f };

	bool skeleton;
	float skeletonColours[3] = { 1.f,1.f,1.f };

	bool head;
	float headColours[3] = { 1.f,1.f,1.f };

	bool joint;
	float jointColours[3] = { 1.f,1.f,1.f };

	bool snapLines;

	bool distance;

	inline nlohmann::json to_json();
	inline bool from_json(nlohmann::json json);
};
espConfig espConf = {};


struct aimConfig {
	bool state;
	bool rcs;
	bool trigger;

	bool checkSpotted = true;
	float smoothing = 3.2f;

	float fov = 2.5;
	bool fovCircle;

	int bone;
	int boneSelect = 0;
	std::vector<std::string> bones = { "Head", "Neck","Chest", "Crotch" };
	std::map <std::string, int> boneMap = { {"Head",6},{"Neck",5},{"Chest",4},{"Crotch",0} };

	int aimMode = 3;
	std::vector<std::string> aimModes = { "Closest to Player", "Closest to Crosshair", "Furthest from crosshair", "No preference" };
	std::map <std::string, int> aimModeMap = { {"Closest to Player",0},{"Closest to Crosshair",1},{"Furthest from crosshair",2},{"No preference",3} };

	bool isHotAim;
	int hotSelectAim = 0;
	int hotAim;

	float sens = 1.25f;

	bool isHotTrigger;
	int hotSelectTrigger = 0;
	int hotTrigger;

	bool playerLock;

	std::vector<std::string> hotKey = { "SHIFT","ALT","CTRL","Left mouse","Right mouse" };
	std::map <std::string, int> hotKeyMap = { {"SHIFT",VK_SHIFT}, {"ALT",VK_MENU},{"CTRL",VK_CONTROL},{"Left mouse",VK_LBUTTON},{"Right mouse",VK_RBUTTON} };

	inline nlohmann::json to_json();
	inline bool from_json(nlohmann::json json);
};
aimConfig aimConf = {};


struct miscConfig {
	bool bunnyHop;
	bool flash;
	bool itemESP;
	bool deathmatchMode;
	bool fovCheck = false;
	int fov = 90;

	inline nlohmann::json to_json();
	inline bool from_json(nlohmann::json json);
};
miscConfig miscConf = {};

inline namespace config {
	inline nlohmann::json configFile = json::readFromJsonFile(json::configFile);

	nlohmann::json to_json();
	void load();
	void save();
	void create();
	bool exists();
}

enum bones : int {
	head            = 6,
	neck            = 5,
	chest           = 4,
	chest_1         = 2,
	shoulderRight   = 8,
	shoulderLeft    = 13,
	elbowRight      = 9,
	elbowLeft       = 14,
	handRight       = 11,
	handLeft        = 16,
	crotch          = 0,
	leftCrotch      = 22,
	rightCrotch     = 25,
	kneeRight       = 26,
	kneeLeft        = 23,
	ankleRight      = 27,
	ankleLeft       = 24,
};

struct BoneConnection {
	int bone1;
	int bone2;

	BoneConnection(int b1, int b2) : bone1(b1), bone2(b2) {}
};

BoneConnection boneConnections[] = {
	BoneConnection(bones::head, bones::neck),
	BoneConnection(bones::neck, bones::chest),
	BoneConnection(bones::chest,bones::crotch),
	BoneConnection(bones::chest, bones::shoulderRight),
	BoneConnection(bones::shoulderRight, bones::elbowRight),
	BoneConnection(bones::elbowRight, bones::handRight),
	BoneConnection(bones::chest, bones::shoulderLeft),
	BoneConnection(bones::shoulderLeft, bones::elbowLeft),
	BoneConnection(bones::elbowLeft, bones::handLeft),
	BoneConnection(bones::chest, bones::chest_1),
	BoneConnection(bones::crotch, bones::leftCrotch),
	BoneConnection(bones::crotch, bones::rightCrotch),
	BoneConnection(bones::leftCrotch, bones::kneeLeft),
	BoneConnection(bones::kneeLeft,bones::ankleLeft),
	BoneConnection(bones::rightCrotch, bones::kneeRight),
	BoneConnection(bones::kneeRight, bones::ankleRight)
};

namespace timAppleSystem {
	std::string weaponIconsTTF = ".\\fonts\\weaponIcons.ttf";
}