#include <iostream>
#include <vector>

bool isSubsetSum(const std::vector<int>& set, int sum); // Declaracion

int main() {
    std::vector<int> set = {3, 34, 4, 12, 5, 2};
    int sum = 9;

    if (isSubsetSum(set, sum))
        std::cout << "Existe un subconjunto con la suma dada\n";
    else
        std::cout << "No existe subconjunto con la suma dada\n";

    return 0;
}
