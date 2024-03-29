#pragma once

#include "graph.hpp"

/*----------------------------------------------------------------------------------------------------*/

// Renvoie un tableau correspondant au chemin eulérien du graphe g à partir du sommet sommet_depart, s'il existe. Sinon, renvoie nullptr.
std::vector<int> obtenir_chemin_eulerien(GrapheAugmente &g, int sommet_depart);
