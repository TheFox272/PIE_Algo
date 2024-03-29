#include "augmentation.hpp"

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente augmente(const Graphe g, const int seed)
{
    GrapheAugmente g_augmente = GrapheAugmente(g);

    //TODO: Implementer l'augmentation du graphe (Mayeul ?)

    // Solutions temporaire : on augmente toutes les arêtes
    for (size_t i = 0; i < g.getListeArete().size(); i++)
    {
        g_augmente.augmenterArete(g.getListeArete()[i].getSommet1(), g.getListeArete()[i].getSommet2());
    }

    return g_augmente;
}
