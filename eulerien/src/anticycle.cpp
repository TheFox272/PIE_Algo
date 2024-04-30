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

int trouver_correspondance(int noeud,std::vector<int> listeSommet)
/*
    Fonction qui permet de trouver le noeud réel du graphe à partir d'un
    numéroté comme dans listeSommet (qui ne sert que pour la matrice d'adjacence)
*/
{
    int taille_liste = listeSommet.size();
    for(int i = 0; i<taille_liste; ++i)
    {
        if(listeSommet[i]==noeud)
        {
            return i;
        }
    }

    return -1;

}

bool recursion_cycle(int noeud, std::vector<std::vector<std::pair<int, int>>>& matrice_adjacence, std::vector<Arete>& chemin_courant,std::vector<bool>& visites,bool augmenteOnly)
{
    /*
    Quelque chose n'est pas clair :
    Un cycle de non-orientés, ok il faut éliminer.
    Un cycle d'orientés, ok il faut éliminer.
    Mais un mix ? Aucune idée.

    Pour l'instant :
    On élimine quelque soit l'orientation de l'arète.
    Ce ne sera pas un soucis car on utilisera que des aretes augmentés orientés.

    L'erreur semble être est dans l'article utilisé
    "Genetic Algorithm for Mixed Chinese Postman Problem"

    Il faudrait contacter les auteurs pour en avoir le coeur net.
    */
    int n = matrice_adjacence[noeud].size();

    for(int j = 0; j<n; ++j)
        {
            if(augmenteOnly)
            {
                // on vérifie que l'arète est augmenté
            if(matrice_adjacence[noeud][j].first > 0 && matrice_adjacence[noeud][j].second > 1)
            {
                if(!visites[j])
                {
                    visites[j] = true;
                    Arete arete_ij = Arete(noeud, j, matrice_adjacence[noeud][j].first, true);
                    
                    chemin_courant.push_back(arete_ij);
                    if(recursion_cycle(j, matrice_adjacence, chemin_courant, visites, augmenteOnly))
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
                    Arete arete_ij(noeud, j, matrice_adjacence[noeud][j].first, true);
                    if(noeud_dans_liste(j, chemin_courant))
                    {
                        chemin_courant.push_back(arete_ij);
                        return true;
                    }
                }
                
            }
            }
            else
            {
                if(matrice_adjacence[noeud][j].first > 0)
            {
                if(!visites[j])
                {
                    visites[j] = true;

                    Arete arete_ij(noeud, j, matrice_adjacence[noeud][j].second, true);
                    chemin_courant.push_back(arete_ij);
                    if(recursion_cycle(j, matrice_adjacence, chemin_courant, visites,augmenteOnly))
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
                    Arete arete_ij(noeud, j, matrice_adjacence[noeud][j].first, true);
                    if(noeud_dans_liste(j, chemin_courant))
                    {
                        chemin_courant.push_back(arete_ij);
                        return true;
                    }
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

    std::vector<Arete> listeAretes;
    if(augmenteOnly)
    {
        listeAretes = g.getListeAreteAugmentee();
    }
    else
    {
        listeAretes = g.getListeArete();
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
        nb_sommet = liste_noeuds.size();
    }

    if(nb_sommet == 0)
    {
        return {};
    }

    int aleatoire_n = std::rand() % nb_sommet;

    int noeud_depart = liste_noeuds[aleatoire_n];
    std::vector<int> listeSommet = g.getListeSommet();

    // On cherche la correspondance avec la liste de sommet de la matrice d'adjacence.
    int noeud_depart_correspondance = trouver_correspondance(noeud_depart, listeSommet);

    visites[noeud_depart_correspondance] = true;
    std::vector<std::vector<std::pair<int, int>>> matrice_adjacence = g.getMatriceAdj();

    // Attention : les noeuds du cycle sont numérotés comme dans listeSommet. Il faudra les convertir plus tard (voir ci-dessous)
    bool existence_cycle = recursion_cycle(noeud_depart_correspondance, matrice_adjacence, chemin_courant, visites, augmenteOnly);
    if(existence_cycle)
    {        
        Arete final = chemin_courant.back();
        
        int sommet_final = final.getSommet2();
        std::cout << "final : " << sommet_final << "\n";
        int i = 0;
            
        while(chemin_courant[i].getSommet1() != sommet_final)
        {
            ++i;
        }

        chemin_courant.erase(chemin_courant.begin(), chemin_courant.begin() + i);

        // On convertit les sommets du cycle (numéroté comme dans listeSommet) en ceux originels.
        int chemin_courant_taille = chemin_courant.size();
        for(int i = 0; i<chemin_courant_taille; ++i)
        {
            Arete arete(listeSommet[chemin_courant[i].getSommet1()], listeSommet[chemin_courant[i].getSommet2()], chemin_courant[i].getPoids(), chemin_courant[i].getOriente());
            chemin_courant[i] = arete;
        }
        return chemin_courant;
    }
    else
    {
        return {};
    }
}


void eliminer_cycles_augmentes(GrapheAugmente& g)
{
    std::vector<Arete> cycle_augmente = trouver_cycle(g, true);

    while(cycle_augmente.size() != 0)
    {
        for(Arete arete_cycle : cycle_augmente)
        {
            g.supprimerAreteAugmentee(arete_cycle);
        }
        std::cout << std::endl;

        afficher_chemin(cycle_augmente);
        cycle_augmente = trouver_cycle(g, true);
    }

}




