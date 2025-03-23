#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>
#include "imgui.h"
#include "node.h"

class Graph
{
public:
    Graph();
    // Add a node to the graph
    void addNode();

    // Remove a node and its edges
    void removeNode(int nodeID);

    // Add an edge (always undirected)
    void addEdge(int from, int to);

    // Print the adjacency list
    // void printGraph() const;

    // Get neighbors of a node
    // const std::vector<int> &getNeighbors(int nodeID) const;

    std::unordered_map<int, Node> &getAdjacencyList();

    int getIdCount() const;

    void greedyColoring();

    void resetGraph();

private:
    std::unordered_map<int, Node> adjacencyList;
    std::unordered_map<std::string, ImVec4> colors;
    int idCount = 0;
};

#endif // GRAPH_H