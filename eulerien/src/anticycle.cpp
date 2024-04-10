#include "anticycle.hpp"

/*----------------------------------------------------------------------------------------------------*/

bool arete_dans_liste(Arete cible, std::vector<Arete> listeAretes)
{
    for(Arete arete : listeAretes)
    {
        if(cible == arete)
        {
            return true;
        }
    }

    return false;
}

bool recursion_cycle(int noeud, std::vector<std::vector<double>> matrice_adjacence, std::vector<Arete> chemin_courant,std::vector<bool> visites)
{
    int n = matrice_adjacence[noeud].size();

    for(int j = 0; j<n; ++j)
        {
            if(matrice_adjacence[noeud][j] != -1)
            {
                if(!visites[j])
                {
                    visites[j] = true;
                    Arete arete_ij(noeud, j, matrice_adjacence[noeud][j], true);
                    chemin_courant.push_back(arete_ij);
                    if(recursion_cycle(j, matrice_adjacence, chemin_courant, visites))
                    {
                        return true;
                    }
                    else
                    {
                        chemin_courant.pop_back();
                    }
                }
                else
                {
                    Arete arete_ij(noeud, j, matrice_adjacence[noeud][j], true);
                    if(arete_dans_liste(arete_ij, chemin_courant))
                    {
                        chemin_courant.push_back(arete_ij);
                        return true;
                    }
                }
                
            }
        }

    return false;
}


GrapheAugmente eliminer_cycle_augmente(GrapheAugmente g)
{
    std::vector<Arete> cycle_augmente = trouver_cycle(g, true);
    std::vector<Arete> aretes_augmente = g.getListeAreteAugmentee();
    int n = aretes_augmente.size();

    if(cycle_augmente.size() == 0)
    {
        return g;
    }

    for(Arete arete_cycle : cycle_augmente)
    {
        for(int i = 0; i<n; ++i)
        {
            if(arete_cycle == aretes_augmente[i])
            {
                aretes_augmente.erase(aretes_augmente.begin() + i);
            }
        }
    }

    GrapheAugmente resultat(g);
    
    for(Arete arete_augmente : aretes_augmente)
    {
        resultat.ajouterAreteAugmentee(arete_augmente);
    }

    return resultat;
}

std::vector<Arete> trouver_cycle(GrapheAugmente g, bool augmenteOnly)
/* 
    Retourne un tableau vide si pas de cycle
    Sinon retourne le chemin
*/
{

    std::srand(unsigned(std::time(0)));

    std::vector<Arete> chemin_courant;

    int n = g.getNbSommet();
    std::vector<bool> visites(n,false);

    std::vector<std::vector<double>> matrice_adjacence(n, std::vector<double>(n, -1.0));
    std::vector<Arete> listeAretes;
    if(augmenteOnly)
    {
        listeAretes = g.getListeAreteAugmentee();
    }
    else
    {
        listeAretes = g.getListeArete();
    }

    for(Arete arete : listeAretes)
    {
        double poids = arete.getPoids();
        int noeud1 = arete.getSommet1();
        int noeud2 = arete.getSommet1();

        matrice_adjacence[noeud1][noeud2] = poids;
    }

    int aleatoire_n = rand() % n;
    bool existence_cycle = recursion_cycle(g.getListeSommet()[aleatoire_n], matrice_adjacence, chemin_courant, visites);

    if(existence_cycle)
    {
        Arete final = chemin_courant.back();
        int sommet_final = final.getSommet2();
        int i = 0;
        while(chemin_courant[i].getSommet1() != sommet_final)
        {
            chemin_courant.erase(chemin_courant.begin() + i);
            ++i;
        }
        return chemin_courant;
    }
    else
    {
        return {};
    }
}


