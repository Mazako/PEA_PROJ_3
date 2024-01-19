#include <unordered_set>
#include <iostream>
#include "GeneticAlgorithm.h"
#include "PeaUtils.h"

// method: OX, PMX
ShortestPathResults *GeneticAlgorithm::solve(TspMatrix *matrix, long timeInSeconds, int populationSize,
                                             std::string method) {
    using std::cout;
    using std::endl;
    std::vector<std::string> logs;

    auto pathComparator = [](GeneticPath* a, GeneticPath* b){
        return a->getCost() < b->getCost();
    };

    auto invertedPathComparator = [](GeneticPath* a, GeneticPath* b){
        return a->getCost() > b->getCost();
    };

    double mutationFactor = 0.01;
    double crossingFactor = 0.8;
    double parentsFactor = 0.75;
    double mutationPopulationFactor = 0.125;

    int parentsSize = populationSize * parentsFactor;
    int mutationCount = populationSize * mutationPopulationFactor;

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

    auto start = std::chrono::high_resolution_clock::now();
    bool timeLimit = false;
    while (!timeLimit) {
        auto parents = rankBasedSelection(population, matrix, parentsSize);
        std::vector<GeneticPath*> changedElements;
        if (PeaUtils::randomFormalDouble() < mutationFactor) {
            for (int i = 0; i < mutationCount; i++) {
                mutate(parents, matrix);
            }
        }

        int crossingNumber = (parentsSize * crossingFactor);
        for (int i = 0; i < crossingNumber; i++) {
            auto pair = PeaUtils::randomTwoInt(parentsSize);
            while ((*crossed[pair.first] && *crossed[pair.second])) {
                pair = PeaUtils::randomTwoInt(parentsSize);
            }
            auto p1 = parents[pair.first];
            auto p2 = parents[pair.second];
            GeneticPath* geneticPath;
            if (method == "OX") {
                geneticPath = orderCrossover(p1, p2, matrix);
            } else if (method == "PMX") {
                geneticPath = partiallyMatchedCrossover(p1, p2, matrix);
            } else {
                throw std::invalid_argument("Unknown crossing method");
            }
            changedElements.push_back(geneticPath);
        }

        std::sort(changedElements.begin(), changedElements.end(), invertedPathComparator);
        std::unordered_set<long long> similarCosts;

        while (parents.size() < populationSize && !changedElements.empty()) {
            auto best = changedElements.back();
            changedElements.pop_back();
            if (!similarCosts.count(best->getCost())) {
                parents.push_back(best->copy());
                similarCosts.insert(best->getCost());
            }
            delete best;
        }

        while (parents.size() < populationSize) {
            int* path = PeaUtils::generateRandomPath(matrix->getN());
            parents.push_back(new GeneticPath(matrix->getN(), path, matrix->calculateCost(path)));
        }

        std::sort(parents.begin(), parents.end(), pathComparator);

        if (parents[0]->getCost() < bestKnownSolution->getCost()) {
            delete bestKnownSolution;
            bestKnownSolution = parents[0]->copy();
//            cout << "HIT! " << bestKnownSolution->getCost() << endl;

            std::string log;
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start).count();
            log.append(std::to_string(elapsed)).append(";").append(std::to_string(bestKnownSolution->getCost()));
            logs.push_back(log);
        }

        for (int i = 0; i < populationSize; i++) {
            delete population[i];
        }

        for (int i = 0; i < changedElements.size(); i++) {
            delete changedElements[i];
        }

        for (int i = 0; i < parentsSize; i++) {
            for (int j = 0; j < parentsSize; j++) {
                crossed[i][j] = false;
            }
        }

        population = parents;
        auto current = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(current - start).count() >= timeInSeconds) {
            timeLimit = true;
        }
    }

    std::string suffix = method + "_" + std::to_string(populationSize);

    auto path = PeaUtils::saveResultsToFile(matrix->getN(), bestKnownSolution->getArray(), matrix->getName(), suffix);
    PeaUtils::saveLogsToFile(logs, "PATH_" + suffix, matrix->getName());
    return new ShortestPathResults(bestKnownSolution->getCost(), matrix->getN(), bestKnownSolution->getArray(),
                                   timeInSeconds, true, path);

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

void GeneticAlgorithm::mutate(const std::vector<GeneticPath *>& parents, TspMatrix *matrix) {
    int parentIndex = PeaUtils::randomInt(parents.size());
    auto selectedParent = parents[parentIndex];

    auto selected = PeaUtils::randomTwoInt(matrix->getN());
    PeaUtils::swap(selected.first, selected.second, selectedParent->getArray());
    selectedParent->setCost(matrix->calculateCost(selectedParent->getArray()));
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

GeneticPath *
GeneticAlgorithm::partiallyMatchedCrossover(GeneticPath *parent1, GeneticPath *parent2, TspMatrix *matrix) {
    int n = parent1->getN();
    int* newPath = new int [n];
    std::unordered_map<int, int> map;
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
    for (int i = a; i <= b; i++) {
        newPath[i] = parent1->getArray()[i];
        beenSet.insert(parent1->getArray()[i]);
        map[parent1->getArray()[i]] = parent2->getArray()[i];
    }

    for (int i = 0; i < n; i++) {
        if (i >= a && i <= b) {
            continue;
        }

        int element = parent2->getArray()[i];

        while (beenSet.count(element)) {
            element = map[element];
        }

        newPath[i] = element;
        beenSet.insert(element);

    }

    return new GeneticPath(n, newPath, matrix->calculateCost(newPath));


}
