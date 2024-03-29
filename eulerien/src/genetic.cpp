#include "genetic.hpp"

/*----------------------------------------------------------------------------------------------------*/

int evaluer(const GrapheAugmente g)
{
    return g.getPoidsTotAugmente();
}

bool comparer(const GrapheAugmente g1, const GrapheAugmente g2)
{
    return evaluer(g1) <= evaluer(g2);
}

/*----------------------------------------------------------------------------------------------------*/

std::vector<GrapheAugmente> init_population(const Graphe g, const int taille_pop)
{
    std::vector<GrapheAugmente> pop;
    for (int i = 0; i < taille_pop; i++)
    {
        pop.push_back(augmente(g, i));
    }
    return pop;
}

/*----------------------------------------------------------------------------------------------------*/

std::vector<GrapheAugmente> selection(const std::vector<GrapheAugmente>& pop, const int taille_pop, const double taux_selection)
{
    // On arrondit à l'inférieur la taille de la sélection. On arrondira au supérieur pour la reproduction, afin de toujours avoir une variation de la population.
    const int taille_selection = static_cast<int>(std::floor(taille_pop * taux_selection));

    std::vector<GrapheAugmente> pop_copie = pop;
    std::partial_sort(pop_copie.begin(), pop_copie.begin() + taille_selection, pop_copie.end(), comparer);

    return std::vector<GrapheAugmente>(pop_copie.begin(), pop_copie.begin() + taille_selection);
}

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente selection_aleatoire(const std::vector<GrapheAugmente>& pop, const int taille_pop)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, taille_pop - 1);
    int index = dist(gen);
    return pop[index];
}

std::vector<GrapheAugmente> reproduction(const std::vector<GrapheAugmente>& pop, const int taille_pop, const double taux_reproduction, const double taux_mutation)
{
    // On arrondit au supérieur la taille de la reproduction, afin de toujours avoir une variation de la population.
    const int taille_reproduction = static_cast<int>(std::ceil(taille_pop * taux_reproduction));
    const int taille_mutation = static_cast<int>(std::ceil(taille_reproduction * taux_mutation));
    const int taille_croisement = taille_reproduction - taille_mutation;

    std::vector<GrapheAugmente> pop_reproduction;

    // Mutation
    for (int i = 0; i < taille_mutation; i++)
    {
        GrapheAugmente mutant = mutation(selection_aleatoire(pop, taille_pop));
        pop_reproduction.push_back(mutant);
    }

    // Croisement
    for (int i = 0; i < taille_croisement; i++)
    {
        GrapheAugmente parent1 = selection_aleatoire(pop, taille_pop);
        GrapheAugmente parent2 = selection_aleatoire(pop, taille_pop);
        GrapheAugmente enfant = croisement(parent1, parent2);
        pop_reproduction.push_back(enfant);
    }

    return pop_reproduction;
}

/*----------------------------------------------------------------------------------------------------*/

std::vector<GrapheAugmente> evolution(const Graphe g, const int taille_pop, const int nb_gen, const double taux_reproduction, const double taux_mutation)
{
    std::vector<GrapheAugmente> pop = init_population(g, taille_pop);

    for (int i = 0; i < nb_gen; i++)
    {
        std::vector<GrapheAugmente> pop_selection = selection(pop, taille_pop, 1-taux_reproduction);
        std::vector<GrapheAugmente> pop_reproduction = reproduction(pop, taille_pop, taux_reproduction, taux_mutation);

        pop = pop_selection;
        pop.insert(pop.end(), pop_reproduction.begin(), pop_reproduction.end());

        // On affiche le meilleur individu de la génération précédente
        std::cout << "Génération " << i << " : " << evaluer(pop[0]) << std::endl;
    }

    return pop;
}

/*----------------------------------------------------------------------------------------------------*/

GrapheAugmente generer_graphe_eulerien(const Graphe g, const int taille_pop, const int nb_gen, const double taux_reproduction, const double taux_mutation)
{
    std::vector<GrapheAugmente> pop = evolution(g, taille_pop, nb_gen, taux_reproduction, taux_mutation);
    std::sort(pop.begin(), pop.end(), comparer);
    return pop[0];
}
