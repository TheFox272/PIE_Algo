# include "eulerien.hpp"

/*----------------------------------------------------------------------------------------------------*/

size_t trouver_arete_partante_aleatoire(std::vector<Arete> &aretes, int sommet)
{
    std::random_shuffle(aretes.begin(), aretes.end());
    for (size_t i = 0; i < aretes.size(); i++)
    {
        if (aretes[i].partDe(sommet))
            return i;
    }
    return -1;
}

std::vector<int> obtenir_chemin_eulerien(GrapheAugmente &g, int sommet_depart)
{
    // // On initialise le générateur de nombres aléatoires
    // std::srand(unsigned(std::time(0)));

    // std::vector<Arete> aretes = g.getListeAreteTotale();
    std::vector<int> chemin;

    // chemin.push_back(sommet_depart);
    // int sommet_actuel = sommet_depart;

    //TODO: algorithme de Hierholzer

    return chemin;
}
    

