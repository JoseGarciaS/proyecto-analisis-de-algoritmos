#include <iostream>
#include <vector>
#include "knapsack.cpp"

int main() {
    std::vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};
    double capacity = 50.0;

    double maxValue = fractionalKnapsack(capacity, items);
    std::cout << "Valor maximo en mochila = " << maxValue << std::endl;

    return 0;
}
