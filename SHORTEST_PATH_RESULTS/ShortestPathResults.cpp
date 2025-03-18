#include "ShortestPathResults.h"

#include <utility>

ShortestPathResults::ShortestPathResults(const unsigned long long int cost,
                                         const int n, std::vector<int> path,
                                         const long long secondsTime,
                                         const bool noTimeCause,
                                         std::string resultsPath)
    : noTimeCause(noTimeCause), cost(cost), path(std::move(path)), n(n),
      secondsTime(secondsTime), resultsPath(std::move(resultsPath))
{
}

std::string ShortestPathResults::toString() const
{
    std::string str;
    str.append("Ilosc wierzcholkow: ").append(std::to_string(n));
    str.append("\tkoszt: ").append(std::to_string(cost));
    str.append("\tsciezka: ");
    for (int i = 0; i < n; i++)
    {
        str.append(std::to_string(path[i])).append(", ");
    }
    str.append("\tczas: ").append(std::to_string(secondsTime)).append(" s.");
    return str;
}

bool ShortestPathResults::isNoTimeCause() const { return noTimeCause; }

unsigned long long int ShortestPathResults::getCost() const { return cost; }

std::vector<int> ShortestPathResults::getPath() const { return path; }

int ShortestPathResults::getN() const { return n; }

long long int ShortestPathResults::getSecondsTime() const
{
    return secondsTime;
}

std::string ShortestPathResults::getFilePath() { return resultsPath; }
