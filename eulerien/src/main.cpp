#include "main.hpp"

/*----------------------------------------------------------------------------------------------------*/
// CONSTANTES

/*----------------------------------------------------------------------------------------------------*/

// Test mutation
void test_mutation(GrapheAugmente g)
{
    g.afficher();
    GrapheAugmente mutant = mutation_1(g);
    std::cout << "\nMutant" << std::endl;
    mutant.afficher();
}

// Test recherche de chemin eulérien
void test_graphe_eulerien(Graphe g)
{
    GrapheAugmente ga = generer_graphe_eulerien(g, 5, 20, 0.6, 1.0);
    ga.afficher();

}

// Test recherche de chemin eulérien arete
void test_chemin_arete(GrapheAugmente g, int sommet_depart, int sommet_arrive)
{
    std::vector<Arete> chemin = trouver_chemin_aleatoire(g, sommet_depart, sommet_arrive, false);

    // Affciher le chemin
    std::cout << "Chemin : ";
    afficher_chemin(chemin);
}

// Test de la fonction augmente
void test_augmente(Graphe g){
    for (int i = 0; i < 1000; i++)
    {
        GrapheAugmente ga = augmente(g, i);
        if (ga.getPoidsTotAugmente() == 1)
            ga.afficher();
    }

    // test_graphe_eulerien(ga);
    // std::vector<int> chemin = obtenir_chemin_eulerien(ga, 1);
    // std::cout << chemin.size() << " ";
    // for (size_t i = 0; i < chemin.size(); i++)
    // {
    //     std::cout << chemin[i] << "->";
    // }
    // std::cout << std::endl;
}

int main()
{
    Graphe g;
    // On ajoute des arêtes normales
    g.ajouterArete(1, 2, 1, true);
    g.ajouterArete(2, 3);
    g.ajouterArete(3, 4);
    g.ajouterArete(4, 5);
    g.ajouterArete(4, 2);
    g.ajouterArete(5, 1);

    // g.afficher();
    test_graphe_eulerien(g);
    // test_augmente(g);

    return 0;
}


