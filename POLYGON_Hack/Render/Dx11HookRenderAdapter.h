#pragma once
#include <Windows.h>
#include <d3d11.h>
#include "RenderWrapper.h"

class Dx11HookRenderAdapter : public RenderWrapper {
public:
    Dx11HookRenderAdapter() {
        OwnPtr = this;
    }

private:
    static Dx11HookRenderAdapter* OwnPtr;
public:
    virtual bool Initialize(std::function<void(void)> RenderBack,std::function<bool(void)> IsUITouchAllowed, std::function<bool(void)> IsRenderAllowed)  override;
    virtual void AddLine(float x1, float y1, float x2, float y2, float width, ImU32 color) override;
    virtual void AddRect(float x, float y, float w, float h, float width, float rounding, ImU32 color) override;
    virtual void AddRectFilled(float x, float y, float w, float h, ImU32 color) override;
    virtual void AddCircle(float x, float y, float r, float num, float width, ImU32 color) override;
    virtual void AddCircleFilled(float x, float y, float r, float num, ImU32 color) override;
    virtual void AddStrokeText(float x, float y, ImU32 color, ImU32 color_background, const char* text) override;
    virtual void AddText(float x, float y, ImU32 color, const char* text) override;

private:
    static void    WINAPI GetDxContext();
    static HRESULT WINAPI RenderInit(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
    static HRESULT WINAPI HookFn_Present(IDXGISwapChain* This, UINT SyncInterval, UINT Flags);
    static HRESULT WINAPI HookFn_ResizeBuffers(IDXGISwapChain* This, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
    static LRESULT WINAPI HookFn_WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    static bool GetSwapChain();
    static bool GetVirtualMethodTable(uintptr_t* Table, int index, uintptr_t* Method);
    static bool ChangeVirtualMethodTable(uintptr_t* Table, int index, void* NewMethod);
    static bool ChangeWndProc(WNDPROC NewWndProc, WNDPROC* OldWndProc);

private:
    typedef HRESULT(__stdcall* PresentFn) (IDXGISwapChain* This, UINT SyncInterval, UINT Flags);
    typedef HRESULT(__stdcall* ResizeBuffersFn) (IDXGISwapChain* This, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

    PresentFn Og_Present = nullptr;
    ResizeBuffersFn Og_ResizeBuffers = nullptr;
    WNDPROC Og_WndProc = nullptr;

private:
    HWND GameWindow = nullptr;
    IDXGISwapChain* SwapChain = nullptr;
    ID3D11Device* Device = nullptr;
    ID3D11DeviceContext* DeviceContext = nullptr;
    ID3D11RenderTargetView* mainRenderTargetView = nullptr;
    uintptr_t* DirectxVirtualMethodTable = nullptr;
};
