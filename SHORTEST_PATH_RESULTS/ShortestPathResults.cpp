#include "ShortestPathResults.h"

ShortestPathResults::ShortestPathResults(unsigned long long int cost, int n, int* path,
                                         long long secondsTime, bool noTimeCause, std::string resultPath) : cost(cost), path(path), n(n), secondsTime(secondsTime),
                                                                                 noTimeCause(noTimeCause), resultsPath(resultPath) {
}

ShortestPathResults::~ShortestPathResults() {
    delete this->path;
}

std::string ShortestPathResults::toString() {
    std::string str;
    str.append("Ilosc wierzcholkow: ").append(std::to_string(n));
    str.append("\tkoszt: ").append(std::to_string(cost));
    str.append("\tsciezka: ");
    for (int i = 0; i < n; i++) {
        str.append(std::to_string(path[i])).append(", ");
    }
    str.append("\tczas: ").append(std::to_string(secondsTime)).append(" s.");
    return str;
}

bool ShortestPathResults::isNoTimeCause() const {
    return noTimeCause;
}

unsigned long long int ShortestPathResults::getCost() const {
    return cost;
}

int* ShortestPathResults::getPath() const {
    return path;
}

int ShortestPathResults::getN() const {
    return n;
}

long long int ShortestPathResults::getSecondsTime() const {
    return secondsTime;
}

std::string ShortestPathResults::getFilePath() {
    return resultsPath;
}
