#pragma once

#include "graph.hpp"

#include <stack>

/*----------------------------------------------------------------------------------------------------*/

// Renvoie un tableau correspondant au chemin eulérien du graphe g à partir du sommet sommet_depart, s'il existe. Sinon, renvoie nullptr.
std::vector<int> hierholzer(GrapheAugmente &g, int sommet_depart);
