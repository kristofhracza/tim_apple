#pragma once

#include <string>
#include <vector>
#include <map>

struct espConfig {
	bool state = true;
	bool checkSpotted;

	bool boundBox = true;
	bool filledBox = true;
	float filledBoxAlpha = 0.2f;
	float boundBoxThickness = 1.5f;
	float spottedColours[3] = { 0.f,1.f,0.75f };
	float notSpottedColours[3] = { 0.f,1.f,0.75f };
	float cornerColours[3] = { 1.f,1.f,1.f };
	float width = 2.5f;

	bool isPawnName;
	std::string pawnName;

	bool isPawnGun = true;
	std::string pawnGun;

	bool isHealthBar =  true;
	bool hpCounter;
	float health[3];

	float attributeColours[3] = { 1.f,1.f,1.f };

	bool skeleton = true;
	float skeletonColours[3] = { 1.f,1.f,1.f };

	bool joint;
	float jointColours[3] = { 1.f,1.f,1.f };

	bool snapLines;

	bool distance;
};
inline espConfig espConf = {};


struct aimConfig {
	bool state = false;
	bool rcs;
	bool trigger;

	bool checkSpotted;
	float smoothing = 1.f;

	float fov = 2.5;
	bool fovCircle;

	int bone;
	int boneSelect = 0;
	std::vector<std::string> bones = { "Head", "Neck","Chest", "Crotch"};
	std::map <std::string, int> boneMap = { {"Head",6},{"Neck",5},{"Chest",4},{"Crotch",0}};

	bool isHotAim;
	int hotSelectAim = 0;
	int hotAim;

	bool isHotTrigger;
	int hotSelectTrigger = 0;
	int hotTrigger;

	bool playerLock = true;

	std::vector<std::string> hotKey = {"SHIFT","ALT","CTRL","Left mouse","Right mouse"};
	std::map <std::string, int> hotKeyMap = { {"SHIFT",VK_SHIFT}, {"ALT",VK_MENU},{"CTRL",VK_CONTROL},{"Left mouse",VK_LBUTTON},{"Right mouse",VK_RBUTTON}};
};
inline aimConfig aimConf;


struct miscConfig{
	bool bunnyHop;
	bool flash;
	bool itemESP;
};
inline miscConfig miscConf;


enum bones : int {
	head = 6,
	neck = 5,
	chest = 4,
	shoulderRight = 8,
	shoulderLeft = 13,
	elbowRight = 9,
	elbowLeft = 14,
	handRight = 11,
	handLeft = 16,
	crotch = 0,
	kneeRight = 23,
	kneeLeft = 26,
	ankleRight = 24,
	ankleLeft = 27,
};


inline namespace boneGroups {
	inline std::vector<int> mid = {bones::head,bones::neck,bones::chest,bones::crotch};
	inline std::vector<int> leftArm = { bones::neck,bones::shoulderLeft,bones::elbowLeft,bones::handLeft};
	inline std::vector<int> righttArm = { bones::neck,bones::shoulderRight,bones::elbowRight,bones::handRight };
	inline std::vector<int> leftLeg = {bones::crotch,bones::kneeLeft,bones::ankleLeft};
	inline std::vector<int> rightLeg = { bones::crotch,bones::kneeRight,bones::ankleRight};
	inline std::vector<std::vector<int>> allGroups = {mid,leftArm,righttArm,leftLeg,rightLeg};
};

inline namespace timAppleSystem {
	inline std::string weaponIconsTTF = ".\\fonts\\weaponIcons.ttf";
}

typedef struct espConfig tEspConfig;
typedef struct aimConfig tAimConfig;
typedef struct miscConfig tMiscConfig;

int config_LoadFromJson(tEspConfig& stEsp, tAimConfig& stAim, tMiscConfig& stMisc);
int config_PutToJson(tEspConfig& stEsp, tAimConfig& stAim, tMiscConfig& stMisc);