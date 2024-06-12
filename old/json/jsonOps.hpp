#pragma once

#include <fstream>

#include "json.hpp"

#include "../util/utilFunctions.hpp"

namespace json {
	inline std::wstring clientDLLFile = L"\\client.dll.json";
	inline std::wstring offsetFile = L"\\offsets.json";
	inline std::wstring buttonsFile = L"\\buttons.json";

	nlohmann::json readFromJsonFile(std::wstring fileName);
}
