#include <unordered_set>
#include <iostream>
#include "GeneticAlgorithm.h"
#include "PeaUtils.h"

ShortestPathResults *GeneticAlgorithm::solve(TspMatrix *matrix, long timeInSeconds) {
    using std::cout;
    using std::endl;

    auto pathComparator = [](GeneticPath* a, GeneticPath* b){
        return a->getCost() < b->getCost();
    };
    double mutationFactor = 0.01;
    double crossingFactor = 0.8;
    int populationSize = 500;
    int parentsSize = 250;

    bool** crossed = new bool *[parentsSize];
    for (int i = 0; i < parentsSize; i++) {
        crossed[i] = new bool [parentsSize];
        for (int j = 0; j < parentsSize; j++) {
            crossed[i][j] = false;
        }
    }

    auto population = calculateInitialPopulation(matrix, populationSize);
    std::sort(population.begin(), population.end(), pathComparator);
    auto bestKnownSolution = population[0]->copy();

    int generation = 0;

    while (true) {
        auto parents = rankBasedSelection(population, matrix, parentsSize);
        std::vector<GeneticPath*> changedElements;
        if (PeaUtils::randomFormalDouble() < mutationFactor) {
            changedElements.push_back(mutate(parents, matrix));
        }

        int crossingNumber = (parentsSize * crossingFactor) / 2;
        for (int i = 0; i < crossingNumber; i++) {
            auto pair = PeaUtils::randomTwoInt(parentsSize);
            while ((*crossed[pair.first] && *crossed[pair.second]) || (*crossed[pair.second] && *crossed[pair.first])) {
                pair = PeaUtils::randomTwoInt(parentsSize);
            }
            auto p1 = parents[pair.first];
            auto p2 = parents[pair.second];
            changedElements.push_back(orderCrossover(p1, p2, matrix));
            changedElements.push_back(orderCrossover(p2,p1, matrix));
        }

        population.insert(population.begin(), changedElements.begin(), changedElements.end());
        std::sort(population.begin(), population.end(), pathComparator);
        while (population.size() > populationSize) {
            auto last =  population.back();
            population.pop_back();
            delete last;
        }

        if (population[0]->getCost() < bestKnownSolution->getCost()) {
            delete bestKnownSolution;
            bestKnownSolution = population[0]->copy();
            cout << "HIT! " << bestKnownSolution->getCost() << endl;
            if (bestKnownSolution->getCost() < 6000) {
                cout << "\n";
            }
        }

        for (int i = 0; i < parents.size(); i++) {
            delete parents[i];
        }

        for (int i = 0; i < parentsSize; i++) {
            for (int j = 0; j < parentsSize; j++) {
                crossed[i][j] = false;
            }
        }
        generation++;

    }

}

std::vector<GeneticPath *> GeneticAlgorithm::rankBasedSelection(std::vector<GeneticPath *> &population, TspMatrix *matrix, int size) {
    int populationSize = population.size();
    double runningCdf = 1.0;
    double selectionPressure = 1.5;
    std::vector<double> cdf;
    std::vector<double> probabilities;
    std::vector<GeneticPath*> parents;

    for (int i = 0; i < populationSize; i++) {
        int rank = populationSize - i - 1;
        double p = (double)((2 - selectionPressure) / populationSize) + (double)((2 * rank * (selectionPressure - 1)) / (populationSize * (populationSize - 1)));
        probabilities.push_back(p);
        cdf.push_back(runningCdf);
        runningCdf -= p;
    }

    for (int i = 0; i < size; i++) {
        double rand = PeaUtils::randomFormalDouble();
        int j = populationSize - 1;
        int lastGoodKnown = j;
        while (cdf[j] < rand && j != -1) {
            if (cdf[j] != -1) {
                lastGoodKnown = j;
            }
            j--;
        }
        if (j == -1) {
            parents.push_back(population[lastGoodKnown]->copy());
        } else {
            cdf[j] = -1.0;
            parents.push_back(population[j]->copy());
        }
    }

    return parents;
}

std::vector<GeneticPath*> GeneticAlgorithm::calculateInitialPopulation(TspMatrix *matrix, int size) {
    std::vector<GeneticPath*> vector;
    for (int i = 0; i < size; i++) {
        int* path = PeaUtils::generateRandomPath(matrix->getN());
        vector.push_back(new GeneticPath(matrix->getN(), path, matrix->calculateCost(path)));
    }
    return vector;
}

GeneticPath * GeneticAlgorithm::mutate(const std::vector<GeneticPath *>& parents, TspMatrix *matrix) {
    int parentIndex = PeaUtils::randomInt(parents.size());
    auto selectedParent = parents[parentIndex]->copy();

    auto selected = PeaUtils::randomTwoInt(matrix->getN());
    PeaUtils::swap(selected.first, selected.second, selectedParent->getArray());
    selectedParent->setCost(matrix->calculateCost(selectedParent->getArray()));
    return selectedParent;
}

GeneticPath *GeneticAlgorithm::orderCrossover(GeneticPath *parent1, GeneticPath *parent2, TspMatrix *matrix) {
    int n = parent1->getN();
    int* newPath = new int [n];
    std::unordered_set<int> beenSet;

    auto pair = PeaUtils::randomTwoInt(n);
    int a;
    int b;
    if (pair.first > pair.second) {
        a = pair.second;
        b = pair.first;
    } else {
        a = pair.first;
        b = pair.second;
    }
//    a = 3;
//    b = 6;

    for (int i = a; i <= b; i++) {
        newPath[i] = parent1->getArray()[i];
        beenSet.insert(parent1->getArray()[i]);
    }

    int ptr = (b + 1) % n;
    int next = ptr;
    while (next != a) {
        if (!beenSet.count(parent2->getArray()[ptr])) {
            newPath[next] = parent2->getArray()[ptr];
            next = (next + 1) % n;
        }
        ptr = (ptr + 1) % n;
    }

    return new GeneticPath(n, newPath, matrix->calculateCost(newPath));
}
