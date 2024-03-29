#pragma once

#include "graph.hpp"

#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

/*----------------------------------------------------------------------------------------------------*/

// Renvoie un graphes augmenté muté à partir du graphe augmenté g.
GrapheAugmente mutation(const GrapheAugmente g);

// Première mutation : on prend un chemin aléatoire entre deux sommets du graphe, ne passant que par des arêtes augmentées.
// On supprime les arêtes du graphe augmenté qui sont dans ce chemin, et on ajoute aux arêtes augmentées les arêtes du graphe
// appartenant à un autre chemin (aléatoire) entre les deux sommets.
GrapheAugmente mutation_1(const GrapheAugmente g);

GrapheAugmente mutation_2(const GrapheAugmente g);

GrapheAugmente croisement(const GrapheAugmente g1, const GrapheAugmente g2);
