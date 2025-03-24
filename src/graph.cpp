#include "graph.h"
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <stack>
#include <chrono>

using namespace std;

Graph::Graph()
{
    idCount = 0;

    colors = {
        {"White", ImVec4(1.0f, 1.0f, 1.0f, 1.0f)},
        //{"Black", ImVec4(0.0f, 0.0f, 0.0f, 1.0f)},
        {"Red", ImVec4(1.0f, 0.0f, 0.0f, 1.0f)},
        //{"Green", ImVec4(0.0f, 1.0f, 0.0f, 1.0f)},
        {"Blue", ImVec4(0.0f, 0.0f, 1.0f, 1.0f)}};
}

// Add a node to the graph
void Graph::addNode()
{
    idCount++;
    adjacencyList[idCount] = Node();
}

// Remove a node and its edges
void Graph::removeNode(int nodeID)
{
    // Check if the node exists
    if (adjacencyList.find(nodeID) != adjacencyList.end())
    {
        // Remove the node from all neighbor lists

        for (const auto &neighbor : adjacencyList[nodeID].getNeighbors())
        {
            adjacencyList[neighbor].removeNeighbor(nodeID);
        }

        // Remove the node from the adjacency list
        adjacencyList.erase(nodeID);
    }
}

// Add an undirected edge (always bidirectional)
void Graph::addEdge(int from, int to)
{
    adjacencyList[from].addNeighbor(to);
    adjacencyList[to].addNeighbor(from);
}

std::unordered_map<int, Node> &Graph::getAdjacencyList()
{
    return adjacencyList;
}

int Graph::getIdCount() const
{
    return idCount;
}

void Graph::greedyColoring()
{
    auto start = std::chrono::high_resolution_clock::now();

    unordered_set<int> processedNodes;
    stack<int> visitedNodes;

    int currentNode = 1;
    visitedNodes.push(currentNode);

    while (!visitedNodes.empty())
    {
        currentNode = visitedNodes.top();
        visitedNodes.pop();

        if (processedNodes.find(currentNode) != processedNodes.end())
        {
            continue;
        }

        unordered_set<string> neighborsColors;
        for (auto neighbor : adjacencyList[currentNode].getNeighbors())
        {
            neighborsColors.insert(adjacencyList[neighbor].getColor().first);
        }

        for (auto &[colorName, color] : colors)
        {
            if (neighborsColors.find(colorName) == neighborsColors.end())
            {
                adjacencyList[currentNode].setColor(colorName, color);
                break;
            }
        }

        processedNodes.insert(currentNode);

        for (auto neighbor : adjacencyList[currentNode].getNeighbors())
        {
            if (processedNodes.find(neighbor) == processedNodes.end())
            {
                visitedNodes.push(neighbor);
            }
        }
    }
}

void Graph::resetGraph()
{
    adjacencyList.clear();
    idCount = 0;
}