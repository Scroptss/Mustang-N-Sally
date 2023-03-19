#include "menu.h"

ImColor menu_rgb()
{

	{
		if (flHue > 255.0f)
			flHue = 0.0f;
	}

	ImColor EspPnDColorsrgb_menu = ImColor::HSV(flHue, 1.f, 1.f, 0.7f);
	return EspPnDColorsrgb_menu;
}

void rgbstyle()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	vec2_t res = { desktop.right, desktop.bottom };

	ImColor menu_rgb_c = menu_rgb();

	auto& style = ImGui::GetStyle();

	ImGui::SetNextWindowSize(ImVec2(res.x / 3.4, res.y / 2.5), ImGuiCond_Once);

	style.WindowPadding = ImVec2(6, 4);
	style.WindowRounding = 10.f;
	style.FramePadding = ImVec2(5, 2);
	style.FrameRounding = 4.0f;
	style.ItemSpacing = ImVec2(7, 1);
	style.ItemInnerSpacing = ImVec2(1, 1);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 6.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 16.0f;
	style.GrabMinSize = 20.0f;
	style.GrabRounding = 2.0f;
	style.WindowTitleAlign.x = 0.50f;
	style.FrameBorderSize = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.ItemInnerSpacing = ImVec2(5, 0);
}

void runstyle()
{

	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	vec2_t res = { desktop.right, desktop.bottom };

	auto& style = ImGui::GetStyle();

	ImGui::SetNextWindowSize(ImVec2(res.x / 3.4, res.y / 2.5), ImGuiCond_Once);

	style.WindowPadding = ImVec2(6, 4);
	style.WindowRounding = 1.3f;
	style.FramePadding = ImVec2(5, 2);
	style.FrameRounding = 4.0f;
	style.ItemSpacing = ImVec2(7, 1);
	style.ItemInnerSpacing = ImVec2(1, 1);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 6.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 8.0f;
	style.GrabMinSize = 20.0f;
	style.GrabRounding = 2.0f;
	style.WindowTitleAlign.x = 0.50f;
	style.FrameBorderSize = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.ItemInnerSpacing = ImVec2(5, 0);

}

namespace menu
{
	bool is_open()
	{
		return open;
	}
	
	void draw()
	{

		if (menurgb)
		{
			rgbstyle();
		}
		else
		{
			runstyle();
		}

		if (is_open())
		{

			*(int*)((DWORD64)GetModuleHandleA(NULL) + 0x17E71335) = 0;
			ImGui::Begin("Mustang N' Sally", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
			{							
		         	if (ImGui::BeginTabBar("Main", ImGuiTabBarFlags_NoTooltip))
					{				
						players::player_list();

						friends::friends_list();
					
						misc::misc_list();
					}
				
				ImGui::End();
			}
		}
		else
		{
			*(int*)((DWORD64)GetModuleHandleA(NULL) + 0x17E71335) = 1;
		}
	}
}