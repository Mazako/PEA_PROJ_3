#ifndef PEA_PROJ_3_GENETICALGORITHM_H
#define PEA_PROJ_3_GENETICALGORITHM_H

#include <vector>
#include "ShortestPathResults.h"
#include "TspMatrix.h"
#include "GeneticPath.h"

class GeneticAlgorithm {
    static std::vector<GeneticPath*> calculateInitialPopulation(TspMatrix *matrix, int size);
    static std::vector<GeneticPath*> rankBasedSelection(std::vector<GeneticPath*> &population, TspMatrix* matrix, int size);
    static void mutate(const std::vector<GeneticPath*>& parents, TspMatrix* matrix);
public:
    static GeneticPath *orderCrossover(GeneticPath *parent1, GeneticPath *parent2, TspMatrix *matrix);
    static GeneticPath *partiallyMatchedCrossover(GeneticPath *parent1, GeneticPath *parent2, TspMatrix *matrix);
    static ShortestPathResults *solve(TspMatrix *matrix, long timeInSeconds, int populationSize, std::string method);

};


#endif //PEA_PROJ_3_GENETICALGORITHM_H
