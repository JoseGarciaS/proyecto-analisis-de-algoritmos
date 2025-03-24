#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "knapsack.h"

// Mochila 0/1: máximo valor sin fracciones
std::vector<std::vector<int>> knapsack01(int capacity, std::vector<Item *> items)
{
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        for (int w = 0; w <= capacity; ++w)
        {
            if (items[i - 1]->weight <= w)
            {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - items[i - 1]->weight] + items[i - 1]->value);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp;
}
