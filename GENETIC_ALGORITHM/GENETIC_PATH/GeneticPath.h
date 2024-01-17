#ifndef PEA_PROJ_3_GENETICPATH_H
#define PEA_PROJ_3_GENETICPATH_H


class GeneticPath {
    int n;
    int* array;
    long long cost;
public:
    GeneticPath(int n, int *array, long long int cost);
    ~GeneticPath();

    int *getArray() const;

    long long int getCost() const;

    void setCost(long long int cost);

    GeneticPath* copy();

    int getN() const;
};


#endif //PEA_PROJ_3_GENETICPATH_H
