# include "graph.hpp"

/*----------------------------------------------------------------------------------------------------*/
// Constantes

/*----------------------------------------------------------------------------------------------------*/

// CLASSE ARETE
// Constructeurs
Arete::Arete(int sommet1, int sommet2, int poids, bool oriente): m_sommet1(sommet1), m_sommet2(sommet2), m_poids(poids), m_oriente(oriente) {}

// Destructeur
Arete::~Arete() {}

// Méthodes
int Arete::getSommet1() const { return m_sommet1; }

int Arete::getSommet2() const { return m_sommet2; }

int Arete::getPoids() const { return m_poids; }

bool Arete::getOriente() const { return m_oriente; }


// CLASSE Graphe
// Constructeurs
Graphe::Graphe(): m_nbSommet(0), m_nbArete(0), m_poidsTot(0) {}

Graphe::Graphe(Graphe const &g): m_nbSommet(g.m_nbSommet), m_nbArete(g.m_nbArete), m_poidsTot(g.m_poidsTot), m_listeSommet(g.m_listeSommet), m_listeArete(g.m_listeArete) {}

// Destructeur
Graphe::~Graphe() {}

// Méthodes
int Graphe::getNbSommet() const { return m_nbSommet; }

int Graphe::getNbArete() const { return m_nbArete; }

int Graphe::getPoidsTot() const { return m_poidsTot; }

std::vector<int> Graphe::getListeSommet() const { return m_listeSommet; }

std::vector<Arete> Graphe::getListeArete() const { return m_listeArete; }

void Graphe::ajouterArete(int sommet1, int sommet2, int poids, bool oriente)
{
    m_listeArete.push_back(Arete(sommet1, sommet2, poids, oriente));
    m_nbArete++;
    m_poidsTot += poids;
    if (std::find(m_listeSommet.begin(), m_listeSommet.end(), sommet1) == m_listeSommet.end())
    {
        m_listeSommet.push_back(sommet1);
        m_nbSommet++;
    }
    if (std::find(m_listeSommet.begin(), m_listeSommet.end(), sommet2) == m_listeSommet.end())
    {
        m_listeSommet.push_back(sommet2);
        m_nbSommet++;
    }
}

void Graphe::afficher() const
{
    std::cout << "Nombre de sommets : " << m_nbSommet << std::endl;
    std::cout << "Nombre d'arrêtes : " << m_nbArete << std::endl;
    std::cout << "Poids total : " << m_poidsTot << std::endl;
    std::cout << "Liste des sommets : ";
    for (int i = 0; i < m_nbSommet; i++)
    {
        std::cout << m_listeSommet[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Liste des arrêtes : " << std::endl;
    for (int i = 0; i < m_nbArete; i++)
    {
        std::cout << "Arete " << i << " : " << m_listeArete[i].getSommet1() << " - " << m_listeArete[i].getSommet2() << " (" << m_listeArete[i].getPoids() << ")";
        if (m_listeArete[i].getOriente())
        {
            std::cout << " orientée" << std::endl;
        }
        else
        {
            std::cout << " non orientée" << std::endl;
        }
    }
}


// CLASSE GrapheAugmente
// Constructeurs
GrapheAugmente::GrapheAugmente(Graphe g): Graphe(g), m_poidsTotAugmente(0) {}

// Destructeur
GrapheAugmente::~GrapheAugmente() {}

// Méthodes
int GrapheAugmente::getPoidsTotAugmente() const { return m_poidsTotAugmente; }

std::vector<Arete> GrapheAugmente::getListeAreteAugmentee() const { return m_listeAreteAugmente; }

void GrapheAugmente::ajouterAreteAugmentee(int sommet1, int sommet2, int poids, bool oriente)
{
    m_listeAreteAugmente.push_back(Arete(sommet1, sommet2, poids, oriente));
    m_nbArete++;
    m_poidsTotAugmente += poids;
}

void GrapheAugmente::afficher() const
{
    std::cout << "Nombre de sommets : " << m_nbSommet << std::endl;
    std::cout << "Nombre d'arrêtes : " << m_nbArete << std::endl;
    std::cout << "Poids total : " << m_poidsTot << std::endl;
    std::cout << "Liste des sommets : ";
    for (int i = 0; i < m_nbSommet; i++)
    {
        std::cout << m_listeSommet[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Liste des arrêtes : " << std::endl;
    for (int i = 0; i < m_nbArete; i++)
    {
        std::cout << "Arete " << i << " : " << m_listeArete[i].getSommet1() << " - " << m_listeArete[i].getSommet2() << " (" << m_listeArete[i].getPoids() << ")";
        if (m_listeArete[i].getOriente())
        {
            std::cout << " orientée" << std::endl;
        }
        else
        {
            std::cout << " non orientée" << std::endl;
        }
    }
    std::cout << "Poids total augmenté : " << m_poidsTotAugmente << std::endl;
    std::cout << "Liste des arrêtes augmentées : " << std::endl;
    for (int i = 0; i < m_nbArete; i++)
    {
        std::cout << "Arete " << i << " : " << m_listeAreteAugmente[i].getSommet1() << " - " << m_listeAreteAugmente[i].getSommet2() << " (" << m_listeAreteAugmente[i].getPoids() << ")";
        if (m_listeAreteAugmente[i].getOriente())
        {
            std::cout << " orientée" << std::endl;
        }
        else
        {
            std::cout << " non orientée" << std::endl;
        }
    }
}


