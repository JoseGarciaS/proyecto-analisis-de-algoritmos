#include "app.h"
#include "imgui.h"
#include "windowRenderer.h"
#include <unordered_map>
#include <iostream>

namespace app
{
    static bool isInitialized = false;

    enum Window
    {
        Graph,
        Knapsack,
        Subsetsum
    };

    static Window currentWindow = Window::Graph;

    static void mainMenuBar()
    {
        ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // RGBA: White
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));      // Black text

        ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));       // White background for menu items
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.9f, 0.9f, 0.9f, 1.0f)); // Slightly darker white when hovered

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Project"))
            {
                if (ImGui::MenuItem("Graph coloring"))
                {
                    currentWindow = Window::Graph;
                }
                if (ImGui::MenuItem("Knapsack"))
                {
                    currentWindow = Window::Knapsack;
                }
                if (ImGui::MenuItem("Subset Sum"))
                {
                    currentWindow = Window::Subsetsum;
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
        ImGui::PopStyleColor(4);
    }

    void RenderWindows(std::unordered_map<std::string, ImageData> &loadedImages)
    {
        mainMenuBar();
        ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight() + 1));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

        switch (currentWindow)
        {
        case Window::Graph:
            graphWindow::Render();
            break;
        case Window::Knapsack:
            knapsackWindow::Render(loadedImages);
            break;
        case Window::Subsetsum:
            subsetsumWindow::Render();
            break;
        default:
            break;
        }
    }
}
