#include "app.h"
#include "imgui.h"
#include "windowRenderer.h"
#include <unordered_map>
#include <iostream>

static void mainMenuBar()
{
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // RGBA: White
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));      // Black text

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Project"))
        {
            if (ImGui::MenuItem("Coloracion de grafos"))
            {
            }
            if (ImGui::MenuItem("Knapsack"))
            {
            }
            if (ImGui::MenuItem("Subsetsum"))
            {
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    ImGui::PopStyleColor(2);
}

namespace app
{
    static bool isInitialized = false;

    void RenderWindows(std::unordered_map<std::string, ImageData> &loadedImages)
    {
        mainMenuBar();
        ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight() + 1));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::ShowDemoWindow();
        // templateWindow::Render();
        // graphWindow::Render();
        knapsackWindow::Render(loadedImages);
        // subsetsumWindow::Render();
    }
}
