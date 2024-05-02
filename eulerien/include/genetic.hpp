#pragma once

#include "graph.hpp"
#include "augmentation.hpp"
#include "evolution.hpp"
#include "anticycle.hpp"

#include <cmath>
#include <random>

/*----------------------------------------------------------------------------------------------------*/

// Le but est de minimiser cette fonction
int evaluer(const GrapheAugmente g);

std::vector<GrapheAugmente> init_population(const Graphe g, const int taille_pop);

std::vector<GrapheAugmente> selection(const std::vector<GrapheAugmente>& pop, const int taille_selection);

std::vector<GrapheAugmente> reproduction(const std::vector<GrapheAugmente>& pop, const int taille_pop, const int taille_evolution, const double taux_mutation);

std::vector<GrapheAugmente> evolution(const Graphe g, const int taille_pop, const int nb_gen, const double taux_selection, const double taux_mutation);

GrapheAugmente generer_graphe_eulerien(const Graphe g, const int taille_pop, const int nb_gen, const double taux_selection, const double taux_mutation);
