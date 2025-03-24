#include <iostream>
#include <vector>
#include <algorithm>

struct Item {
    double value;
    double weight;
};

bool compare(Item a, Item b) {
    return (a.value / a.weight) > (b.value / b.weight);
}

double fractionalKnapsack(double capacity, std::vector<Item> items) {
    std::sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;

    for (const auto& item : items) {
        if (capacity >= item.weight) {
            capacity -= item.weight;
            totalValue += item.value;
        } else {
            totalValue += item.value * (capacity / item.weight);
            break;
        }
    }

    return totalValue;
}

