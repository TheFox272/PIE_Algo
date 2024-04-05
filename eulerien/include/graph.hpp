#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <ctime>

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
        Arete(const int sommet1, const int sommet2, const int poids, const bool oriente=false);

        // Destructeur de l'arete
        ~Arete();

        // Méthodes pour récupérer les attributs de l'arete
        int getSommet1() const;
        int getSommet2() const;
        int getPoids() const;
        bool getOriente() const;

        // Méthode pour savoir si l'arrête est partante d'un sommet donné
        bool partDe(int sommet) const;
        bool vaVers(int sommet) const;

        
        // Operateur egalite :
        bool operator==(const Arete& autre) const;
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
        size_t getNbSommet() const;
        size_t getNbArete() const;
        int getPoidsTot() const;
        std::vector<int> getListeSommet() const;
        std::vector<Arete> getListeArete() const;

        // Méthode pour ajouter une arrête
        void ajouterArete(int sommet1, int sommet2, int poids=1, bool oriente=false);

        // Méthode pour afficher le graphe (pour le debug)
        void afficher() const;

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
    public:
        // Constructeur du graphe augmenté, à partir d'un graphe normal qui lui sert de base
        GrapheAugmente();
        GrapheAugmente(Graphe g);

        // Destructeur du graphe augmenté
        ~GrapheAugmente();

        // Méthodes pour récupérer les attributs du graphe augmenté
        int getPoidsTotAugmente() const;
        std::vector<Arete> getListeAreteAugmentee() const;
        std::vector<Arete> getListeAreteTotale() const;

        // Méthodes pour ajouter/supprimer une arrête augmentée
        void augmenterArete(Arete arete);
        void augmenterArete(int sommet1, int sommet2);
        void supprimerAreteAugmentee(int sommet1, int sommet2);

        // Méthode pour afficher le graphe augmenté (pour le debug), on surcharge la méthode de la classe mère
        void afficher() const;
};

/*----------------------------------------------------------------------------------------------------*/

// Renvoie un tableau correspondant à un chemin aléatoire du graphe g entre les sommets sommet_depart et sommet_arrive, s'il existe. Sinon, renvoie un tableau vide.
// Cette fonction se base sur l'algorithme de recherche en profondeur.
// Si augmenteOnly est à true, alors le chemin ne doit passer que par des arêtes augmentées. Sinon, il passera par des arêtes normales.
std::vector<int> trouver_chemin_aleatoire(const GrapheAugmente &g, int sommet_depart, int sommet_arrive, bool augmenteOnly=false);
std::vector<Arete> trouver_chemin_aleatoire_aretes(const GrapheAugmente &g, int sommet_depart, int sommet_arrive, bool augmenteOnly);

