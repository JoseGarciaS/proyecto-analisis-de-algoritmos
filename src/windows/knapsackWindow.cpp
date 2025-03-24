#include "windowRenderer.h"
#include "imgui.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "imageData.h"
#include <unordered_map>
#include <string>
#include "knapsack.h"
#include <random>
#include <algorithm>

namespace knapsackWindow
{
    static std::vector<Item> items = {
        {"TV", 400, 50},
        {"Speakers", 300, 30},
        {"Tablet", 150, 5},
        {"Camera", 200, 10},
        {"Plant1", 50, 5},
        {"Lamp", 70, 10},
        {"Painting", 120, 15},
        {"SmallPlant", 30, 3},
        {"Plant2", 50, 5},
        {"MediumSofa", 300, 50},
        {"LargeSofa", 500, 80},
        {"Books", 20, 2},
        {"Clock", 100, 10},
    };

    static std::vector<Item *> stealableItems = {};
    static int capacity = 100;
    int maxCapacity = 275;

    int maxStealableItems = 13;
    static int stealableItemsCount = 10;
    static bool looted = false;

    void PopulateStealableItems()
    {
        stealableItems.clear();

        for (auto &item : items)
        {
            item.stolen = false;
            item.stealable = false;
        }

        std::random_device rd;
        std::mt19937 rng(rd());

        std::shuffle(items.begin(), items.end(), rng);

        for (int i = 0; i < stealableItemsCount; ++i)
        {
            items[i].stealable = true;
            stealableItems.push_back(&items[i]);
        }
    }

    void markStolenItems(int capacity, const std::vector<Item *> &items, const std::vector<std::vector<int>> &dp)
    {
        int n = items.size();
        int w = capacity;

        for (int i = n; i > 0 && w > 0; --i)
        {
            if (dp[i][w] != dp[i - 1][w]) // Item was included
            {
                items[i - 1]->stolen = true; // Mark the item as stolen
                w -= items[i - 1]->weight;   // Reduce the remaining capacity
            }
        }
    }

    void Render(std::unordered_map<std::string, ImageData> &loadedImages)
    {

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // RGBA: White

        ImGui::Begin("knapsack", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        ImVec2 viewportSize = ImGui::GetIO().DisplaySize;

        ImGui::SetCursorPos(ImVec2(0, 0));
        // // Background
        ImGui::Image(reinterpret_cast<ImTextureID>(loadedImages["Background.png"].texture), viewportSize);

        for (const auto &item : items)
        {
            ImGui::SetCursorPos(ImVec2(0, 0));
            std::string imageName;

            if (item.stealable && !item.stolen)
            {
                imageName = item.name + "Glow.png";
            }
            else if (!item.stealable)
            {
                imageName = item.name + ".png";
            }
            else if (item.stolen)
            {
                continue;
            }

            auto img = loadedImages[imageName];
            ImGui::Image(reinterpret_cast<ImTextureID>(img.texture), viewportSize); // Example size: 100x100
        }

        ImGui::SetCursorPos(ImVec2(0, 0));
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
        ImGui::Text("KnapSack");
        ImGui::PopFont();

        ImGui::Spacing();

        if (!looted)
        {

            if (ImGui::Button("Shuffle Items"))
            {
                PopulateStealableItems();
            }
        }

        if (!looted && !stealableItems.empty())
        {
            if (ImGui::Button("Steal!"))
            {
                auto dp = knapsack01(capacity, stealableItems);
                int value = dp[stealableItemsCount][capacity];
                markStolenItems(capacity, stealableItems, dp);
                std::cout << "Max value: " << value << std::endl;

                for (const auto &item : stealableItems)
                {
                    if (item->stolen)
                    {
                        std::cout << "Stolen: " << item->name << std::endl;
                    }
                }
                looted = true;
            }
        }

        if (looted)
        {
            if (ImGui::Button("Reset"))
            {
                looted = false;
                PopulateStealableItems();
            }
        }

        if (!looted)
        {

            ImGui::PushItemWidth(viewportSize.x * 0.08f);
            ImGui::Text("Capacity");
            ImGui::SliderInt("##Capacity", &capacity, 2, maxCapacity);
            ImGui::Text("Items to Steal");
            if (ImGui::SliderInt("##ItemsToSteal", &stealableItemsCount, 1, maxStealableItems))
            {
                PopulateStealableItems();
            }
            ImGui::PopItemWidth();
        }

        if (looted)
        {
            ImGui::SetCursorPos(ImVec2(viewportSize.x - 200, 50));
            ImGui::BeginChild("Stolen Items", ImVec2(180, viewportSize.y - 100), true);

            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
            ImGui::Text("Stolen Items:");
            ImGui::PopFont();
            ImGui::Separator();

            int usedCapacity = 0;
            int totalValue = 0;

            for (const auto &item : stealableItems)
            {
                if (item->stolen)
                {
                    usedCapacity += item->weight;
                    totalValue += item->value;
                    ImGui::Text("%s", item->name.c_str());
                    ImGui::Text("Weight: %d, Value: %d", item->weight, item->value);
                    ImGui::Separator();
                }
            }

            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
            ImGui::Text("Items left behind:");
            ImGui::PopFont();
            ImGui::Separator();

            for (const auto &item : stealableItems)
            {
                if (!item->stolen)
                {
                    ImGui::Text("%s", item->name.c_str());
                    ImGui::Text("Weight: %d, Value: %d", item->weight, item->value);
                    ImGui::Separator();
                }
            }

            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
            ImGui::Text("Backpack Capacity: \n %d / %d", usedCapacity, capacity);
            ImGui::Text("Total Value: %d", totalValue);
            ImGui::PopFont();

            ImGui::EndChild();
        }

        ImGui::End();
        ImGui::PopStyleColor();
    }
}