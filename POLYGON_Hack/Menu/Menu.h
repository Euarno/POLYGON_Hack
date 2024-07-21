#pragma once
#include <Render/ImGui/imgui.h>
#include <DesignPattern/SingleWrapper.h>
class Menu :public SingleWrapper<Menu>
{
public:
	Menu()noexcept = default;
	~Menu()noexcept = default;
public:
	static void Render() noexcept {
		ImGui::Begin("Euarno Test");
		ImGui::End();
	}
private:

};
