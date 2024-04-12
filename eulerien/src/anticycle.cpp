#include "anticycle.hpp"

/*----------------------------------------------------------------------------------------------------*/


bool noeud_dans_liste(int cible, std::vector<Arete> listeAretes)
{
    for(Arete arete : listeAretes)
    {
        if(cible == arete.getSommet1())
        {
            return true;
        }
    }

    return false;
}

bool recursion_cycle(int noeud, std::vector<std::vector<double>> matrice_adjacence, std::vector<Arete>& chemin_courant,std::vector<bool>& visites)
{
    int n = matrice_adjacence[noeud].size();

    for(int j = 0; j<n; ++j)
        {
            if(matrice_adjacence[noeud][j] != -1.0)
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
                    if(noeud_dans_liste(j, chemin_courant))
                    {
                        chemin_courant.push_back(arete_ij);
                        return true;
                    }
                }
                
            }
        }

    return false;
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
        int noeud2 = arete.getSommet2();

        matrice_adjacence[noeud1][noeud2] = poids;
    }
    std::vector<int> liste_noeuds;
    int nb_sommet(0);

    if(augmenteOnly)
    {
        for(Arete arete : listeAretes)
        {
        
            int sommet1 = arete.getSommet1();
            int sommet2 = arete.getSommet2();
        
            if (std::find(liste_noeuds.begin(), liste_noeuds.end(), sommet1) == liste_noeuds.end())
            {
                liste_noeuds.push_back(sommet1);
                nb_sommet++;
            }
            if (std::find(liste_noeuds.begin(), liste_noeuds.end(), sommet2) == liste_noeuds.end())
            {
                liste_noeuds.push_back(sommet2);
                nb_sommet++;
            }
        
        }
    }
    else
    {
        liste_noeuds = g.getListeSommet();
    }

    int aleatoire_n = rand() % nb_sommet;
    int noeud_depart = liste_noeuds[aleatoire_n];
    visites[noeud_depart] = true;

    bool existence_cycle = recursion_cycle(noeud_depart, matrice_adjacence, chemin_courant, visites);
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


GrapheAugmente eliminer_cycle_augmente(GrapheAugmente g)
{
    std::vector<Arete> cycle_augmente = trouver_cycle(g, true);
    std::vector<Arete> aretes_augmente = g.getListeAreteAugmentee();

    if(cycle_augmente.size() == 0)
    {
        return g;
    }

    for(Arete arete_cycle : cycle_augmente)
    {
        int n = aretes_augmente.size();
        for(int i = 0; i<n; ++i)
        {
            if(arete_cycle == aretes_augmente[i])
            {
                aretes_augmente.erase(aretes_augmente.begin() + i);
            }

        }
    }
    
    GrapheAugmente resultat((Graphe) g);

    for(Arete arete_augmente : aretes_augmente)
    {
        resultat.ajouterAreteAugmentee(arete_augmente);
    }
    
    return resultat;
}




