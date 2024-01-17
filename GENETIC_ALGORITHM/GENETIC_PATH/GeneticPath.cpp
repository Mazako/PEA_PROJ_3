#include "GeneticPath.h"
#include "PeaUtils.h"

GeneticPath::GeneticPath(int n, int *array, long long int cost) :n(n), array(array), cost(cost) {}

GeneticPath::~GeneticPath() {
    delete[] array;
}

int *GeneticPath::getArray() const {
    return array;
}

long long int GeneticPath::getCost() const {
    return cost;
}

GeneticPath *GeneticPath::copy() {
    return new GeneticPath(n, PeaUtils::copyArray(n, array), cost);
}

void GeneticPath::setCost(long long int cost) {
    GeneticPath::cost = cost;
}

int GeneticPath::getN() const {
    return n;
}
