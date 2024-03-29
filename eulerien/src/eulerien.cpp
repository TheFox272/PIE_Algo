# include "eulerien.hpp"

/*----------------------------------------------------------------------------------------------------*/

int trouver_arete(const std::vector<Arete> &aretes, int depart)
{
    for (size_t i = 0; i < aretes.size(); i++)
    {
        if (aretes[i].partDe(depart))
        {
            return i;
        }
    }
    return -1;
}

std::vector<int> obtenir_chemin_eulerien(GrapheAugmente &g, int sommet_depart)
{
    // Initialisation
    std::vector<int> chemin;
    std::vector<Arete> aretes = g.getListeAreteTotale();

    chemin.push_back(sommet_depart);
    int sommet_actuel = sommet_depart;

    while (aretes.size() > 0)
    {
        int i = trouver_arete(aretes, sommet_actuel);
        if (i == -1)
        {
            return std::vector<int>();
        }
        else
        {
            chemin.push_back(aretes[i].getSommet2());
            sommet_actuel = aretes[i].getSommet2();
            aretes.erase(aretes.begin() + i);
        }
    }

    return chemin;
}
    

