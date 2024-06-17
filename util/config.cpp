#include <Windows.h>
#include "config.hpp"
#include <stdio.h>

#include <iostream>
#include <fstream>
#include "../json/json.hpp"

using json = nlohmann::json;


// Serialization for espConfig
void to_json(json& j, const espConfig& espConf) {
	j = json {
		{"state", espConf.state},
		{"checkSpotted", espConf.checkSpotted},
		{"boundBox", espConf.boundBox},
		{"filledBox", espConf.filledBox},
		{"filledBoxAlpha", espConf.filledBoxAlpha},
		{"boundBoxThickness", espConf.boundBoxThickness},
		{"spottedColours", espConf.spottedColours},
		{"notSpottedColours", espConf.notSpottedColours},
		{"cornerColours", espConf.cornerColours},
		{"width", espConf.width},
		{"isPawnName", espConf.isPawnName},
		{"pawnName", espConf.pawnName},
		{"isPawnGun", espConf.isPawnGun},
		{"pawnGun", espConf.pawnGun},
		{"isHealthBar", espConf.isHealthBar},
		{"hpCounter", espConf.hpCounter},
		{"health", espConf.health},
		{"attributeColours", espConf.attributeColours},
		{"skeleton", espConf.skeleton},
		{"skeletonColours", espConf.skeletonColours},
		{"joint", espConf.joint},
		{"jointColours", espConf.jointColours},
		{"snapLines", espConf.snapLines},
		{"distance", espConf.distance}
	};
}

// Deserialization for espConfig
void from_json(const json& j, espConfig& espConf) {
	j.at("state").get_to(espConf.state);
	j.at("checkSpotted").get_to(espConf.checkSpotted);
	j.at("boundBox").get_to(espConf.boundBox);
	j.at("filledBox").get_to(espConf.filledBox);
	j.at("filledBoxAlpha").get_to(espConf.filledBoxAlpha);
	j.at("boundBoxThickness").get_to(espConf.boundBoxThickness);
	j.at("spottedColours").get_to(espConf.spottedColours);
	j.at("notSpottedColours").get_to(espConf.notSpottedColours);
	j.at("cornerColours").get_to(espConf.cornerColours);
	j.at("width").get_to(espConf.width);
	j.at("isPawnName").get_to(espConf.isPawnName);
	j.at("pawnName").get_to(espConf.pawnName);
	j.at("isPawnGun").get_to(espConf.isPawnGun);
	j.at("pawnGun").get_to(espConf.pawnGun);
	j.at("isHealthBar").get_to(espConf.isHealthBar);
	j.at("hpCounter").get_to(espConf.hpCounter);
	j.at("health").get_to(espConf.health);
	j.at("attributeColours").get_to(espConf.attributeColours);
	j.at("skeleton").get_to(espConf.skeleton);
	j.at("skeletonColours").get_to(espConf.skeletonColours);
	j.at("joint").get_to(espConf.joint);
	j.at("jointColours").get_to(espConf.jointColours);
	j.at("snapLines").get_to(espConf.snapLines);
	j.at("distance").get_to(espConf.distance);
}

// Serialization for aimConfig
void to_json(json& j, const aimConfig& aimConf) {
	j = json {
		{"state", aimConf.state},
		{"checkSpotted", aimConf.checkSpotted},
		{"smoothing", aimConf.smoothing},
		{"fov", aimConf.fov},
		{"fovCircle", aimConf.fovCircle},
		{"bone", aimConf.bone},
		{"boneSelect", aimConf.boneSelect},
		{"bones", aimConf.bones},
		{"boneMap", aimConf.boneMap},
		{"isHotAim", aimConf.isHotAim},
		{"hotSelectAim", aimConf.hotSelectAim},
		{"hotAim", aimConf.hotAim},
		{"isHotTrigger", aimConf.isHotTrigger},
		{"hotSelectTrigger", aimConf.hotSelectTrigger},
		{"hotTrigger", aimConf.hotTrigger},
		{"hotKey", aimConf.hotKey},
		{"hotKeyMap", aimConf.hotKeyMap},
		{"rcs", aimConf.rcs},
		{"playerLock", aimConf.playerLock},
		{"trigger", aimConf.trigger}
	};
}

// Deserialization for aimConfig
void from_json(const json& j, aimConfig& aimConf) {
	j.at("state").get_to(aimConf.state);
	j.at("checkSpotted").get_to(aimConf.checkSpotted);
	j.at("smoothing").get_to(aimConf.smoothing);
	j.at("fov").get_to(aimConf.fov);
	j.at("fovCircle").get_to(aimConf.fovCircle);
	j.at("bone").get_to(aimConf.bone);
	j.at("boneSelect").get_to(aimConf.boneSelect);
	j.at("bones").get_to(aimConf.bones);
	j.at("boneMap").get_to(aimConf.boneMap);
	j.at("isHotAim").get_to(aimConf.isHotAim);
	j.at("hotSelectAim").get_to(aimConf.hotSelectAim);
	j.at("hotAim").get_to(aimConf.hotAim);
	j.at("isHotTrigger").get_to(aimConf.isHotTrigger);
	j.at("hotSelectTrigger").get_to(aimConf.hotSelectTrigger);
	j.at("hotTrigger").get_to(aimConf.hotTrigger);
	j.at("hotKey").get_to(aimConf.hotKey);
	j.at("hotKeyMap").get_to(aimConf.hotKeyMap);
	j.at("rcs").get_to(aimConf.rcs);
	j.at("playerLock").get_to(aimConf.playerLock);
	j.at("trigger").get_to(aimConf.trigger);
}

// Serialization for miscConfig
void to_json(json& j, const miscConfig& miscConf) {
	j = json {
		{"bunnyHop", miscConf.bunnyHop},
		{"flash", miscConf.flash},
		{"itemESP", miscConf.itemESP}
	};
}

// Deserialization for miscConfig
void from_json(const json& j, miscConfig& miscConf) {
	j.at("bunnyHop").get_to(miscConf.bunnyHop);
	j.at("flash").get_to(miscConf.flash);
	j.at("itemESP").get_to(miscConf.itemESP);
}

int config_LoadFromJson(tEspConfig& stEsp, tAimConfig& stAim, tMiscConfig& stMisc)
{
	#pragma warning(disable:4996)
	FILE* f = fopen("config.json", "r");
	if (f) {
		fclose(f);

		json loadedJson;
		std::ifstream loadFile("config.json");
		loadFile >> loadedJson;

		stEsp = loadedJson["espConfig"].get<espConfig>();
		stAim = loadedJson["aimConfig"].get<aimConfig>();
		stMisc = loadedJson["miscConfig"].get<miscConfig>();
	}
	else {
		json configJson;
		to_json(configJson["espConfig"], stEsp);
		to_json(configJson["aimConfig"], stAim);
		to_json(configJson["miscConfig"], stMisc);
		
		std::ofstream file("config.json");
		file << std::setw(4) << configJson << std::endl;
	}

	return 0;
}

int config_PutToJson(tEspConfig& stEsp, tAimConfig& stAim, tMiscConfig& stMisc)
{
	json configJson;
	to_json(configJson["espConfig"], stEsp);
	to_json(configJson["aimConfig"], stAim);
	to_json(configJson["miscConfig"], stMisc);

	std::ofstream file("config.json");
	file << std::setw(4) << configJson << std::endl;
	return 0;
}