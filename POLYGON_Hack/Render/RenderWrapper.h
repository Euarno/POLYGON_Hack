#pragma once
#include <memory>
#include <functional>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
class RenderWrapper {
public:
	virtual ~RenderWrapper() = default;
public:
	std::function<void(void)> RenderBack = nullptr;
	std::function<bool(void)> IsUITouchAllowed = nullptr;
	std::function<bool(void)> IsRenderAllowed = nullptr;
public:

	virtual bool Initialize(std::function<void(void)> RenderBack, std::function<bool(void)> IsUITouchAllowed, std::function<bool(void)> IsRenderAllowed) {
		this->RenderBack = RenderBack;
		this->IsUITouchAllowed = IsUITouchAllowed;
		this->IsRenderAllowed = IsRenderAllowed;
		return true;
	};
	virtual void AddLine(float x1, float y1, float x2, float y2, float width, ImU32 color) = 0;
	virtual void AddRect(float x, float y, float w, float h, float width, float rounding, ImU32 color) = 0;
	virtual void AddRectFilled(float x, float y, float w, float h, ImU32 color) = 0;
	virtual void AddCircle(float x, float y, float r, float num, float width, ImU32 color) = 0;
	virtual void AddCircleFilled(float x, float y, float r, float num, ImU32 color) = 0;
	virtual void AddStrokeText(float x, float y, ImU32 color, ImU32 color_background, const char* text) = 0;
	virtual void AddText(float x, float y, ImU32 color, const char* text) = 0;
};


