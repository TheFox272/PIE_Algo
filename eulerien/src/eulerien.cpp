# include "eulerien.hpp"

/*----------------------------------------------------------------------------------------------------*/

bool safe(std::vector<Arete> aretes, int sommet, Arete arete, int sommet_origine){
    aretes.erase(std::find(aretes.begin(), aretes.end(), arete));
    int sommet_suivant = arete.sommetOppose(sommet);
    Arete arete_dirigee(sommet, sommet_suivant, arete.getPoids(), true); 
    aretes.push_back(arete_dirigee);

    int equilibre = 0;
    for (Arete a : aretes)
    {
        if (a.vaVers(sommet_suivant) && a.getOriente())
            equilibre++;
        else if (a.partDe(sommet_suivant) && a.getOriente())
            equilibre--;
        else if (a.incident(sommet_suivant) && !a.getOriente()){
            if (safe(aretes, sommet_suivant, a, sommet_origine))
                equilibre--;
            else
                equilibre++;
        }
    }
    if (equilibre > 0){
        if (equilibre == 1 && sommet_suivant == sommet_origine)
            return true;
        return false;
    }
    return true;
}


int trouver_arete_partante_aleatoire(std::vector<Arete> &aretes, int sommet, int sommet_origine, bool oriente)
{
    std::random_shuffle(aretes.begin(), aretes.end());
    for (size_t i = 0; i < aretes.size(); i++)
    {
        if (aretes[i].partDe(sommet)){
            if (oriente){
                if (aretes[i].getOriente())
                    return static_cast<int>(i);
            }
            else{
                if (aretes[i].getOriente())
                    continue;
                if (safe(aretes, sommet, aretes[i], sommet_origine))
                    return static_cast<int>(i);
            }
        }
    }
    // Si aucune arete trouvée, on renvoie -1
    return -1;
}

int trouver_arete_partante_aleatoire(std::vector<Arete> &aretes, std::vector<int> liste_sommet, int sommet_origine, bool oriente=true)
{
    for (int u : liste_sommet)
    {
        int i = trouver_arete_partante_aleatoire(aretes, u, sommet_origine, oriente);
        if (i != -1){
            return u;
        }
    }
    if (oriente)
        return trouver_arete_partante_aleatoire(aretes, liste_sommet, sommet_origine, false);
    return -1;
}

std::vector<int> cycle_depuis(std::vector<Arete> &aretes, int sommet_depart)
{
    std::vector<int> cycle;
    cycle.push_back(sommet_depart);
    int i_arete_courante;
    int sommet_courant = sommet_depart;

    // On commence par trouver un cycle quelconque partant du sommet de départ
    do
    {
        // std::cout << sommet_courant << "   ";
        // afficher_chemin(aretes);
        // // on affiche le cycle
        // std::cout << "cycle : ";
        // for (size_t i = 0; i < cycle.size(); i++)
        // {
        //     std::cout << cycle[i] << "->";
        // }
        // std::cout << std::endl;
        // std::cout << std::endl;

        i_arete_courante = trouver_arete_partante_aleatoire(aretes, sommet_courant, sommet_depart, true);
        if (i_arete_courante == -1)
            i_arete_courante = trouver_arete_partante_aleatoire(aretes, sommet_courant, sommet_depart, false);
        if (i_arete_courante == -1){
            std::cerr << "Erreur : pas d'arête partante trouvée" << std::endl;
            return {};
        }
        sommet_courant = aretes[i_arete_courante].sommetOppose(sommet_courant);
        cycle.push_back(sommet_courant);
        aretes.erase(aretes.begin() + i_arete_courante);
    } while (sommet_courant != sommet_depart);

    return cycle;
}

std::vector<int> hierholzer(GrapheAugmente &g, int sommet_depart)
{
    // On initialise le générateur de nombres aléatoires
    std::srand(unsigned(std::time(0)));

    std::vector<Arete> aretes = g.getListeAreteTotale();
    std::vector<int> chemin;

    std::vector<int> cycle = cycle_depuis(aretes, sommet_depart);
    chemin.insert(chemin.begin(), cycle.begin(), cycle.end());

    // S'il reste des arêtes inexplorées, c'est qu'elles forment un sous-cycle que l'on va pouvoir fusionner à notre cycle original
    while (!aretes.empty())
    {
        sommet_depart = trouver_arete_partante_aleatoire(aretes, chemin, sommet_depart);
        if (sommet_depart == -1){
            printf("Erreur : graphe non eulérien !");
            return {};
        }
        cycle = cycle_depuis(aretes, sommet_depart);
        auto it = std::find(chemin.begin(), chemin.end(), sommet_depart);
        chemin.insert(it, cycle.begin(), cycle.end());
    }
    
    return chemin;
}


