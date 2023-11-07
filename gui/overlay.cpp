#include "overlay.hpp"
#include "menu.hpp"

#include "../util/Vectors.h"
#include "../util/MemMan.hpp"
#include "../util/attributes.hpp"

#include "../features/entry.hpp"

WNDCLASSEXW overlayESP::createWindowClass(HINSTANCE hInstance,WNDPROC Wndproc, LPCWSTR windowname) {
	this->hInstance = hInstance;

	windowClass.cbSize = sizeof(WNDCLASSEXA);
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = Wndproc;
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = windowname;

	return windowClass;
};


HWND overlayESP::createWindow(int horizontalSize, int verticallSize) {
	HWND window = nullptr;
	RegisterClassExW(&windowClass);
	window = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, windowClass.lpszClassName, windowClass.lpszClassName, WS_POPUP, 0, 0, 1920, 1080, 0, 0, windowClass.hInstance, 0);
	SetLayeredWindowAttributes(window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);

	this->window = window;

	return window;
}


void overlayESP::makeFrameIntoClientArea() {

	RECT clientArea{};
	GetClientRect(window, &clientArea);

	RECT windowArea{};
	GetWindowRect(window, &windowArea);

	POINT diff{};
	ClientToScreen(window, &diff);

	const MARGINS margins{
		windowArea.left + (diff.x - windowArea.left),
		windowArea.top + (diff.y - windowArea.top),
		clientArea.right,
		clientArea.bottom
	};

	DwmExtendFrameIntoClientArea(window, &margins);
}


void overlayESP::makeDeviceAndSwapChain() {

	swapChain.BufferDesc.RefreshRate.Numerator = 60;
	swapChain.BufferDesc.RefreshRate.Denominator = 1;
	swapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChain.SampleDesc.Count = 1;
	swapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChain.BufferCount = 2;
	swapChain.OutputWindow = window;
	swapChain.Windowed = TRUE;
	swapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChain.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, featureLevels, 2, D3D11_SDK_VERSION, &swapChain, &loadedSwapChain, &device, &loadedLevel, &deviceContext);

	loadedSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	if (backBuffer) {
		device->CreateRenderTargetView(backBuffer, 0, &renderTargetView);
		backBuffer->Release();
	}
};

void overlayESP::initWindow(int nShowCmd) {
	ShowWindow(window, nShowCmd);
	UpdateWindow(window);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	imGuiMenu::normalText= io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 15.f);
	imGuiMenu::titleText = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdanab.ttf", 16.f);
	imGuiMenu::subTitleText = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdanab.ttf", 15.f);
	imGuiMenu::highlightText = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdanai.ttf", 13.f);
	imGuiMenu::espNameText = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdanab.ttf", 15.f);
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, deviceContext);
}

void overlayESP::renderLoop(MemoryManagement::moduleData client) {
	bool state = true;
	bool menutoggle = true;

	while (state){
		if (GetAsyncKeyState(VK_INSERT) & 1){
			menutoggle = !menutoggle;
		}

		MSG msg;
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				state = false;
			}

			if (!state) {
				break;
			}
		}

		if (GetAsyncKeyState(VK_END)) {
			this->destroyWindow();
			exit(0);
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		mainLoop(state,client);

		if (menutoggle) {
			imGuiMenu::renderMenu(state);
			SetWindowLong(window, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
		}
		else {
			SetWindowLong(window, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
		}

		ImGui::EndFrame();
		ImGui::Render();

		float color[4]{ 0.f,0.f ,0.f ,0.f };
		deviceContext->OMSetRenderTargets(1, &renderTargetView, 0);
		deviceContext->ClearRenderTargetView(renderTargetView, color);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		loadedSwapChain->Present(1, 0);

		Sleep(1);
	}
}

void overlayESP::destroyWindow() {
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (loadedSwapChain) {
		loadedSwapChain->Release();
	}
	if (deviceContext) {
		deviceContext->Release();
	}
	if (device) {
		device->Release();
	}
	if (renderTargetView) {
		renderTargetView->Release();
	}

	DestroyWindow(window);
	UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);
}