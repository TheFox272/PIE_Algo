
#pragma once

#include "graph.hpp"

/*----------------------------------------------------------------------------------------------------*/

std::vector<Arete> trouver_cycle(GrapheAugmente g, bool augmenteOnly);
GrapheAugmente eliminer_cycle_augmente(GrapheAugmente g);
