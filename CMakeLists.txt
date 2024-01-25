cmake_minimum_required(VERSION 3.25.2)
project(PEA_PROJ_3)

set(CMAKE_CXX_STANDARD 17)

include_directories(PEA_UTILS
        SHORTEST_PATH_RESULTS
        GENETIC_ALGORITHM
        GENETIC_ALGORITHM/GENETIC_PATH
        TSP_MATRIX
        MENU
        pugixml-1.14/src)


add_executable(PEA_PROJ_3 main.cpp
        PEA_UTILS/PeaUtils.cpp
        PEA_UTILS/PeaUtils.h
        SHORTEST_PATH_RESULTS/ShortestPathResults.h
        SHORTEST_PATH_RESULTS/ShortestPathResults.cpp
        TSP_MATRIX/TspMatrix.cpp
        TSP_MATRIX/TspMatrix.h
        pugixml-1.14/src/pugixml.cpp
        GENETIC_ALGORITHM/GeneticAlgorithm.cpp
        GENETIC_ALGORITHM/GeneticAlgorithm.h
        GENETIC_ALGORITHM/GENETIC_PATH/GeneticPath.cpp
        GENETIC_ALGORITHM/GENETIC_PATH/GeneticPath.h MENU/Menu.cpp MENU/Menu.h)