#pragma once
#include "Dx11HookRenderAdapter.h"

Dx11HookRenderAdapter* Dx11HookRenderAdapter::OwnPtr = nullptr;
bool Dx11HookRenderAdapter::Initialize(std::function<void(void)> RenderBack, std::function<bool(void)> IsUITouchAllowed, std::function<bool(void)> IsRenderAllowed) {
	RenderWrapper::Initialize(RenderBack, IsUITouchAllowed, IsRenderAllowed);
	if (this->GetSwapChain()) {

		this->GameWindow = ::FindWindowA("UnrealWindow", NULL);


		this->DirectxVirtualMethodTable = *(uintptr_t**)this->SwapChain;
		
		this->GetVirtualMethodTable(this->DirectxVirtualMethodTable, 8, (uintptr_t*)&this->Og_Present);

		this->GetVirtualMethodTable(this->DirectxVirtualMethodTable, 13, (uintptr_t*)&this->Og_ResizeBuffers);
		
		this->ChangeWndProc((WNDPROC)&HookFn_WndProc, &this->Og_WndProc);

		this->ChangeVirtualMethodTable(this->DirectxVirtualMethodTable, 8, &RenderInit);

		this->ChangeVirtualMethodTable(this->DirectxVirtualMethodTable, 13, &HookFn_ResizeBuffers);

		return true;
	}
	return false;
}
void Dx11HookRenderAdapter::AddLine(float x1, float y1, float x2, float y2, float width, ImU32 color) {
	ImGui::GetWindowDrawList()->AddLine(ImVec2(x1, x2), ImVec2(x2, y2), color, width);
};
void Dx11HookRenderAdapter::AddRect(float x, float y, float w, float h, float width, float rounding, ImU32 color) {
	ImGui::GetWindowDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, rounding, 0, width);
};
void Dx11HookRenderAdapter::AddRectFilled(float x, float y, float w, float h, ImU32 color) {
	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.0f, 0);
};
void Dx11HookRenderAdapter::AddCircle(float x, float y, float r, float num, float width, ImU32 color) {
	ImGui::GetWindowDrawList()->AddCircle(ImVec2(x, y), r, color, num, width);
};
void Dx11HookRenderAdapter::AddCircleFilled(float x, float y, float r, float num, ImU32 color) {
	ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(x, y), r, color, num);
};
void Dx11HookRenderAdapter::AddStrokeText(float x, float y, ImU32 color, ImU32 color_background, const char* text) {
	ImGui::GetWindowDrawList()->AddText(ImVec2(x - 1, y + 1), color_background, text);
	ImGui::GetWindowDrawList()->AddText(ImVec2(x - 1, y - 1), color_background, text);
	ImGui::GetWindowDrawList()->AddText(ImVec2(x + 1, y + 1), color_background, text);
	ImGui::GetWindowDrawList()->AddText(ImVec2(x + 1, y - 1), color_background, text);
	ImGui::GetWindowDrawList()->AddText(ImVec2(x, y), color, text);
};
void Dx11HookRenderAdapter::AddText(float x, float y, ImU32 color, const char* text) {
	ImGui::GetWindowDrawList()->AddText(ImVec2(x, y), color, text);
};
void Dx11HookRenderAdapter::GetDxContext() {
	//OwnPtr->SwapChain = pSwapChain;
	OwnPtr->SwapChain->GetDevice(__uuidof(OwnPtr->Device), (void**)&OwnPtr->Device);
	OwnPtr->Device->GetImmediateContext(&OwnPtr->DeviceContext);

	ID3D11Texture2D* RenderTarget = nullptr;
	OwnPtr->SwapChain->GetBuffer(0, __uuidof(RenderTarget), (void**)&RenderTarget);
	OwnPtr->Device->CreateRenderTargetView(RenderTarget, nullptr, &OwnPtr->mainRenderTargetView);
	RenderTarget->Release();
}
HRESULT Dx11HookRenderAdapter::RenderInit(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	static bool isInit = false;
	if (!isInit) {
		isInit = true;
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyhbd.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
		ImGui_ImplWin32_Init(OwnPtr->GameWindow);
	}

	//Get DirectX Context
	Dx11HookRenderAdapter::GetDxContext();


	ImGui_ImplDX11_Init(OwnPtr->Device, OwnPtr->DeviceContext);


	Dx11HookRenderAdapter::ChangeVirtualMethodTable(OwnPtr->DirectxVirtualMethodTable, 8, &Dx11HookRenderAdapter::HookFn_Present);

	return OwnPtr->Og_Present(pSwapChain, SyncInterval, Flags);
}
HRESULT Dx11HookRenderAdapter::HookFn_Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	
	OwnPtr->RenderBack();

	ImGui::Render();
	OwnPtr->DeviceContext->OMSetRenderTargets(1, &OwnPtr->mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return  OwnPtr->Og_Present(pSwapChain, SyncInterval, Flags);
}
HRESULT Dx11HookRenderAdapter::HookFn_ResizeBuffers(IDXGISwapChain* This, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {

	if (OwnPtr->Device) {
		OwnPtr->Device->Release();
		OwnPtr->mainRenderTargetView->Release();
		ImGui_ImplDX11_Shutdown();
		OwnPtr->Device = nullptr;

		OwnPtr->ChangeVirtualMethodTable(OwnPtr->DirectxVirtualMethodTable, 8, &Dx11HookRenderAdapter::RenderInit);
	}
		
	return OwnPtr->Og_ResizeBuffers(This, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}
LRESULT Dx11HookRenderAdapter::HookFn_WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYUP:
		/*if (wParam == VK_HOME)
			*(OwnPtr->UItouch) = !*(OwnPtr->UItouch);*/
		break;
	}
	if (OwnPtr->IsUITouchAllowed()){
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;
	}
	return CallWindowProcA(OwnPtr->Og_WndProc, hWnd, uMsg, wParam, lParam);
}

