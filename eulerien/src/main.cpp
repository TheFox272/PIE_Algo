#include "main.hpp"

/*----------------------------------------------------------------------------------------------------*/
// CONSTANTES

/*----------------------------------------------------------------------------------------------------*/

int main()
{
    Graphe g;
    g.ajouterArete(1, 2, 1);
    g.ajouterArete(2, 3, 1);
    g.ajouterArete(3, 4, 2);
    g.ajouterArete(4, 1, 2);

    g.afficher();

    GrapheAugmente ga = generer_chemin_eulerien(g, 10, 10, 0.5, 0.1, 0.4);
    ga.afficher();

    return 0;
}


