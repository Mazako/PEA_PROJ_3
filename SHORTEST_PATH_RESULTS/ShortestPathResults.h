#ifndef PEA_PROJ_1_SHORTESTPATHRESULTS_H
#define PEA_PROJ_1_SHORTESTPATHRESULTS_H
#include <string>
#include <vector>

class ShortestPathResults
{
    bool noTimeCause;
    unsigned long long int cost;
    std::vector<int> path;
    int n;
    long long secondsTime;
    std::string resultsPath;

public:
    ShortestPathResults(unsigned long long int cost, int n, std::vector<int> path,
                        long long secondsTime, bool noTimeCause,
                        std::string resultsPath);

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] bool isNoTimeCause() const;

    [[nodiscard]] unsigned long long int getCost() const;

    [[nodiscard]] std::vector<int> getPath() const;

    [[nodiscard]] int getN() const;

    [[nodiscard]] long long int getSecondsTime() const;

    std::string getFilePath();
};

#endif // PEA_PROJ_1_SHORTESTPATHRESULTS_H
