#ifndef PEA_PROJ_1_SHORTESTPATHRESULTS_H
#define PEA_PROJ_1_SHORTESTPATHRESULTS_H
#include <string>

class ShortestPathResults {
    bool noTimeCause;
    unsigned long long int cost;
    int* path;
    int n;
    long long secondsTime;
    std::string resultsPath;

public:
    ShortestPathResults(unsigned long long int cost, int n, int* path,
                        long long secondsTime, bool noTimeCause, std::string resultsPath);

    ~ShortestPathResults();

    std::string toString();

    bool isNoTimeCause() const;

    unsigned long long int getCost() const;

    int* getPath() const;

    int getN() const;

    long long int getSecondsTime() const;

    std::string getFilePath();
};


#endif //PEA_PROJ_1_SHORTESTPATHRESULTS_H
