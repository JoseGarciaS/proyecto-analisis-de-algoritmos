#include "node.h"
#include <algorithm>

using namespace std;

Node::Node()
{
    position = ImVec2(0, 0);
    color = {"White", ImVec4(1.0f, 1.0f, 1.0f, 1.0f)};
}

void Node::addNeighbor(int neighbor)
{
    neighbors.push_back(neighbor);
}

void Node::removeNeighbor(int neighbor)
{
    neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), neighbor), neighbors.end());
}

const std::vector<int> &Node::getNeighbors() const
{
    return neighbors;
}

ImVec2 Node::getPosition() const
{
    return position;
}

void Node::setPosition(ImVec2 pos)
{
    position = pos;
}

void Node::setColor(std::string name, ImVec4 col)
{
    color = {name, col};
}

std::pair<std::string, ImVec4> Node::getColor() const
{
    return color;
}