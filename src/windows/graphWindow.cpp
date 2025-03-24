#include "windowRenderer.h"
#include "imgui.h"
#include "graph.h"
#include <algorithm>
#include <iostream>

using namespace std;

namespace graphWindow
{
    enum State
    {
        MovingNode,
        DeletingNode,
        AddingEdge,
        RunningAlgorithm
    };

    enum Selection
    {
        Single,
        Pair
    };

    static Graph graph;

    static int selectedNode1 = -1;
    static int selectedNode2 = -1;
    static int selectionMode = Selection::Single;
    static int currentState = State::MovingNode;

    void singleSelection(int nodeID)
    {
        selectedNode1 = (selectedNode1 == nodeID) ? -1 : nodeID;
    }

    void pairSelection(int nodeID)
    {

        if (selectedNode1 == -1)
        {
            selectedNode1 = nodeID;
        }
        else if (selectedNode2 == -1 && nodeID != selectedNode1)
        {
            selectedNode2 = nodeID;
        }
        else
        {
            selectedNode1 = -1;
        }
    }

    bool findNeighbor(int nodeID, const std::vector<int> &neighbors)
    {
        return std::find(neighbors.begin(), neighbors.end(), nodeID) != neighbors.end();
    }

    void resetSelection()
    {
        selectedNode1 = -1;
        selectedNode2 = -1;
    }

    void Render()
    {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // Set text color to black

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // RGBA: White

        ImGui::Begin("graph", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
        ImGui::Text("Graph Coloring");
        ImGui::PopFont();

        ImGui::Spacing();

        auto buttonStyle = [](bool isActive)
        {
            if (isActive)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered)); // Default ImGui hovered color
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_Button)); // Default ImGui color
            }
        };

        buttonStyle(currentState == State::MovingNode);
        if (ImGui::Button("Move Node"))
        {
            resetSelection();
            currentState = State::MovingNode;
            selectionMode = Selection::Single;
        }
        ImGui::PopStyleColor();

        buttonStyle(currentState == State::DeletingNode);
        if (ImGui::Button("Remove Node"))
        {
            resetSelection();
            currentState = State::DeletingNode;
            selectionMode = Selection::Single;
        }
        ImGui::PopStyleColor();

        buttonStyle(currentState == State::AddingEdge);
        if (ImGui::Button("Add Edge"))
        {
            resetSelection();
            currentState = State::AddingEdge;
            selectionMode = Selection::Pair;
        }
        ImGui::PopStyleColor();

        buttonStyle(currentState == State::RunningAlgorithm);
        if (ImGui::Button("Color Graph"))
        {
            currentState = State::RunningAlgorithm;

            if (!graph.getAdjacencyList().empty())
            {
                graph.greedyColoring();
            }
        }
        ImGui::PopStyleColor();

        buttonStyle(false); // Reset button is not state-dependent
        if (ImGui::Button("Reset"))
        {
            graph.resetGraph();
            currentState = State::MovingNode;
        }
        ImGui::PopStyleColor();

        buttonStyle(false); // Add Node button is not state-dependent
        if (ImGui::Button("Add Node"))
        {
            graph.addNode();
            selectionMode = Selection::Single;
            currentState = State::MovingNode;
            selectedNode1 = graph.getIdCount();
        }
        ImGui::PopStyleColor();

        static ImVec2 buttonSize = ImVec2(80, 80);

        // Iterate through the graph's nodes and create a button for each
        auto &adjacencyList = graph.getAdjacencyList();
        ImDrawList *drawList = ImGui::GetWindowDrawList(); // Use the window's draw list
        ImVec2 mousePos = ImGui::GetMousePos();

        // Draw lines between nodes
        for (auto &[id, node] : adjacencyList)
        {

            ImVec2 nodePos = node.getPosition();
            ImVec2 start = ImVec2(nodePos.x + buttonSize.x / 2, nodePos.y + buttonSize.y / 2);

            for (const auto &neighbor : node.getNeighbors())
            {
                ImVec2 neighborPos = adjacencyList[neighbor].getPosition();
                ImVec2 end = ImVec2(neighborPos.x + buttonSize.x / 2, neighborPos.y + buttonSize.y / 2);
                drawList->AddLine(start, end, IM_COL32(0, 0, 0, 255), 2.0f);
            }
        }

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 40.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);                      // Border size
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.9f, 0.9f, 1.0f)); // Slightly darker when hovered
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));  // Even darker when clicked

        // Render nodes
        for (auto &[id, node] : adjacencyList)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, node.getColor().second); // White background

            // Set border color: green for selected nodes, black otherwise
            if (id == selectedNode1 || id == selectedNode2)
            {
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // Green border
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // Black border
            }

            std::string buttonLabel = to_string(id);
            ImGui::SetCursorScreenPos(node.getPosition());

            if (currentState == State::MovingNode && selectedNode1 == id)
            {
                ImVec2 buttonPos = ImVec2(mousePos.x - buttonSize.x / 2, mousePos.y - buttonSize.y / 2);
                node.setPosition(buttonPos);
                ImGui::SetCursorScreenPos(buttonPos);
            }

            if (ImGui::Button(buttonLabel.c_str(), buttonSize))
            {
                if (selectionMode == Selection::Single)
                {
                    singleSelection(id);
                }
                else if (selectionMode == Selection::Pair)
                {
                    pairSelection(id);
                }
            }

            ImGui::PopStyleColor(2); // Pop border and button colors

            ImGui::Spacing();
        }

        // Restore styles
        ImGui::PopStyleColor(2); // Pop hovered, active, and default button colors
        ImGui::PopStyleVar(2);

        switch (currentState)
        {
        case State::DeletingNode:

            if (selectedNode1 != -1)
            {
                graph.removeNode(selectedNode1);
                resetSelection();
            }
            break;

        case State::AddingEdge:
            if (selectedNode1 != -1 && selectedNode2 != -1 && !findNeighbor(selectedNode2, adjacencyList[selectedNode1].getNeighbors()))
            {
                graph.addEdge(selectedNode1, selectedNode2);
                resetSelection();
            }
            else if (selectedNode1 != -1 && selectedNode2 != -1)
            {
                resetSelection();
            }

            break;

        default:
            break;
        }

        // Pop the white background color
        ImGui::PopStyleColor(2);
        ImGui::End();
    }
}