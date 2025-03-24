#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <iostream>
#include <vector>
#include <algorithm>

struct Item
{
    double value;
    double weight;
};

bool compare(Item a, Item b);

double fractionalKnapsack(double capacity, std::vector<Item> items);

#endif // KNAPSACK_H
