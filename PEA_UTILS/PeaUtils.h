#ifndef PEA_PROJ_1_PEAUTILS_H
#define PEA_PROJ_1_PEAUTILS_H

#include "ShortestPathResults.h"
#include "TspMatrix.h"
#include <chrono>
#include <functional>
#include <string>

class PeaUtils
{
    PeaUtils();

public:
    static void swap(int i, int j, int* array);

    static int* copyArray(int n, const int* array);

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

    static TspMatrix readMatrixFromFile(const std::string& filename);

    static TspMatrix readMatrixFromAtspFile(const std::string& filename);

    static TspMatrix readMatrixFromXmlFile(const std::string& filename);

    static int factorial(int n);

    static long double calculateAvgTime(int resultCount,
                                        ShortestPathResults** results);

    static long double calculateStandardDeviation(int resultCount,
                                                  ShortestPathResults** results,
                                                  long double avg);

    static long double calculateSuccessRate(int resultCount,
                                            ShortestPathResults** results);

    static std::vector<int> subtractVectors(std::vector<int>& v1,
                                            std::vector<int>& v2);

    static double calculateAverage(const std::vector<long long int>& vec);

    static int** generateEmptyMatrix(int n);

    static std::string saveResultsToFile(int n, const std::vector<int>& path,
                                         const std::string& matrixName,
                                         const std::string& methodPrefix);

    static std::string
    PeaUtils::generateRandomFileName(const std::string& method,
                                     const std::string& matrixName);

    static void saveLogsToFile(const std::vector<std::string>& logs,
                               const std::string& method,
                               const std::string& matrix);

    static long long readPathAndCalculateCost(const TspMatrix& matrix,
                                              const std::string& filename);

    static std::vector<int> generateRandomPath(const int N);
};

#endif // PEA_PROJ_1_PEAUTILS_H
