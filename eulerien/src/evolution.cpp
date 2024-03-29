#include "evolution.hpp"

/*----------------------------------------------------------------------------------------------------*/
// Constantes

#define PROBA_1 1.0

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente mutation(const GrapheAugmente g)
{
    double random = (double)rand() / RAND_MAX;
    if (random < PROBA_1)
    {
        return mutation_1(g);
    }
    else
    {
        return mutation_2(g);
    }
    
}

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente mutation_1(const GrapheAugmente g) {
    // On initialise le générateur de nombres aléatoires
    std::srand(unsigned(std::time(0)));

    // Récupérer les sommets du graphe augmenté
    std::vector<Arete> aretes = g.getListeAreteAugmentee();

    if (aretes.empty())
    {
        return g;
    }

    std::vector<int> chemin1;

    // On choisit une arête augmentée aléatoire
    int areteActuelle = rand() % aretes.size();
    int sommet_depart = aretes[areteActuelle].getSommet1();
    int sommet_arrive = aretes[areteActuelle].getSommet2();

    chemin1.push_back(sommet_depart);
    chemin1.push_back(sommet_arrive);
    aretes.erase(aretes.begin() + areteActuelle);

    // On continue le DFS au travers des arêtes augmentées, pendant un nombre d'itérations aléatoire
    size_t nbIterations = rand() % aretes.size();
    std::cout << "Nombre d'itérations : " << nbIterations << std::endl;
    for (size_t i = 0; i < nbIterations; i++)
    {   
        // On mélange les arêtes pour avoir un chemin aléatoire
        std::random_shuffle(aretes.begin(), aretes.end());

        bool trouve = false;
        for (size_t j = 0; j < aretes.size(); j++)
        {
            if (aretes[j].partDe(sommet_arrive))
            {
                int prochain_sommet = aretes[j].getSommet1() == sommet_arrive ? aretes[j].getSommet2() : aretes[j].getSommet1();
                trouve = true;
                sommet_arrive = prochain_sommet;
                chemin1.push_back(sommet_arrive);
                aretes.erase(aretes.begin() + j);
                break;
            }
        }
        if (!trouve)
        {
            break;
        }
    }

    // Trouver un chemin aléatoire entre les deux sommets passant uniquement par des arêtes normales
    std::vector<int> chemin2 = trouver_chemin_aleatoire(g, sommet_depart, sommet_arrive, false);

    // Afficher les deux chemins, pour le debug
    std::cout << "Chemin 1 : ";
    for (size_t i = 0; i < chemin1.size(); i++)
    {
        std::cout << chemin1[i] << "->";
    }
    std::cout << std::endl;

    std::cout << "Chemin 2 : ";
    for (size_t i = 0; i < chemin2.size(); i++)
    {
        std::cout << chemin2[i] << "->";
    }
    std::cout << std::endl;

    // Créer une copie du graphe augmenté
    GrapheAugmente nouveauGraphe(g);

    // Supprimer les arêtes du graphe augmenté qui sont dans le chemin
    for (size_t i = 0; i < chemin1.size() - 1; ++i) {
        int sommet1 = chemin1[i];
        int sommet2 = chemin1[i + 1];
        nouveauGraphe.supprimerAreteAugmentee(sommet1, sommet2);
    }

    // Ajouter au graphe augmenté de nouvelles arêtes entre les deux sommets
    for (size_t i = 0; i < chemin2.size() - 1; ++i) {
        int sommet1 = chemin2[i];
        int sommet2 = chemin2[i + 1];
        nouveauGraphe.augmenterArete(sommet1, sommet2);
    }

    // // Affcichage des deux graphes, pour le debug
    // std::cout << "Graphe original : " << std::endl;
    // g.afficher();
    // std::cout << "Graphe muté : " << std::endl;
    // nouveauGraphe.afficher();

    return nouveauGraphe;
}


/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente mutation_2(const GrapheAugmente g)
{
    return g;
}

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente croisement(const GrapheAugmente g1, const GrapheAugmente g2)
{
    return g1;
}
