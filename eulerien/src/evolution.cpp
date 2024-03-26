#include "evolution.hpp"

/*----------------------------------------------------------------------------------------------------*/
// Constantes

#define PROBA_1 0.5

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente mutation(const GrapheAugmente g)
{
    double random = (double)rand() / RAND_MAX;
    if (random < PROBA_1)
    {
        return mutation_1(g);
    }
    else
    {
        return mutation_2(g);
    }
    
}

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente mutation_1(const GrapheAugmente g)
{
    return g;
}

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente mutation_2(const GrapheAugmente g)
{
    return g;
}

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente croisement(const GrapheAugmente g1, const GrapheAugmente g2)
{
    return g1;
}
