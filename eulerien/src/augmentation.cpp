#include "augmentation.hpp"

/*----------------------------------------------------------------------------------------------------*/

void update(std::vector<Arete>& chemin, std::vector<Arete>& aretesRestantes, std::vector<Arete>& cheminEulerien)
{
    for(const Arete& arete : chemin)
    {
        auto iArete = std::find(aretesRestantes.begin(), aretesRestantes.end(), arete);
        if(iArete != aretesRestantes.end())
            aretesRestantes.erase(iArete);
        cheminEulerien.push_back(arete);
    }
}

GrapheAugmente augmente(const Graphe g, const unsigned int graine, std::vector<Arete> AreteAugmentees)
{
    // On initialise le générateur de nombres aléatoires avec la graine
    std::srand(graine);

    if (g.getNbSommet() < 2)
    {
        std::cerr << "Le graphe doit contenir au moins 2 sommets" << std::endl;
        return GrapheAugmente();
    }

    std::vector<int> listeSommet = g.getListeSommet();
    int rand_vstart = std::rand() % listeSommet.size();
    // On s'assure que vend != vstart
    int rand_vend = (rand_vstart + (std::rand() % (listeSommet.size() - 1)) + 1) % listeSommet.size();

    int vstart = listeSommet[rand_vstart];
    int vhead = listeSommet[rand_vend];
    int x;

    std::vector<Arete> aretesRestantes = g.getListeArete();
    aretesRestantes.insert(aretesRestantes.end(), AreteAugmentees.begin(), AreteAugmentees.end());
    std::vector<Arete> cheminEulerien;
    GrapheAugmente ga(g);

    std::vector<Arete> chemin = trouver_chemin_aleatoire(ga, vstart, vhead, false);
    update(chemin, aretesRestantes, cheminEulerien);

    while(!aretesRestantes.empty())
    {        
        Arete arete_choisie;
        bool tous_incidents = true;
        std::vector<Arete> aretes_non_incidentes;
        for(const Arete& arete : aretesRestantes)
        {
            if(!(arete.incident(vhead)))
            {
                aretes_non_incidentes.push_back(arete);
                tous_incidents = false;
            }
        }

        if(tous_incidents)
        {
            int rand_arete = std::rand() % aretesRestantes.size();
            arete_choisie = aretesRestantes[rand_arete];
            x = arete_choisie.sommetOppose(vhead);
        }
        else
        {
            int rand_arete = rand() % aretes_non_incidentes.size();
            arete_choisie = aretes_non_incidentes[rand_arete];
            x = arete_choisie.getSommet1();
        }

        std::vector<Arete> cheminHead;
        if (x == arete_choisie.getSommet2())
            cheminHead = {arete_choisie};
        else
            cheminHead = trouver_chemin_aleatoire(ga, vhead, x, false);

        // Si le chemin termine déjà par l'arête choisie, on ne la rajoute pas (on évite un allez-retour inutile)
        if(cheminHead.back() != arete_choisie){
            vhead = arete_choisie.sommetOppose(x);
            Arete arete_temp(x, vhead, arete_choisie.getPoids(), true);
            cheminHead.push_back(arete_temp);
        }
        else
        {
            vhead = x;
        }

        update(cheminHead, aretesRestantes, cheminEulerien);
    }

    // On rajoute le chemin de retour pour fermer le cycle
    std::vector<Arete> chemin_retour = trouver_chemin_aleatoire(ga, vhead, vstart, false);
    for(const Arete& arete_chemin : chemin_retour)
    {
        cheminEulerien.push_back(arete_chemin);
    }

    // On ajoute les arêtes augmentées (où l'on passe plusieurs fois)
    for(size_t i=0 ; i < cheminEulerien.size() ; i++)
    {
        for(size_t j=i+1 ; j < cheminEulerien.size() ; j++)
        {
            if(cheminEulerien[i] == cheminEulerien[j] || cheminEulerien[i] == -cheminEulerien[j])
            {
                ga.ajouterAreteAugmentee(cheminEulerien[i]);
                break;
            }
        }
    }

    ga.setCheminEulerien(cheminEulerien);  // inutile ?

    return ga;
}
