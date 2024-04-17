# include "eulerien.hpp"

/*----------------------------------------------------------------------------------------------------*/

int trouver_arete_partante_aleatoire(std::vector<Arete> &aretes, int sommet, bool oriente)
{
    std::random_shuffle(aretes.begin(), aretes.end());
    for (size_t i = 0; i < aretes.size(); i++)
    {
        if (aretes[i].partDe(sommet) && oriente == aretes[i].getOriente())
            return static_cast<int>(i);
    }
    // Si aucune arete trouvée, on renvoie -1
    return -1;
}

int trouver_arete_partante_aleatoire(std::vector<Arete> &aretes, std::vector<int> liste_sommet, bool oriente=true)
{
    for (int u : liste_sommet)
    {
        int i = trouver_arete_partante_aleatoire(aretes, u, oriente);
        if (i != -1)
            return u;
    }
    if (oriente)
        return trouver_arete_partante_aleatoire(aretes, liste_sommet, false);
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
        std::cout << sommet_courant << "   ";
        afficher_chemin(aretes);
        // on affiche le cycle
        std::cout << "cycle : ";
        for (size_t i = 0; i < cycle.size(); i++)
        {
            std::cout << cycle[i] << "->";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        i_arete_courante = trouver_arete_partante_aleatoire(aretes, sommet_courant, true);
        if (i_arete_courante == -1)
            i_arete_courante = trouver_arete_partante_aleatoire(aretes, sommet_courant, false);
        if (i_arete_courante == -1)
            throw std::runtime_error("Erreur : graphe non eulérien !");
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
        sommet_depart = trouver_arete_partante_aleatoire(aretes, chemin);
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


