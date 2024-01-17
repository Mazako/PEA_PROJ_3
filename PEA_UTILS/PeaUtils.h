#ifndef PEA_PROJ_1_PEAUTILS_H
#define PEA_PROJ_1_PEAUTILS_H

#include <string>
#include <random>
#include <functional>
#include <fstream>
#include <chrono>
#include "TspMatrix.h"
#include "ShortestPathResults.h"

class PeaUtils {
private:
    PeaUtils();

public:
    static void swap(int i, int j, int* array);

    static int* copyArray(int n, const int* array);

    static int** copyMatrix(int n, int** matrix);

    static int minimum(int n, const int* array);

    static int minimumColumn(int n, int** matrix, int column);

    static int* createArrayFromZeroToNMinusOne(int n);

    static int* createArrayFromOneToNMinusOne(int n);

    static std::vector<int> createVectorFromZeroToNMinusOne(int n);

    static int randomInt();

    static int randomInt(int range);

    static double randomFormalDouble();

    static std::pair<int, int> randomTwoInt(int range);

    static TspMatrix* generateRandomTSPInstance(int n);

    static std::string matrixToString(const TspMatrix* tspMatrix);

    static std::string arrayToString(int n, int* arr);

    static TspMatrix* readMatrixFromFile(const std::string& filename);

    static TspMatrix * readMatrixFromAtspFile(const std::string& filename);

    static TspMatrix* readMatrixFromXmlFile(const std::string& filename);

    static int factorial(int n);

    static long double calculateAvgTime(int resultCount, ShortestPathResults** results);

    static long double calculateStandardDeviation(int resultCount, ShortestPathResults** results, long double avg);

    static long double calculateSuccessRate(int resultCount, ShortestPathResults** results);

    static std::vector<int> subtractVectors(std::vector<int>& v1, std::vector<int>& v2);

    static double calculateAverage(const std::vector<long long int> &vec);

    static int** generateEmptyMatrix(int n);

    static std::string saveResultsToFile(int n, int *path, std::string matrixName, std::string methodPrefix);

    static void saveLogsToFile(std::vector<std::string> logs, std::string fileName);

    static long long readPathAndCalculateCost(TspMatrix* matrix, std::string filename);

    static int* generateRandomPath(int N) {
        std::vector<int> path(N);
        for (int i = 0; i < N; ++i) {
            path[i] = i;
        }

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        shuffle(path.begin(), path.end(), std::default_random_engine(seed));

        int* arr = new int[N];
        for (int i = 0; i < N; i++) {
            arr[i] = path[i];
        }
        return arr;
    }
};


#endif //PEA_PROJ_1_PEAUTILS_H
