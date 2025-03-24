#include "windowRenderer.h"
#include "imgui.h"
#include "subsetsum.h"
#include <vector>
#include <algorithm>

namespace subsetsumWindow
{

    static std::vector<int> set = {};
    static int inputNumber = 1; // Input number for the set
    static int sum = -1;        // Sum to find in the subset
    static std::vector<std::vector<bool>> subsetResult = {};

    void Reset()
    {
        set.clear();
        subsetResult.clear();
    }

    void Render()
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // RGBA: White
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));     // Set text color to black

        ImGui::Begin("subsetsum", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        ImVec2 viewportSize = ImGui::GetIO().DisplaySize;
        // ImGui::SetCursorPos(ImVec2(0, 0));

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
        ImGui::Text("Subset Sum");
        ImGui::PopFont();

        ImGui::Spacing();

        if (subsetResult.empty())
        {
            ImGui::PushItemWidth(viewportSize.x * 0.08f);
            ImGui::Text("Input Number");
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::GetStyleColorVec4(ImGuiCol_Button)); // Set input bar background color to button color
            if (ImGui::InputInt("##input", &inputNumber))
            {
                if (inputNumber < 0)
                {
                    inputNumber = 0;
                }
            }
            ImGui::PopStyleColor(); // Restore previous style
            ImGui::PopItemWidth();

            if (ImGui::Button("Add to Set"))
            {
                if (std::find(set.begin(), set.end(), inputNumber) == set.end())
                {
                    set.push_back(inputNumber);
                }
            }

            if (ImGui::Button("Remove Last from Set"))
            {
                if (!set.empty())
                {
                    set.pop_back();
                }
            }

            if (ImGui::Button("Set Sum Value"))
            {
                sum = inputNumber;
            }

            if (!set.empty() && sum != -1)
            {
                if (ImGui::Button("Calculate"))
                {
                    subsetResult = SubsetSum(set, sum);
                }
            }
        }
        else
        {
            if (ImGui::Button("Reset"))
            {
                Reset();
            }
        }

        ImGui::SetCursorPos(ImVec2(viewportSize.x * 0.86f, viewportSize.y * 0.1f)); // Position at the right side of the screen
        ImGui::BeginChild("RightPanel", ImVec2(viewportSize.x * 0.12f, viewportSize.y * 0.3f), true);

        if (sum == -1)
        {
            ImGui::Text("Current Sum: None");
        }
        else
        {
            ImGui::Text("Current Sum: %d", sum);
        }

        ImGui::Separator();
        ImGui::Text("Set:");
        for (int num : set)
        {
            ImGui::BulletText("%d", num);
        }

        ImGui::Separator();
        ImGui::Text("Subset:");
        if (!subsetResult.empty())
        {
            std::vector<int> subset;
            int tempSum = sum;
            for (int i = set.size(); i > 0 && tempSum > 0; --i)
            {
                if (subsetResult[i][tempSum] && !subsetResult[i - 1][tempSum])
                {
                    subset.push_back(set[i - 1]);
                    tempSum -= set[i - 1];
                }
            }
            for (int num : subset)
            {
                ImGui::BulletText("%d", num);
            }
        }
        else
        {
            ImGui::Text("None");
        }

        ImGui::EndChild();

        if (!subsetResult.empty())
        {
            ImVec2 matrixSize = ImVec2(viewportSize.x * 0.6f, viewportSize.y * 0.5f);
            ImVec2 matrixPos = ImVec2((viewportSize.x - matrixSize.x) * 0.5f, (viewportSize.y - matrixSize.y) * 0.5f); // Center the matrix display
            ImGui::SetCursorPos(matrixPos);
            ImGui::SetCursorPos(ImVec2((viewportSize.x - subsetResult[0].size() * 50.0f) * 0.5f, (viewportSize.y - subsetResult.size() * 50.0f) * 0.5f)); // Center the container

            ImVec2 outerContainerSize = ImVec2(viewportSize.x * 0.6f, viewportSize.y * 0.3f);                                                  // 60% of display width, 30% of display height
            ImVec2 outerContainerPos = ImVec2((viewportSize.x - outerContainerSize.x) * 0.5f, (viewportSize.y - outerContainerSize.y) * 0.5f); // Center the container

            ImGui::SetCursorPos(outerContainerPos);
            ImVec2 innerContainerSize = ImVec2(subsetResult[0].size() * 50.0f, subsetResult.size() * 50.0f);
            ImVec2 innerContainerPos = ImVec2((viewportSize.x - innerContainerSize.x) * 0.5f, viewportSize.y * 0.1f); // Align vertically with the sum and set display

            ImGui::SetCursorPos(innerContainerPos);
            ImGui::BeginChild("MatrixDisplay", innerContainerSize, false, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration); // Inner container without borders

            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]); // Use the second font
            ImVec2 textSize = ImGui::CalcTextSize("Subset Result Matrix");
            ImGui::SetCursorPosX((innerContainerSize.x - textSize.x) * 0.5f); // Center horizontally
            ImGui::Text("Subset Result Matrix");
            ImGui::PopFont(); // Restore the previous font
            ImGui::Spacing();

            if (ImGui::BeginTable("SubsetTable", subsetResult[0].size(), ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders)) // Added borders flag
            {
                for (size_t i = 0; i < subsetResult.size(); ++i)
                {
                    ImGui::TableNextRow();
                    for (size_t j = 0; j < subsetResult[i].size(); ++j)
                    {
                        ImGui::TableSetColumnIndex(j);

                        if (i == 0) // First row
                        {
                            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.0f, 0.5f, 1.0f, 1.0f))); // Blue background
                            ImGui::Text("%d", (j == subsetResult[0].size() - 1 ? sum : j));
                        }
                        else if (j == 0) // First column
                        {
                            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.0f, 0.5f, 1.0f, 1.0f))); // Light blueish background
                            ImGui::Text("%d", (i > 0 ? set[i - 1] : 0));
                        }
                        else
                        {
                            ImVec4 cellColor = subsetResult[i][j] ? ImVec4(0.0f, 1.0f, 0.0f, 1.0f) : ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Green for true, red for false
                            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(cellColor));
                            ImGui::Text(" ");
                        }
                    }
                }
                ImGui::EndTable();
            }

            ImGui::EndChild(); // End inner container
        }

        ImGui::End();
        ImGui::PopStyleColor(2);
    }
}