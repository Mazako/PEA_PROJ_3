#include "PeaUtils.h"

#include "pugixml.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <random>

void PeaUtils::swap(int i, int j, int* array)
{
    int tmp = array[j];
    array[j] = array[i];
    array[i] = tmp;
}

int PeaUtils::randomInt() { return randomInt(INT32_MAX); }

int PeaUtils::randomInt(int range)
{
    // RANGE IS EXCLUSIVE
    range--;
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<> distribution(0, range);
    return distribution(rng);
}

double PeaUtils::randomFormalDouble()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<> distr(0.0, 1.0);
    return distr(rng);
}

TspMatrix* PeaUtils::generateRandomTSPInstance(const int n)
{
    auto matrix = std::make_unique<std::unique_ptr<int[]>[]>(n);
    for (int i = 0; i < n; i++)
    {
        matrix[i] = std::make_unique<int[]>(n);
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                matrix[i][j] = -1;
            }
            else
            {
                if (j < i)
                {
                    while (matrix[i][j] == matrix[j][i])
                    {
                        matrix[i][j] = randomInt();
                    }
                }
                matrix[i][j] = randomInt();
            }
        }
    }
    return new TspMatrix(n, std::move(matrix));
}

int* PeaUtils::copyArray(const int n, const int* array)
{
    int* newArr = new int[n];
    for (int i = 0; i < n; i++)
    {
        newArr[i] = array[i];
    }
    return newArr;
}

int* PeaUtils::createArrayFromZeroToNMinusOne(int n)
{
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
    return arr;
}

int* PeaUtils::createArrayFromOneToNMinusOne(int n)
{
    int* arr = new int[n - 1];
    for (int i = 1; i < n; i++)
    {
        arr[i - 1] = i;
    }
    return arr;
}

TspMatrix PeaUtils::readMatrixFromFile(const std::string& filename)
{
    using namespace std;
    string line;
    fstream newFile;
    newFile.open(filename, ios::in);
    int count;
    newFile >> count;
    if (count <= 0)
    {
        throw invalid_argument("Too small length of array");
    }
    auto matrix = std::make_unique<std::unique_ptr<int[]>[]>(count);
    for (int i = 0; i < count; i++)
    {
        matrix[i] = std::make_unique<int[]>(count);
        for (int j = 0; j < count; j++)
        {
            newFile >> matrix[i][j];
            if (i == j)
            {
                matrix[i][j] = -1;
            }
        }
    }
    return {count, std::move(matrix)};
}

TspMatrix PeaUtils::readMatrixFromAtspFile(const std::string& filename)
{
    using namespace std;
    string line;
    fstream newFile;
    newFile.open(filename, ios::in);

    getline(newFile, line);
    stringstream nameStream(line);
    string name;
    nameStream >> name;
    nameStream >> name;

    for (int i = 0; i < 3; i++)
    {
        getline(newFile, line);
    }
    stringstream dimensionStream(line);
    string dimensionStr;
    dimensionStream >> dimensionStr;
    dimensionStream >> dimensionStr;
    int dimension = stoi(dimensionStr);

    for (int i = 0; i < 4; i++)
    {
        getline(newFile, line);
    }
    auto array = std::make_unique<std::unique_ptr<int[]>[]>(dimension);
    for (int i = 0; i < dimension; i++)
    {
        array[i] = std::make_unique<int[]>(dimension);
    }
    stringstream rowBuffer(line);
    string numberBuffer;
    int i = 0;
    int j = 0;
    int counter = 0;
    while (line != "EOF")
    {
        while (rowBuffer >> numberBuffer)
        {
            array[i][j] = stoi(numberBuffer);
            counter++;
            if (counter % dimension == 0)
            {
                i++;
                j = 0;
            }
            else
            {
                j++;
            }
        }
        getline(newFile, line);
        rowBuffer = stringstream(line);
    }
    newFile.close();
    return {dimension, std::move(array), name};
}

int PeaUtils::factorial(int n)
{
    int result = 1;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

long double PeaUtils::calculateAvgTime(int resultCount,
                                       ShortestPathResults** results)
{
    long long totalTime = 0.;
    int successCount = 0;
    for (int i = 0; i < resultCount; i++)
    {
        if (results[i]->isNoTimeCause())
        {
            successCount++;
            totalTime += results[i]->getSecondsTime();
        }
    }

    if (successCount == 0)
    {
        return -1;
    }

    return static_cast<long double>(totalTime) / successCount;
}

int PeaUtils::minimum(int n, const int* array)
{
    int minimum = array[0];
    if (minimum == -1)
    {
        minimum = array[1];
    }
    for (int i = 0; i < n; i++)
    {
        if (array[i] > -1 && array[i] < minimum)
        {
            minimum = array[i];
        }
    }
    return minimum;
}

int PeaUtils::minimumColumn(const int n, int** matrix, const int column)
{
    int minimum = matrix[0][column];
    if (minimum == -1)
    {
        minimum = matrix[1][column];
    }
    for (int i = 1; i < n; i++)
    {
        if (matrix[i][column] > -1 && matrix[i][column] < minimum)
        {
            minimum = matrix[i][column];
        }
    }
    return minimum;
}

std::vector<int> PeaUtils::createVectorFromZeroToNMinusOne(const int n)
{
    std::vector<int> v;
    v.reserve(n);
    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }
    return v;
}

