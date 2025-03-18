#ifndef PEA_PROJ_3_MENU_H
#define PEA_PROJ_3_MENU_H

#include "TspMatrix.h"
#include <string>

#include <optional>

class Menu
{
    double mutationFactor = 0.01;
    double crossingFactor = 0.8;
    std::string crossingMode = "OX";
    std::optional<TspMatrix> matrix;
    long maxSecondsTime = 120;
    int populationSize = 200;

    void setMutationFactor();
    void setCrossingFactor();
    void readMatrix();
    void setMaxTime();
    void setPopulationSize();
    void performGA();
    void readResultFileAndCalcPath();
    void changeCrossingMode();

public:
    void start();
};


#endif //PEA_PROJ_3_MENU_H
