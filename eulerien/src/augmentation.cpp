#include "augmentation.hpp"

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente augmente(Graphe& g, const int seed)
{
    /* Code de la partie "INITIALIZE THE POPULATION "*/
    std::vector<int> listeSommet = g.getListeSommet();
    int rand_start = std::rand() % listeSommet.size();
    int rand_end = std::rand() % listeSommet.size();

    int vstart = listeSommet[rand_start];
    int vhead = listeSommet[rand_end];

    std::vector<Arete> aretes_euler;
    std::vector<Arete> S = g.getListeArete();
        GrapheAugmente aug(g);


    while(S.size() > 0)
    {
        Arete arete_choisie(0,0,0);
        bool tous_incidents = true;
        std::vector<Arete> aretes_non_incidentes;
        for(auto arete_S : S)
        {
            if(!(arete_S.vaVers(vstart)))
            {
                aretes_non_incidentes.push_back(arete_S);
                tous_incidents = false;
            }
        }

        if(tous_incidents)
        {
            int rand_arete = rand() % S.size();
            arete_choisie = S[rand_arete];
        }
        else
        {
            int rand_arete = rand() % aretes_non_incidentes.size();
            arete_choisie = aretes_non_incidentes[rand_arete];
        }
        int x = arete_choisie.getSommet1();
        int y = arete_choisie.getSommet2();

        std::vector<Arete> chemin = trouver_chemin_aleatoire_aretes(aug, vhead, x, false);
        for(auto arete_chemin : chemin)
        {
            auto cherche = find(S.begin(), S.end(), arete_chemin);
            if(cherche != chemin.end())
            {
                S.erase(cherche);
                aretes_euler.push_back(arete_chemin);
            }
        }
        vhead = y;     
    }
    std::vector<Arete> chemin_retour = trouver_chemin_aleatoire_aretes(aug, vhead, vstart, false); /* il faut faire un algorithme qui renvoie une suite d'arete */
    for(auto arete_chemin : chemin_retour)
    {
            aretes_euler.push_back(arete_chemin);
    }

    for(auto arete1 : aretes_euler)
    {
        int compteur = 0;
        for(auto arete2 : aretes_euler)
        {
            if(arete2 == arete1)
            {
                ++compteur;
            }

            if(compteur > 1)
            {
                aug.augmenterArete(arete1);
            }
        }
    }

}
