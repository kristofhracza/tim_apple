#include "fov.hpp"

void fov::setFov(int newFov, LocalPlayer localPlayer) {

	uintptr_t cameraServices = MemMan.ReadMem<uintptr_t>(localPlayer.getPlayerPawn() + clientDLL::C_BasePlayerPawn_["m_pCameraServices"]);
	int currentFOV = MemMan.ReadMem<int>(cameraServices + clientDLL::CCSPlayerBase_CameraServices_["m_iFOV"]);

	if (localPlayer.getIsScoped()) return;
	if (currentFOV == newFov) return;

	MemMan.WriteMem<int>(cameraServices + clientDLL::CCSPlayerBase_CameraServices_["m_iFOV"], newFov);
}