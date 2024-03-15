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
int Arete::getSommet1() { return m_sommet1; }

int Arete::getSommet2() { return m_sommet2; }

int Arete::getPoids() { return m_poids; }

bool Arete::getOriente() { return m_oriente; }


// CLASSE GRAPH
// Constructeurs
Graph::Graph(): m_nbSommet(0), m_nbArete(0), m_poidsTot(0) {}

// Destructeur
Graph::~Graph() {}

// Méthodes
int Graph::getNbSommet() { return m_nbSommet; }

int Graph::getNbArete() { return m_nbArete; }

int Graph::getPoidsTot() { return m_poidsTot; }

std::vector<int> Graph::getListeSommet() { return m_listeSommet; }

std::vector<Arete> Graph::getListeArete() { return m_listeArete; }

void Graph::ajouterArete(int sommet1, int sommet2, int poids, bool oriente)
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

void Graph::afficher()
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

