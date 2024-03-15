#ifndef ORBITE_HPP_INCLUDED
#define ORBITE_HPP_INCLUDED

#include <iostream>
#include <stdbool.h>
#include<iostream>
#include<vector>
#include<array>

/*----------------------------------------------------------------------------------------------------*/
// CONSTANTES

/*----------------------------------------------------------------------------------------------------*/

class Aretes // arete ou arc
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
        Aretes(int sommet1, int sommet2, int poids, bool oriente = false);
        ~Aretes();
        int getSommet1();
        int getSommet2();
        int getPoids();
};


class Graph
{
    private:
        int m_nbSommet;
        int m_nbAretes;
        int m_poidsTot;
        vector<int> m_listeNoeuds;
        vector<Aretes> m_listeAretes;
    public:
        Graph();
        Graph(int nbSommet, vector<int> matriceAdjacence);
        ~Graph();

        vector<vector<Aretes>> trouverChemins();
};


class Set
{
    private:
        int m_taille;
        vector<Aretes> m_listeAretes;

    public:
}

#endif