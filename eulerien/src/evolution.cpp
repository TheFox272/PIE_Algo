#include "evolution.hpp"

/*----------------------------------------------------------------------------------------------------*/
// Constantes

// Probabilité de choisir la mutation 1 (plutôt que la mutation 2)
#define PROBA_1 1.0

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente mutation(const GrapheAugmente g)
{
    double random = (double)std::rand() / RAND_MAX;
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

GrapheAugmente mutation_1(const GrapheAugmente g)
{
    // On initialise le générateur de nombres aléatoires
    std::srand(unsigned(std::time(0)));

    // Récupérer les sommets du graphe augmenté
    std::vector<Arete> aretes = g.getListeAreteAugmentee();

    const size_t nbArete = aretes.size();

    if (nbArete < 2)
    {
        return g;
    }

    std::vector<Arete> chemin;

    // On choisit une arête augmentée aléatoire
    int iAreteActuelle = std::rand() % aretes.size();
    chemin.push_back(aretes[iAreteActuelle]);
    int sommet_depart = chemin[0].getSommet1();
    int sommet_arrive = chemin[0].getSommet2();

    // On supprime l'arête choisie de la liste des arêtes
    aretes.erase(aretes.begin() + iAreteActuelle);

    // On continue le DFS au travers des arêtes augmentées, pendant un nombre d'itérations aléatoire
    size_t nbIterations = std::rand() % aretes.size();
    for (size_t i = 0; i < nbIterations; i++)
    {   
        // On mélange les arêtes pour avoir un chemin aléatoire
        std::random_shuffle(aretes.begin(), aretes.end());

        bool trouve = false;
        for (size_t j = 0; j < aretes.size(); j++)
        {
            if (aretes[j].partDe(sommet_arrive))
            {
                trouve = true;

                int prochain_sommet = aretes[j].sommetOppose(sommet_arrive);
                Arete nouvelleArete(sommet_arrive, prochain_sommet, aretes[j].getPoids(), aretes[j].getOriente());
                sommet_arrive = prochain_sommet;

                chemin.push_back(nouvelleArete);

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
    std::vector<Arete> chemin_alternatif = trouver_chemin_aleatoire(g, sommet_depart, sommet_arrive, false);

    // Créer une copie du graphe augmenté
    GrapheAugmente nouveauGraphe(g);

    // Supprimer les arêtes du graphe augmenté qui sont dans le chemin
    for (size_t i = 0 ; i < chemin.size() ; i++)
        nouveauGraphe.supprimerAreteAugmentee(chemin[i]);

    // Ajouter au graphe augmenté de nouvelles arêtes entre les deux sommets
    for (size_t i = 0 ; i < chemin_alternatif.size() ; i++)
        nouveauGraphe.ajouterAreteAugmentee(chemin_alternatif[i]);

    return nouveauGraphe;
}


/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente mutation_2(const GrapheAugmente g)
{
    return g;
}

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente croisement(const GrapheAugmente g1, const GrapheAugmente g2, double prb)
{
    /* On ne prend qu'un enfant */
    std::vector<Arete> aug_1 = g1.getListeAreteAugmentee();
    std::vector<Arete> aug_2 = g2.getListeAreteAugmentee();
    
    std::random_shuffle(aug_1.begin(), aug_1.end());
    std::random_shuffle(aug_2.begin(), aug_2.end());

    Graphe resultat;

    if(aug_1.size()<aug_2.size())
    {
        for(int i = 0; i<aug_1.size(); ++i)
        {
            double random = static_cast<double>(rand()) / RAND_MAX;
            if(random < prb)
            {
                aug_1[i] = aug_2[i];
            }
        }

        Graphe g_graph(g1);
        GrapheAugmente g(g_graph);

        for(Arete arete : aug_1)
        {
            g.ajouterAreteAugmentee(arete);
        }
    
        resultat = g;
    }
    else
    {
        for(int i = 0; i<aug_2.size(); ++i)
        {
            double random = static_cast<double>(rand()) / RAND_MAX;
            if(random < prb)
            {
                aug_2[i] = aug_1[i];
            }
        }

        Graphe g_graph(g2);
        GrapheAugmente g(g_graph);

        for(Arete arete : aug_2)
        {
            g.ajouterAreteAugmentee(arete);
        }

        resultat = g;
    }

    return resultat;
}
