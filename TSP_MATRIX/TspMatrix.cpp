#include "TspMatrix.h"
#include <iostream>
#include <utility>
#include <vector>

TspMatrix::TspMatrix(const int n,
                     std::unique_ptr<std::unique_ptr<int[]>[]> matrix)
    : n(n), matrix(std::move(matrix)), name("NONE")
{
}

TspMatrix::TspMatrix(const int n,
                     std::unique_ptr<std::unique_ptr<int[]>[]> matrix,
                     std::string name)
    : n(n), matrix(std::move(matrix)), name(std::move(name))
{
}

int TspMatrix::getN() const { return n; }

std::string TspMatrix::toString() const
{
    std::string mat;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat.append(std::to_string(matrix[i][j])).append(" ");
        }
        mat.append("\n");
    }
    return mat;
}

long long int TspMatrix::calculateCost(const std::vector<int>& path) const
{
    const int first = path[0];
    int v1 = path[0];
    int v2;
    long long int totalCost = 0;
    for (int i = 1; i < this->n; i++)
    {
        v2 = path[i];
        totalCost += matrix[v1][v2];
        v1 = v2;
    }
    totalCost += matrix[v2][first];
    return totalCost;
}

unsigned long long
TspMatrix::calculateCostThatExcludeZero(const std::vector<int>& path) const
{
    unsigned long long totalCost = matrix[0][path[0]];
    totalCost += matrix[path[n - 2]][0];
    int v1 = path[0];
    for (int i = 1; i < n - 1; i++)
    {
        const int v2 = path[i];
        totalCost += matrix[v1][v2];
        v1 = v2;
    }
    return totalCost;
}

std::string TspMatrix::getName() const { return name; }
