#pragma once
#include "Dx11HookRenderAdapter.h"
#include "../Engine/EngineMath.h"
class CheatRenderContext :public Dx11HookRenderAdapter {
public:
	//以便换用其它引擎
	using CheatVector2D = FVector2D;
	using CheatVector = FVector;
	using CheatVector4 = FVector4;
public:
	void Esp_Line(CheatVector2D Target, ImU32 Color) {
		Dx11HookRenderAdapter::AddLine(0.0f, 0.0f, static_cast<float>(Target.X), static_cast<float>(Target.Y), 1.0f, Color);
	};
	void Esp_Box(CheatVector4 Target, ImU32 Color) {
		Dx11HookRenderAdapter::AddRect(static_cast<float>(Target.X), static_cast<float>(Target.Y), static_cast<float>(Target.W), static_cast<float>(Target.Z), 1.0f, 0.0f, Color);
	};
};
