#include "app.h"
#include "imgui.h"
#include "windowRenderer.h"
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
    void RenderWindows()
    {
        mainMenuBar();
        ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight() + 1));
        // ImGui::ShowDemoWindow();
        // templateWindow::Render();
        graphWindow::Render();
    }
}

// metodo maestro
// algoritmos greedy
//      analizarlo y ver como funciona
