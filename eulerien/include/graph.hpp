#pragma once

#include <iostream>
#include <iostream>
#include <vector>

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
        int getSommet1();
        int getSommet2();
        int getPoids();
        bool getOriente();
};


class Graph
{
    private:
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
        Graph();

        // Destructeur du graphe
        ~Graph();

        // Méthodes pour récupérer les attributs du graphe
        int getNbSommet();
        int getNbArete();
        int getPoidsTot();
        std::vector<int> getListeSommet();
        std::vector<Arete> getListeArete();

        // Méthode pour ajouter une arrête
        void ajouterArete(int sommet1, int sommet2, int poids, bool oriente = false);

        // Méthode pour afficher le graphe (pour le debug)
        void afficher();
};


// pas besoin de cette classe, on peut utiliser un vecteur d'aretes
// class Set
// {
//     private:
//         int m_taille;
//         std::vector<Arete> m_listeArete;

//     public:
// }
