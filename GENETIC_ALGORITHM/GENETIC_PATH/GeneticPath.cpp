#include "GeneticPath.h"

#include "PeaUtils.h"
#include <utility>

GeneticPath::GeneticPath(const int n, std::vector<int> vec,
                         const long long int cost)
    : n(n), vec(std::move(vec)), cost(cost) {}

std::vector<int> GeneticPath::getArray() const { return vec; }

unsigned long long int GeneticPath::getCost() const { return cost; }

GeneticPath GeneticPath::copy() {
  return {n, std::vector(vec), cost};
}

void GeneticPath::setCost(const long long int cost) { this->cost = cost; }

int GeneticPath::getN() const { return n; }
