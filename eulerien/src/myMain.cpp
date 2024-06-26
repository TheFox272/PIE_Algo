#include "main.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

/*----------------------------------------------------------------------------------------------------*/
// CONSTANTES

/*----------------------------------------------------------------------------------------------------*/

// Test mutation
void test_mutation(GrapheAugmente g)
{
    g.afficher();
    GrapheAugmente mutant = mutation_1(g);
    std::cout << "\nMutant" << std::endl;
    mutant.afficher();
}

// Test recherche de chemin eulérien
void test_graphe_eulerien(Graphe g)
{
    GrapheAugmente ga = generer_graphe_eulerien(g, 5, 20, 0.6, 0.7);
    ga.afficher();

}

// Test recherche de chemin eulérien arete
void test_chemin_arete(GrapheAugmente g, int sommet_depart, int sommet_arrive)
{
    std::vector<Arete> chemin = trouver_chemin_aleatoire(g, sommet_depart, sommet_arrive, false);

    // Affciher le chemin
    std::cout << "Chemin : ";
    afficher_chemin(chemin);
}

// Test de la fonction augmente
void test_augmente(GrapheAugmente g){
    for (int i = 0; i < 10; i++)
    {
        GrapheAugmente ga = augmente(g, i, g.getListeAreteAugmentee());
        // if (ga.getPoidsTotAugmente() == 1)
        ga.afficher();
    }

    // test_graphe_eulerien(ga);
    // std::vector<int> chemin = obtenir_chemin_eulerien(ga, 1);
    // std::cout << chemin.size() << " ";
    // for (size_t i = 0; i < chemin.size(); i++)
    // {
    //     std::cout << chemin[i] << "->";
    // }
    // std::cout << std::endl;
}

void test_croisement()
{
    Graphe g;
    g.ajouterArete(1, 2, 1, true);
    g.ajouterArete(2, 3);
    g.ajouterArete(3, 4);
    g.ajouterArete(4, 5);
    g.ajouterArete(4, 2);
    g.ajouterArete(5, 1);

    GrapheAugmente ga1 = augmente(g, 1);
    GrapheAugmente ga2 = augmente(g, 10);

    ga1.afficher();
    ga2.afficher();
    GrapheAugmente res = croisement(ga1, ga2);
    res.afficher();
}

void test_hierholzer(GrapheAugmente g)
{
    std::vector<int> chemin = hierholzer(g, 1);
    std::cout << "Chemin : ";
    for (size_t i = 0; i < chemin.size(); i++)
    {
        std::cout << chemin[i] << "->";
    }
    std::cout << std::endl;
}

void test_trouver_cycle(GrapheAugmente ga)
{
    std::vector<Arete> cycle_augmente =  trouver_cycle(ga,true);
    if(cycle_augmente.size() == 0)
    {
        std::cout << "Pas de cycle trouve" << std::endl;
    }
    else
    {
        std::cout << "Cycle trouve :" << std::endl;
    }
    afficher_chemin(cycle_augmente);
}

void test_eliminer_cycle_augmente(GrapheAugmente ga)
{
    std::vector<Arete> cycle_augmente = trouver_cycle(ga,true);
    if(cycle_augmente.size() == 0)
    {
        std::cout << "Pas de cycle a eliminer trouve" << std::endl;
    }
    else
    {
        std::cout << "Cycle a eliminer trouve :" << std::endl;
    }

    eliminer_cycles_augmentes(ga);

    ga.afficher();
/*
    GrapheAugmente ga_modifie = eliminer_cycle_augmente(ga);
    std::vector<Arete> liste_aretes = ga_modifie.getListeArete();

    std::cout << "Liste aretes : " << std::endl;
    afficher_chemin(liste_aretes);

    std::cout << "Liste aretes augmentees : " << std::endl;
    std::vector<Arete> liste_aretes_augmentees = ga_modifie.getListeAreteAugmentee();
    afficher_chemin(liste_aretes_augmentees);
*/
}

Graphe lecture_graphe(std::ifstream& fichier)
{
    if(!fichier.is_open())
    {
        std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
    }
    else
    {
        std::cout << "Lecture reussie." << std::endl;
    }

    std::string ligne;
    Graphe g;
    while (std::getline(fichier, ligne))
    {
        std::istringstream iss(ligne);
        int noeud1;
        int noeud2;
        double poids;
        bool oriente;
        if (iss >> noeud1 >> noeud2 >> poids >> oriente) {
                g.ajouterArete(noeud1, noeud2, poids, oriente);
        }
        else {
                std::cerr << "Erreur de lecture sur la ligne : " << ligne << std::endl;
        }

    }

    fichier.close();
    return g;
}

int main()
{
    Graphe g;
    // On ajoute les noeuds dans l'ordre afin de bien définir la matrice d'adjacence
    g.ajouterSommet(1);
    g.ajouterSommet(2);
    g.ajouterSommet(3);
    g.ajouterSommet(4);
    g.ajouterSommet(5);

    // On ajoute des arêtes normales
    g.ajouterArete(1, 2, 1, true);
    g.ajouterArete(2, 3,1, true);
    g.ajouterArete(3, 4,1, true);
    g.ajouterArete(4, 5,1, true);
    g.ajouterArete(4, 2,1, true);
    g.ajouterArete(5, 1,1, true);

    //g.afficherMatriceAdj();
    //test_graphe_eulerien(g);
    // test_augmente(g);

    /* test trouver cycle : */
    GrapheAugmente ga = GrapheAugmente(g);
    ga.ajouterAreteAugmentee(2,3,1, true);
    ga.ajouterAreteAugmentee(3,4,1, true);
    ga.ajouterAreteAugmentee(4,2,1, true);

    ga.ajouterAreteAugmentee(2,3,1, true);
    ga.ajouterAreteAugmentee(3,4,1, true);
    ga.ajouterAreteAugmentee(4,2,1, true);

    ga.ajouterAreteAugmentee(2,3,1, true);

    //ga.afficherListeSommets();
    ga.afficherMatriceAdj();
    test_trouver_cycle(ga);
    
    // test eliminer cycle :
    test_eliminer_cycle_augmente(ga);
    
    /*
    // test de lecture
    std::ifstream fichier("..\\..\\extraction\\graphe.txt");
    Graphe g_read = lecture_graphe(fichier);
    g_read.afficher();

    // augmentation du graphe
    std::cout << "Augmentation du graphe :" << std::endl;
    GrapheAugmente g_aug = augmente(g_read, 238);
    g_aug.afficher();

    // Croisement :
    std::cout << "Test de croisement :" << std::endl;
    GrapheAugmente ga_bis = GrapheAugmente(g);
    ga_bis.ajouterAreteAugmentee(1,2,1, true);
    ga_bis.ajouterAreteAugmentee(4,2,1, true);
    ga_bis.ajouterAreteAugmentee(5,1,1, true);

    ga.afficher();
    ga_bis.afficher();

    std::cout << "ENFANT" << std::endl;
    GrapheAugmente enfant = croisement(ga, ga_bis);
    enfant.afficher();
    

    test_eliminer_cycle_augmente(ga);
*/
    std::cout << "FIN DU PROGRAMME" << std::endl;
    
    return 0;
}
