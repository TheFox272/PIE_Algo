
#pragma once

#include "graph.hpp"

/*----------------------------------------------------------------------------------------------------*/

std::vector<Arete> trouver_cycle(GrapheAugmente g, bool augmenteOnly);
void eliminer_cycles_augmentes(GrapheAugmente& g);