#include "windowRenderer.h"
#include "imgui.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "imageData.h"
#include <unordered_map>
#include <string>

namespace knapsackWindow
{

    void Render(std::unordered_map<std::string, ImageData> &loadedImages)
    {

        auto img = loadedImages["img.png"];

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // RGBA: White

        ImGui::Begin("knapsack", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        ImVec2 viewportSize = ImGui::GetIO().DisplaySize;
        ImGui::SetCursorPos(ImVec2(0, 0));
        ImGui::Image(reinterpret_cast<ImTextureID>(img.texture), viewportSize);
        ImGui::Button("Button");
        ImGui::End();
        ImGui::PopStyleColor();
    }
}