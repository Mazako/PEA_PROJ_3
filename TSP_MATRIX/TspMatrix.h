#ifndef PEA_PROJ_1_TSPMATRIX_H
#define PEA_PROJ_1_TSPMATRIX_H

#include <memory>
#include <string>
#include <vector>

class TspMatrix
{
    int n;
    std::unique_ptr<std::unique_ptr<int[]>[]> matrix;
    std::string name;
public:
    TspMatrix(int n, std::unique_ptr<std::unique_ptr<int[]>[]> matrix, std::string name);

    TspMatrix(int n, std::unique_ptr<std::unique_ptr<int[]>[]> matrix);

    [[nodiscard]] int getN() const;

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] long long int calculateCost(const std::vector<int> &path) const;

    [[nodiscard]] unsigned long long int calculateCostThatExcludeZero(const std::vector<int> &path) const;
};


#endif //PEA_PROJ_1_TSPMATRIX_H
