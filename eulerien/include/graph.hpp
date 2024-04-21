#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <ctime>

/*----------------------------------------------------------------------------------------------------*/
// Constantes

/*----------------------------------------------------------------------------------------------------*/

// Classe représentant une arête ou un arc
class Arete
{
    private:
        // Sommet duquel on part
        int m_sommet1;
        // Sommet auquel on arrive
        int m_sommet2;
        // Poids de l'arete
        int m_poids;
        // Indique si l'arrête peut être parcourue dans les deux sens ou pas
        bool m_oriente;
    public:
        // Constructeurs de l'arete
        Arete();
        Arete(const int sommet1, const int sommet2, const int poids, const bool oriente=false);
        Arete(const Arete& autre);

        // Destructeur de l'arete
        ~Arete();

        // Méthodes pour récupérer les attributs de l'arete
        int getSommet1() const;
        int getSommet2() const;
        int getPoids() const;
        bool getOriente() const;

        // Méthode pour set l'orientation de l'arrête
        void setOriente(bool oriente);

        // Méthode pour savoir si l'arrête est partante d'un sommet donné
        bool partDe(const int sommet) const;
        bool vaVers(const int sommet) const;

        // Méthode pour savoir si un sommet est incident à l'arrête
        bool incident(const int sommet) const;

        // Méthode pour donner le sommet opposé à un sommet donné, renvoie -1 si le sommet n'est pas sur l'arrête
        int sommetOppose(const int sommet) const;

        // Méthode pour savoir si l'arrête est nulle
        bool estNulle() const;

        // Opérateur de comparaison
        // Renvoie true si les deux arrêtes possèdent le même poids et les mêmes sommets, et qu'elles sont orientées de la même manière (ou qu'une des deux est non orientée)
        bool operator == (const Arete& autre) const;
        bool operator != (const Arete& autre) const;
        
        // Opérateur unaire de négation
        Arete operator - () const;
};


class Graphe
{
    protected:
        // Nombre de sommets
        size_t m_nbSommet;
        // Nombre d'arrêtes
        size_t m_nbArete;
        // Poids total du graphe
        int m_poidsTot;
        // Liste des sommets, permet la correspondance entre l'identifiant du sommet et son indice dans la matrice d'adjacence
        std::vector<int> m_listeSommet;
        // Liste des arrêtes
        std::vector<Arete> m_listeArete;
        // Matrice d'adjacence, chaque coordonnée (i,j) contient un coupe (p, k) ou k est le nombre d'arrêtes entre i et j, de poids p
        std::vector<std::vector<std::pair<int, int>>> m_matriceAdj;
    public:
        // Constructeur du graphe
        Graphe();

        Graphe(Graphe const &g);

        // Destructeur du graphe
        ~Graphe();

        // Méthodes pour récupérer les attributs du graphe
        size_t getNbSommet() const;
        size_t getNbArete() const;
        int getPoidsTot() const;
        std::vector<int> getListeSommet() const;
        std::vector<Arete> getListeArete() const;
        std::vector<std::vector<std::pair<int, int>>> getMatriceAdj() const;

        // Méthode pour ajouter une arête
        void ajouterArete(int sommet1, int sommet2, int poids=1, bool oriente=false);
        // Méthode pour ajouter un sommet
        void ajouterSommet(int sommet);

        // Méthode pour afficher le graphe (pour le debug)
        void afficher() const;
        void afficherListeSommets() const;
        void afficherMatriceAdj() const;

};


class GrapheAugmente: public Graphe
{
    private:
        // Nombre d'arrêtes augmentées
        size_t m_nbAreteAugmente;
        // Poids total du graphe augmenté
        int m_poidsTotAugmente;
        // Liste des arrêtes augmentées
        std::vector<Arete> m_listeAreteAugmente;
        // Chemin eulérien
        std::vector<Arete> m_cheminEulerien;
    public:
        // Constructeur du graphe augmenté, à partir d'un graphe normal qui lui sert de base
        GrapheAugmente();
        GrapheAugmente(Graphe g);
        GrapheAugmente(GrapheAugmente const &g, bool copieAreteAugmente=true);

        // Destructeur du graphe augmenté
        ~GrapheAugmente();

        // Méthodes pour récupérer les attributs du graphe augmenté
        int getPoidsTotAugmente() const;
        std::vector<Arete> getListeAreteAugmentee() const;
        std::vector<Arete> getListeAreteTotale() const;
        std::vector<Arete> getCheminEulerien() const;

        // Méthodes pour ajouter/supprimer une arrête augmentée
        void ajouterAreteAugmentee(Arete arete);
        void ajouterAreteAugmentee(int sommet1, int sommet2, int poids, bool oriente);
        void supprimerAreteAugmentee(Arete arete);

        // Méthode pour set le chemin eulérien
        void setCheminEulerien(std::vector<Arete> chemin);

        // Méthode pour afficher le graphe augmenté (pour le debug), on surcharge la méthode de la classe mère
        void afficher() const;
};

/*----------------------------------------------------------------------------------------------------*/

// Renvoie un tableau correspondant à un chemin aléatoire du graphe g entre les sommets sommet_depart et sommet_arrive, s'il existe. Sinon, renvoie un tableau vide.
// Cette fonction se base sur l'algorithme de recherche en profondeur.
// Si augmenteOnly est à true, alors le chemin ne doit passer que par des arêtes augmentées. Sinon, il passera par des arêtes normales.
std::vector<Arete> trouver_chemin_aleatoire(const GrapheAugmente &g, int sommet_depart, int sommet_arrive, bool augmenteOnly);

/*----------------------------------------------------------------------------------------------------*/

// Utile pour le debug, affiche un chemin
void afficher_chemin(const std::vector<Arete> &chemin);
