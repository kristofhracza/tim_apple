#include "misc.hpp"


void misc::bunnyHop(DWORD_PTR base, int flags) {
	if (GetAsyncKeyState(VK_SPACE) && flags & bhopInAir) {
		MemMan.WriteMem<int>(base + offsets::clientDLL["dwForceJump"]["value"], 65537);
	}
	else {
		MemMan.WriteMem<int>(base + offsets::clientDLL["dwForceJump"]["value"], 256);
	}
}