#include "main.hpp"

/*----------------------------------------------------------------------------------------------------*/
// CONSTANTES

/*----------------------------------------------------------------------------------------------------*/

// Test recherche de chemin
void test_chemin(GrapheAugmente g, int sommet_depart, int sommet_arrive)
{
    std::vector<int> chemin = trouver_chemin_aleatoire(g, sommet_depart, sommet_arrive, false);
    if (chemin.size() == 0)
    {
        std::cout << "Pas de chemin entre les deux sommets" << std::endl;
    }
    else
    {
        for (size_t i = 0; i < chemin.size(); i++)
        {
            std::cout << chemin[i] << "->";
        }
    }
    std::cout << std::endl;
}

// Test mutation
void test_mutation(GrapheAugmente g)
{
    GrapheAugmente mutant = mutation_1(g);
    mutant.afficher();
}

// Test recherche de chemin eulérien
void test_graphe_eulerien(GrapheAugmente g)
{
    GrapheAugmente ga = generer_graphe_eulerien(g, 10, 100, 0.5, 0.1);
    ga.afficher();
}



int main()
{
    GrapheAugmente g;
    // On ajoute des arêtes normales
    g.ajouterArete(1, 2);
    g.ajouterArete(2, 3);
    g.ajouterArete(3, 4);
    g.ajouterArete(4, 5);
    g.ajouterArete(4, 2);
    g.ajouterArete(5, 1);
    // // On ajoute des arêtes augmentées
    g.augmenterArete(1, 2);
    g.augmenterArete(2, 3);
    g.augmenterArete(3, 4);
    g.augmenterArete(4, 5);

    g.afficher();

    test_mutation(g);

    return 0;
}


