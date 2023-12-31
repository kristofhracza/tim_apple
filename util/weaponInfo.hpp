#pragma once

enum ItemDefinitionIndex {
    weapon_deagle = 1,
    weapon_elite = 2,
    weapon_fiveseven = 3,
    weapon_glock = 4,
    weapon_ak47 = 7,
    weapon_aug = 8,
    weapon_awp = 9,
    weapon_famas = 10,
    weapon_g3sg1 = 11,
    weapon_galilar = 13,
    weapon_m249 = 14,
    weapon_m4a1 = 16,
    weapon_mac10 = 17,
    weapon_p90 = 19,
    weapon_ump = 24,
    weapon_xm1014 = 25,
    weapon_bizon = 26,
    weapon_mag7 = 27,
    weapon_negev = 28,
    weapon_sawedoff = 29,
    weapon_tec9 = 30,
    weapon_taser = 31,
    weapon_hkp2000 = 32,
    weapon_mp7 = 33,
    weapon_mp9 = 34,
    weapon_nova = 35,
    weapon_p250 = 36,
    weapon_scar20 = 38,
    weapon_sg556 = 39,
    weapon_ssg08 = 40,
    weapon_knife = 42,
    weapon_flashbang = 43,
    weapon_hegrenade = 44,
    weapon_smokegrenade = 45,
    weapon_molotov = 46,
    weapon_decoy = 47,
    weapon_incgrenade = 48,
    weapon_c4 = 49,
    weapon_knife_t = 59,
    weapon_m4a1_silencer = 60,
    weapon_usp_silencer = 61,
    weapon_cz75a = 63,
    weapon_revolver = 64,
    weapon_bayonet = 500,
    weapon_knife_flip = 505,
    weapon_knife_gut = 506,
    weapon_knife_karambit = 507,
    weapon_knife_m9_bayonet = 508,
    weapon_knife_tactical = 509,
    weapon_knife_falchion = 512,
    weapon_knife_survival_bowie = 514,
    weapon_knife_butterfly = 515,
    weapon_knife_push = 516
};

inline const char* getWeaponFromID(uint16_t id) {
    switch (id) {
    case weapon_deagle:         return "Desert Eagle";
    case weapon_elite:          return "Dual-Elites";
    case weapon_fiveseven:      return "Five-Seven";
    case weapon_glock:          return "Glock";
    case weapon_ak47:           return "AK-47";
    case weapon_aug:            return "AUG";
    case weapon_awp:            return "AWP";
    case weapon_famas:          return "Famas";
    case weapon_g3sg1:          return "G3SG1";
    case weapon_galilar:        return "Galil";
    case weapon_m249:           return "M249";
    case weapon_m4a1:           return "M4A4";
    case weapon_mac10:          return "MAC-10";
    case weapon_p90:            return "P90";
    case weapon_ump:            return "UMP";
    case weapon_xm1014:         return "XM1014";
    case weapon_bizon:          return "PP-Bizon";
    case weapon_mag7:           return "Mag7";
    case weapon_negev:          return "Negev";
    case weapon_sawedoff:       return "Sawed-off";
    case weapon_tec9:           return "Tec9";
    case weapon_taser:          return "Zeus";
    case weapon_hkp2000:        return "P2000";
    case weapon_mp7:            return "MP7";
    case weapon_mp9:            return "MP9";
    case weapon_nova:           return "Nova";
    case weapon_p250:           return "P-250";
    case weapon_scar20:         return "Scar20";
    case weapon_sg556:          return "SG556";
    case weapon_ssg08:          return "SSG-08";
    case weapon_flashbang:      return "Flashbang";
    case weapon_hegrenade:      return "HE Granade";
    case weapon_smokegrenade:   return "Smoke";
    case weapon_molotov:        return "Molotov";
    case weapon_decoy:          return "Decoy";
    case weapon_incgrenade:     return "Molotov";
    case weapon_c4:             return "C4";
    case weapon_m4a1_silencer:  return "M4A1-S";
    case weapon_usp_silencer:   return "USP-S";
    case weapon_cz75a:          return "CZ-75a";
    case weapon_revolver:       return "Revolver";
    case weapon_bayonet:
    case weapon_knife:
    case weapon_knife_t:
    case weapon_knife_flip:
    case weapon_knife_gut:
    case weapon_knife_karambit:
    case weapon_knife_m9_bayonet:
    case weapon_knife_tactical:
    case weapon_knife_falchion:
    case weapon_knife_survival_bowie:
    case weapon_knife_butterfly:
    case weapon_knife_push:
        return "Knife";
    default:
        return "Unknown";
    }
}

// Big thanks to FoxHvh https://www.unknowncheats.me/forum/members/4389301.html
// Thread: https://www.unknowncheats.me/forum/counter-strike-2-a/608799-weapon-icon-esp.html
inline const char* gunIcon(const std::string& weapon){
    std::map<std::string, const char*> gunIcons = {
        {"ak47", "W"},
        {"m4a4", "M"},
        {"mp9", "R"},
        {"famas", "H"},
        {"ump45", "b"},
        {"glock", "D"},
        {"knife_ct", "]"},
        {"knife_t", "["},
        {"deagle", "A"},
        {"elite", "B"},
        {"fiveseven", "C"},
        {"revolver", "J"},
        {"hkp2000", "E"},
        {"p250", "F"},
        {"usp_silencer", "G"},
        {"tec9", "H"},
        {"cz75a", "I"},
        {"mac10", "K"},
        {"ump45", "L"},
        {"bizon", "M"},
        {"mp7", "N"},
        {"mp9", "R"},
        {"mp5sd","x"},
        {"p90", "P"},
        {"galilar", "Q"},
        {"famas", "R"},
        {"m4a1_silencer", "T"},
        {"m4a1", "S"},
        {"aug", "U"},
        {"sg556", "V"},
        {"ak47", "W"},
        {"g3sg1", "X"},
        {"scar20", "Y"},
        {"awp", "Z"},
        {"ssg08", "a"},
        {"ssg-08", "a"},
        {"xm1014", "b"},
        {"sawedoff", "c"},
        {"mag7", "d"},
        {"nova", "e"},
        {"negev", "f"},
        {"m249", "g"},
        {"taser", "h"},
        {"flashbang", "i"},
        {"hegrenade", "j"},
        {"smokegrenade", "k"},
        {"molotov", "l"},
        {"decoy", "m"},
        {"incgrenade", "n"},
        {"c4", "o"},
        {"defuse kit", "r" },
   };

    auto it = gunIcons.find(weapon);
    if (it != gunIcons.end()) {
        return it->second;
    }

    return "";
}