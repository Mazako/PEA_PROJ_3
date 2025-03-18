#ifndef PEA_PROJ_3_GENETICALGORITHM_H
#define PEA_PROJ_3_GENETICALGORITHM_H

#include "GeneticPath.h"
#include "ShortestPathResults.h"
#include "TspMatrix.h"
#include <vector>

class GeneticAlgorithm
{
    static std::vector<GeneticPath> calculateInitialPopulation(const TspMatrix& matrix,
                                                               int size);

    static std::vector<GeneticPath>
    rankBasedSelection(std::vector<GeneticPath>& population, int size);

    static void mutate(const std::vector<GeneticPath>& parents,
                       const TspMatrix& matrix);

public:
    static GeneticPath orderCrossover(const GeneticPath& parent1,
                                      const GeneticPath& parent2,
                                      const TspMatrix& matrix);

    static GeneticPath partiallyMatchedCrossover(const GeneticPath& parent1,
                                                 const GeneticPath& parent2,
                                                 const TspMatrix& matrix);

    static ShortestPathResults solve(TspMatrix& matrix, long timeInSeconds,
                                     int populationSize, const std::string& method,
                                     double crossingFactor,
                                     double mutationFactor);
};

#endif // PEA_PROJ_3_GENETICALGORITHM_H
