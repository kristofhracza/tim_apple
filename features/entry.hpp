#pragma once

#include "esp.hpp"
#include "aim.hpp"
#include "fov.hpp"
#include "misc.hpp"
#include "include.hpp"

#include "../util/config.hpp"
#include "../util/utilFunctions.hpp"

void mainLoop(bool state, MemoryManagement::moduleData client);
C_CSPlayerPawn doPreferred(C_CSPlayerPawn C_CSPlayerPawn_, CGameSceneNode CGameSceneNode, LocalPlayer localPlayer, uintptr_t preferredTarget, view_matrix_t viewMatrix, int mode, MemoryManagement::moduleData client);