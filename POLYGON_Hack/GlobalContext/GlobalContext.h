#pragma once
#include <memory>
#include <DesignPattern/SingleWrapper.h>
#include <Console/ConsoleContext.h>
#include <Render/CheatRenderContext.h>
#include <Cheat/RenderLinker.h>

class GlobalContext : public SingleWrapper<GlobalContext>
{
public:
	GlobalContext() noexcept = default;
	~GlobalContext() = default;
public:
	bool Initialize() noexcept {
		if (InitConsole()) {
			auto& ConsoleIns = ConsoleContext::getInstance();
			ConsoleIns.Output(ConsoleColor::Green, "[GlobalContext-Initialize] InitConsole succeeded.\n");

			if (InitRender()) {
				ConsoleIns.Output(ConsoleColor::Green, "[GlobalContext-Initialize] InitRender succeeded.\n");

				if (InitLinker()) {
					ConsoleIns.Output(ConsoleColor::Green, "[GlobalContext-Initialize] InitLinker succeeded.\n");

					if (BindRenderLinker()) {
						ConsoleIns.Output(ConsoleColor::Green, "[GlobalContext-Initialize] BindRenderLinker succeeded.\n");

						if (BindCheatRender()) {
							ConsoleIns.Output(ConsoleColor::Green, "[GlobalContext-Initialize] BindCheatRender succeeded.\n");
						}
						else {
							ConsoleIns.Output(ConsoleColor::Red, "[GlobalContext-Initialize] BindCheatRender failed.\n");
						}
					}
					else {
						ConsoleIns.Output(ConsoleColor::Red, "[GlobalContext-Initialize] BindRenderLinker failed.\n");
					}
				}
				else {
					ConsoleIns.Output(ConsoleColor::Red, "[GlobalContext-Initialize] InitLinker failed.\n");
				}
			}
			else {
				ConsoleIns.Output(ConsoleColor::Red, "[GlobalContext-Initialize] InitRender failed.\n");
			}
		}
		else {
			auto& ConsoleIns = ConsoleContext::getInstance();
			ConsoleIns.Output(ConsoleColor::Red, "[GlobalContext-Initialize] InitConsole failed.\n");
		}
		return false;
	}
private:
	bool InitRender() noexcept {
		m_RenderInstance = std::make_shared<CheatRenderContext>();
		if (!m_RenderInstance) {

			return false;
		}
		return true;
	}

	bool InitLinker() noexcept {
		m_LinkerInstance = std::make_shared<RenderLinker>();
		if (!m_LinkerInstance) {

			return false;
		}
		return true;
	}

	bool InitConsole() {
		auto& ConsoleIns = ConsoleContext::getInstance();
		if (ConsoleIns.Alloc()) {
			return true;
		}
		return false;
	}
	bool FreeConsole() {
		auto& ConsoleIns = ConsoleContext::getInstance();
		if (ConsoleIns.Free()) {
			return true;
		}
		return false;
	}
	bool BindRenderLinker() noexcept {
		if (!m_LinkerInstance->Initialize(m_RenderInstance)) {

			return false;
		}
		return true;
	}

	bool BindCheatRender() noexcept {
		if (!m_RenderInstance->Initialize(
			m_LinkerInstance->GetDrawBackFn(),
			m_LinkerInstance->GetIsUItouchAllowedFn(),
			m_LinkerInstance->GetIsRenderAllowedFn())) {

			return false;
		}
		return true;
	}
private:
	std::shared_ptr<CheatRenderContext> m_RenderInstance = nullptr;
	std::shared_ptr<RenderLinker> m_LinkerInstance = nullptr;
};
