#include <iostream>
#include "TspMatrix.h"
#include "PeaUtils.h"
#include "GeneticAlgorithm.h"
using std::cout;
using std::endl;

void oxTest();

void pmxTest();

int main(int argc, char *argv[]) {
    //FILENAME - SECONDS - POPULATION - METHOD
    if (argc > 1) {
        std::string fileName = argv[1];
        long seconds = std::stol(argv[2]);
        int population = std::stoi(argv[3]);
        std::string method = argv[4];

        auto matrix = PeaUtils::readMatrixFromXmlFile(fileName);
        GeneticAlgorithm::solve(matrix, seconds, population, method);
    }

    auto matrix = PeaUtils::readMatrixFromXmlFile("../RESOURCES/ftv170.xml");
    GeneticAlgorithm::solve(matrix, 240, 200, "PMX");
}

void oxTest() {
    auto matrix = PeaUtils::generateRandomTSPInstance(9);
    int arr1[] = {1, 2, 3, 4, 5, 6, 7,8, 9};
    int arr2[] = {9, 3, 7, 8, 2, 6, 5, 1, 4};
    for (int i = 0; i < 9; i++) {
        arr1[i]--;
        arr2[i]--;
    }
    auto parent1 = new GeneticPath(9, arr1, 0);
    auto parent2 = new GeneticPath(9, arr2, 0);
    auto result = GeneticAlgorithm::orderCrossover(parent1, parent2, matrix);
    cout << PeaUtils::arrayToString(9, result->getArray());

}

void pmxTest() {
    auto matrix = PeaUtils::generateRandomTSPInstance(9);
    int arr1[] = {1, 2, 3, 4, 5, 6, 7,8, 9};
    int arr2[] = {9, 3, 7, 8, 2, 6, 5, 1, 4};
    for (int i = 0; i < 9; i++) {
        arr1[i]--;
        arr2[i]--;
    }
    auto parent1 = new GeneticPath(9, arr1, 0);
    auto parent2 = new GeneticPath(9, arr2, 0);
    auto result = GeneticAlgorithm::partiallyMatchedCrossover(parent1, parent2, matrix);
    cout << PeaUtils::arrayToString(9, result->getArray());

}