
#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Item
{
    std::string name;
    int value;
    int weight;
    bool stealable = false;
    bool stolen = false;
};

std::vector<std::vector<int>> knapsack01(int capacity, std::vector<Item *> items);

#endif // KNAPSACK_H