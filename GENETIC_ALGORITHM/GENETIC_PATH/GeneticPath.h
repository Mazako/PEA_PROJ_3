#ifndef PEA_PROJ_3_GENETICPATH_H
#define PEA_PROJ_3_GENETICPATH_H
#include <vector>

class GeneticPath
{
    int n;
    std::vector<int> vec;
    long long cost;

public:
    GeneticPath(int n, std::vector<int> vec, long long int cost);

    [[nodiscard]] std::vector<int> getArray() const;

    [[nodiscard]] unsigned long long int getCost() const;

    GeneticPath copy();

    void setCost(long long int cost);

    [[nodiscard]] int getN() const;
};

#endif // PEA_PROJ_3_GENETICPATH_H
