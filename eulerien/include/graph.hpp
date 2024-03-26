#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

/*----------------------------------------------------------------------------------------------------*/
// Constantes

/*----------------------------------------------------------------------------------------------------*/

/*
Classe représentant une arrête ou un arc
*/
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
        // Constructeur de l'arete
        Arete(int sommet1, int sommet2, int poids, bool oriente = false);

        // Destructeur de l'arete
        ~Arete();

        // Méthodes pour récupérer les attributs de l'arete
        int getSommet1() const;
        int getSommet2() const;
        int getPoids() const;
        bool getOriente() const;
};


class Graphe
{
    protected:
        // Nombre de sommets
        int m_nbSommet;
        // Nombre d'arrêtes
        int m_nbArete;
        // Poids total du graphe
        int m_poidsTot;
        // Liste des sommets
        std::vector<int> m_listeSommet;
        // Liste des arrêtes
        std::vector<Arete> m_listeArete;
    public:
        // Constructeur du graphe
        Graphe();

        Graphe(Graphe const &g);

        // Destructeur du graphe
        ~Graphe();

        // Méthodes pour récupérer les attributs du graphe
        int getNbSommet() const;
        int getNbArete() const;
        int getPoidsTot() const;
        std::vector<int> getListeSommet() const;
        std::vector<Arete> getListeArete() const;

        // Méthode pour ajouter une arrête
        void ajouterArete(int sommet1, int sommet2, int poids, bool oriente = false);

        // Méthode pour afficher le graphe (pour le debug)
        void afficher() const;
};


class GrapheAugmente: public Graphe
{
    private:
        // Poids total du graphe augmenté
        int m_poidsTotAugmente;
        // Liste des arrêtes augmentées
        std::vector<Arete> m_listeAreteAugmente;
    public:
        // Constructeur du graphe augmenté, à partir d'un graphe normal qui lui sert de base
        GrapheAugmente(Graphe g);

        // Destructeur du graphe augmenté
        ~GrapheAugmente();

        // Méthodes pour récupérer les attributs du graphe augmenté
        int getPoidsTotAugmente() const;
        std::vector<Arete> getListeAreteAugmentee() const;

        // Méthode pour ajouter une arrête augmentée
        void ajouterAreteAugmentee(int sommet1, int sommet2, int poids, bool oriente = false);

        // Méthode pour afficher le graphe augmenté (pour le debug), on surcharge la méthode de la classe mère
        void afficher() const;
};


// pas besoin de cette classe, on peut utiliser un vecteur d'aretes
// class Set
// {
//     private:
//         int m_taille;
//         std::vector<Arete> m_listeArete;

//     public:
// }
