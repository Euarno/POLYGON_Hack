#pragma once
#include <DesignPattern/SingleWrapper.h>
#include <Render/CheatRenderContext.h>
class CheatMain :public SingleWrapper<CheatMain>{
public:
	CheatMain()noexcept = default;
	~CheatMain()noexcept = default;




public:
	static void Render(const std::shared_ptr<CheatRenderContext>& RenderIns) {
		return;
	}
};