#include <iostream>
#include "TspMatrix.h"
#include "PeaUtils.h"
#include "GeneticAlgorithm.h"
#include "Menu.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    //FILENAME - SECONDS - POPULATION - METHOD
    if (argc > 1) {
        std::string fileName = argv[1];
        long seconds = std::stol(argv[2]);
        int population = std::stoi(argv[3]);
        std::string method = argv[4];

        auto matrix = PeaUtils::readMatrixFromXmlFile(fileName);
        GeneticAlgorithm::solve(matrix, seconds, population, method, 0.8, 0.01);
    } else {
        Menu().start();
    }
}