std::vector<int> PeaUtils::subtractVectors(std::vector<int>& v1,
                                           std::vector<int>& v2)
{
    std::vector<int> result;
    for (const auto& item : v1)
    {
        if (std::find(v2.begin(), v2.end(), item) == v2.end())
        {
            result.push_back(item);
        }
    }
    return result;
}

long double PeaUtils::calculateStandardDeviation(const int resultCount,
                                                 ShortestPathResults** results,
                                                 const long double avg)
{
    long double total = .0;
    for (int i = 0; i < resultCount; i++)
    {
        total += std::pow(results[i]->getSecondsTime() - avg, 2);
    }
    total = total / (resultCount - 1);
    return std::sqrt(total);
}

long double PeaUtils::calculateSuccessRate(const int resultCount,
                                           ShortestPathResults** results)
{
    int successes = 0;
    for (int i = 0; i < resultCount; i++)
    {
        if (results[i]->isNoTimeCause())
        {
            successes++;
        }
    }
    return (double)successes / resultCount;
}

double PeaUtils::calculateAverage(const std::vector<long long int>& vec)
{
    if (vec.empty())
        return 0.0;

    double sum = 0.0;
    for (const long long num : vec)
    {
        sum += num;
    }
    return (double)sum / vec.size();
}

int** PeaUtils::generateEmptyMatrix(int n)
{
    int** mat = new int*[n];
    for (int i = 0; i < n; i++)
    {
        mat[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            mat[i][j] = 0;
        }
    }
    return mat;
}

std::string PeaUtils::saveResultsToFile(const int n,
                                        const std::vector<int>& path,
                                        const std::string& matrixName,
                                        const std::string& methodPrefix)
{
    std::string fileName = generateRandomFileName(methodPrefix, matrixName);
    std::fstream fileStream;
    fileStream.open(fileName, std::ios::out);
    fileStream << n << "\n";
    for (int i = 0; i < n; i++)
    {
        fileStream << path[i] << "\n";
    }
    fileStream << path[0] << "\n";
    fileStream.close();
    return fileName;
}

std::string PeaUtils::generateRandomFileName(const std::string& method,
                                             const std::string& matrixName)
{
    std::string fileName;
    fileName.append(method).append("_");
    fileName.append(matrixName);
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    auto parts = std::localtime(&now_c);
    auto year = std::to_string(1900 + parts->tm_year);
    auto month = std::to_string(1 + parts->tm_mon);
    auto day = std::to_string(parts->tm_mday);
    auto hour = std::to_string(parts->tm_hour);
    auto minute = std::to_string(parts->tm_min);
    auto second = std::to_string(parts->tm_sec);
    return fileName.append("_")
                   .append(year)
                   .append("_")
                   .append(month)
                   .append("_")
                   .append(day)
                   .append("_")
                   .append(hour)
                   .append("_")
                   .append(minute)
                   .append("_")
                   .append(second)
                   .append(".txt");
}

void PeaUtils::saveLogsToFile(const std::vector<std::string>& logs,
                              const std::string& method,
                              const std::string& matrix)
{
    const std::string fileName = generateRandomFileName(method, matrix);
    std::fstream is;
    is.open(fileName, std::ios::out);
    for (auto& item : logs)
    {
        is << item << std::endl;
    }
    is.close();
}

TspMatrix PeaUtils::readMatrixFromXmlFile(const std::string& filename)
{
    pugi::xml_document xml;
    if (!xml.load_file(filename.c_str()))
    {
        throw std::invalid_argument("Nie udalo sie wczytac pliku xml");
    }
    const auto mainNode = xml.child("travellingSalesmanProblemInstance");
    const auto nameNode = mainNode.child("name");
    const std::string name = nameNode.child_value();
    const auto graph = mainNode.child("graph");
    int instanceSize = std::distance(graph.begin(), graph.end());
    auto matrix = std::make_unique<std::unique_ptr<int[]>[]>(instanceSize);
    for (int i = 0; i < instanceSize; i++)
    {
        matrix[i] = std::make_unique<int[]>(instanceSize);
    }
    int i = 0;
    for (const auto& vertex : graph.children())
    {
        int j = 0;
        for (const auto& edge : vertex.children())
        {
            const auto strValue = edge.attribute("cost").value();
            const int value = static_cast<int>(std::stod(strValue));
            matrix[i][j] = value;
            j++;
        }
        i++;
    }
    return {instanceSize, std::move(matrix), name};
}

long long PeaUtils::readPathAndCalculateCost(const TspMatrix& matrix,
                                             const std::string& filename)
{
    std::string line;
    std::fstream newFile;
    newFile.open(filename, std::ios::in);
    std::getline(newFile, line);
    int size = std::stoi(line);
    if (size != matrix.getN())
    {
        throw std::invalid_argument("Liczba wierzcholkow niezgodna z instancja");
    }
    auto path = std::vector<int>(matrix.getN());
    for (int i = 0; i < size; i++)
    {
        std::getline(newFile, line);
        path[i] = std::stoi(line);
    }
    return matrix.calculateCost(path);
}

std::vector<int> PeaUtils::generateRandomPath(const int N)
{
    std::vector<int> path(N);
    for (int i = 0; i < N; ++i)
    {
        path[i] = i;
    }

    const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(path.begin(), path.end(), std::default_random_engine(seed));
    return path;
}


std::pair<int, int> PeaUtils::randomTwoInt(int range)
{
    int i = randomInt(range);
    int j = randomInt(range);

    while (i == j)
    {
        j = randomInt(range);
    }
    return {i, j};
}

PeaUtils::PeaUtils() = default;
