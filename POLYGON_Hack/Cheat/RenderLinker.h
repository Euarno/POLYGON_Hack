#pragma once
#include <functional>
#include <memory>
#include <Render/CheatRenderContext.h>
#include <Menu/Menu.h>
#include <Cheat/CheatMain.h>

class RenderLinker {
public:
    RenderLinker() noexcept = default;
    ~RenderLinker() noexcept = default;
public:
    bool Initialize(const std::shared_ptr<CheatRenderContext>& RenderIns) noexcept {
        m_RenderIns = RenderIns;
        return true;
    }

    static void Render() noexcept {
        Menu::getInstance().Render();
        if (m_RenderIns) {
            CheatMain::getInstance().Render(m_RenderIns);
        }
    }

    static bool IsUItouchAllowed() noexcept {
        return true;
    }

    static bool IsRenderAllowedFn() noexcept {
        return true;
    }

    auto GetDrawBackFn() noexcept -> std::function<void()> {
        return &Render;
    }

    auto GetIsUItouchAllowedFn() noexcept -> std::function<bool()> {
        return &IsUItouchAllowed;
    }

    auto GetIsRenderAllowedFn() noexcept -> std::function<bool()> {
        return &IsRenderAllowedFn;
    }

private:
    static std::shared_ptr<CheatRenderContext> m_RenderIns;
};


//类外初始化
std::shared_ptr<CheatRenderContext> RenderLinker::m_RenderIns = nullptr;