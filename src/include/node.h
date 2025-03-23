#ifndef NODE_H
#define NODE_H

#include <vector>
#include <imgui.h>
#include <utility>
#include <string>

class Node
{
public:
    Node();
    void addNeighbor(int neighbor);
    void removeNeighbor(int neighbor);
    const std::vector<int> &getNeighbors() const;
    int getId() const;
    ImVec2 getPosition() const;
    void setPosition(ImVec2 pos);
    void setColor(std::string, ImVec4);
    std::pair<std::string, ImVec4> getColor() const;

private:
    std::vector<int> neighbors;
    ImVec2 position;
    std::pair<std::string, ImVec4> color;
};

#endif