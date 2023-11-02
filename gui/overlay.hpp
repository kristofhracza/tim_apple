#pragma once

#define WIN32_LEAN_AND_MEAN 

#include <Windows.h>
#include <dwmapi.h>
#include <d3d11.h>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"

#include "../util/MemMan.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class overlayESP {
public:

	HINSTANCE hInstance;
	WNDCLASSEXW windowClass;
	HWND window;

	DXGI_SWAP_CHAIN_DESC swapChain{};
	D3D_FEATURE_LEVEL featureLevels[2]{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0
	};
	ID3D11Device* device{ 0 };
	ID3D11DeviceContext* deviceContext{ 0 };
	IDXGISwapChain* loadedSwapChain{ 0 };
	ID3D11RenderTargetView* renderTargetView{ 0 };
	D3D_FEATURE_LEVEL loadedLevel{};
	ID3D11Texture2D* backBuffer{ 0 };


	WNDCLASSEXW createWindowClass(HINSTANCE hInstance,WNDPROC Wndproc,LPCWSTR windowname);

	HWND createWindow(int horizontalSize, int verticallSize);

	void makeFrameIntoClientArea();

	void makeDeviceAndSwapChain();

	void initWindow(int nShowCmd);

	void renderLoop(MemoryManagement::moduleData client);

	void destroyWindow();
};