bool Dx11HookRenderAdapter::GetSwapChain() {
	uintptr_t GameModule = (uintptr_t)GetModuleHandleA((LPCSTR)"POLYGON-Win64-Shipping.exe");

	// 获取第一个偏移量
	uintptr_t FirstOffset = *(uintptr_t*)(GameModule + 0x817B270);

	// 获取第二个偏移量
	uintptr_t SecondOffset = *(uintptr_t*)(FirstOffset + 0x160);

	// 获取第三个偏移量
	uintptr_t ThirdOffset = *(uintptr_t*)(SecondOffset + 0x110);

	uintptr_t  FourthOffset = *(uintptr_t*)(ThirdOffset + 0x8);
	// 返回 IDXGISwapChain 对象的地址
	OwnPtr->SwapChain = *(IDXGISwapChain**)(FourthOffset + 0x10);

	return OwnPtr->SwapChain != nullptr;
}
bool Dx11HookRenderAdapter::GetVirtualMethodTable(uintptr_t* Table, int index, uintptr_t* Method) {
	*Method = Table[index];
	return true;
}
bool Dx11HookRenderAdapter::ChangeVirtualMethodTable(uintptr_t* Table, int index, void* NewMethod) {
	DWORD OldProtect = NULL;
	VirtualProtect((LPVOID)&Table[index], sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &OldProtect);
	Table[index] = (uintptr_t)NewMethod;
	VirtualProtect((LPVOID)&Table[index], sizeof(uintptr_t), OldProtect, &OldProtect);
	return true;

}
bool Dx11HookRenderAdapter::ChangeWndProc(WNDPROC NewWndProc, WNDPROC* OldWndProc) {
	*OldWndProc = (WNDPROC)SetWindowLongPtrA(OwnPtr->GameWindow, GWLP_WNDPROC, (LONG_PTR)NewWndProc);
	return *OldWndProc != NULL;
}
