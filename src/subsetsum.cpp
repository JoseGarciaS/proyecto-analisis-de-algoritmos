#include <iostream>
#include <vector>

std::vector<std::vector<bool>> SubsetSum(const std::vector<int> &set, int sum)
{
    int n = set.size();
    std::vector<std::vector<bool>> subset(n + 1, std::vector<bool>(sum + 1));

    // Si la suma es 0, siempre se puede obtener con subconjunto vacio
    for (int i = 0; i <= n; ++i)
        subset[i][0] = true;

    // Si el subconjunto esta vacio y la suma no es 0, no se puede obtener
    for (int j = 1; j <= sum; ++j)
        subset[0][j] = false;

    // Llenar tabla
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= sum; ++j)
        {
            if (j < set[i - 1])
                subset[i][j] = subset[i - 1][j];
            else
                subset[i][j] = subset[i - 1][j] || subset[i - 1][j - set[i - 1]];
        }
    }

    return subset;
}
