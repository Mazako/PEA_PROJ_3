#ifndef PEA_PROJ_1_TSPMATRIX_H
#define PEA_PROJ_1_TSPMATRIX_H

#include <string>

class TspMatrix {
    int n;
    int** matrix;
    std::string name;

public:
    TspMatrix(int n, int** matrix, std::string name);

    TspMatrix(int n, int** matrix);

    ~TspMatrix();

    int getN() const;

    int** getMatrices() const;

    std::string getName() const;

    long long int calculateCost(const int* path);

    unsigned long long int calculateCostThatExcludeZero(const int* path);
};


#endif //PEA_PROJ_1_TSPMATRIX_H
