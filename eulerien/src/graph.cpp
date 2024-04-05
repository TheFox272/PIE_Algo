# include "graph.hpp"

/*----------------------------------------------------------------------------------------------------*/
// Constantes

/*----------------------------------------------------------------------------------------------------*/

// CLASSE ARETE
// Constructeurs
Arete::Arete(const int sommet1, const int sommet2, const int poids, const bool oriente): m_sommet1(sommet1), m_sommet2(sommet2), m_poids(poids), m_oriente(oriente) {}

// Destructeur
Arete::~Arete() {}

// Méthodes
int Arete::getSommet1() const { return m_sommet1; }

int Arete::getSommet2() const { return m_sommet2; }

int Arete::getPoids() const { return m_poids; }

bool Arete::getOriente() const { return m_oriente; }

bool Arete::partDe(int sommet) const
{
    return (m_sommet1 == sommet || (m_sommet2 == sommet && m_oriente == false));
}

bool Arete::vaVers(int sommet) const
{
    return (m_sommet2 == sommet || (m_sommet1 == sommet && m_oriente == false));
}


// Operateur egalite :
bool Arete::operator==(const Arete& autre) const
{
    return m_sommet1 == autre.m_sommet1 && m_sommet2 == autre.m_sommet2 && m_poids == autre.m_poids && m_oriente == autre.m_oriente;
}

// CLASSE Graphe
// Constructeurs
Graphe::Graphe(): m_nbSommet(0), m_nbArete(0), m_poidsTot(0) {}

Graphe::Graphe(Graphe const &g): m_nbSommet(g.m_nbSommet), m_nbArete(g.m_nbArete), m_poidsTot(g.m_poidsTot), m_listeSommet(g.m_listeSommet), m_listeArete(g.m_listeArete) {}

// Destructeur
Graphe::~Graphe() {}

// Méthodes
size_t Graphe::getNbSommet() const { return m_nbSommet; }

size_t Graphe::getNbArete() const { return m_nbArete; }

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
    for (size_t i = 0; i < m_nbSommet; i++)
    {
        std::cout << m_listeSommet[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Liste des arrêtes : " << std::endl;
    for (size_t i = 0; i < m_nbArete; i++)
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
GrapheAugmente::GrapheAugmente(): Graphe(), m_nbAreteAugmente(0), m_poidsTotAugmente(0) {}
GrapheAugmente::GrapheAugmente(Graphe g): Graphe(g), m_nbAreteAugmente(0), m_poidsTotAugmente(0) {}

// Destructeur
GrapheAugmente::~GrapheAugmente() {}

// Méthodes
int GrapheAugmente::getPoidsTotAugmente() const { return m_poidsTotAugmente; }

std::vector<Arete> GrapheAugmente::getListeAreteAugmentee() const { return m_listeAreteAugmente; }

std::vector<Arete> GrapheAugmente::getListeAreteTotale() const
{
    std::vector<Arete> listeAreteTotale = m_listeArete;
    for (const Arete& arete : m_listeAreteAugmente)
    {
        listeAreteTotale.push_back(arete);
    }
    return listeAreteTotale;
}

void GrapheAugmente::augmenterArete(int sommet1, int sommet2)
{
    for (size_t i = 0; i < m_nbArete; i++)
    {
        if (m_listeArete[i].partDe(sommet1) && m_listeArete[i].vaVers(sommet2))
        {
            m_listeAreteAugmente.push_back(m_listeArete[i]);
            m_poidsTotAugmente += m_listeArete[i].getPoids();
            m_nbAreteAugmente++;
            return;
        }
    }
}
void GrapheAugmente::augmenterArete(Arete arete)
{
    m_listeAreteAugmente.push_back(arete);
    /* ajouter le poids */
}

void GrapheAugmente::supprimerAreteAugmentee(int sommet1, int sommet2)
{
    for (size_t i = 0; i < m_nbAreteAugmente; i++)
    {
        if (m_listeAreteAugmente[i].partDe(sommet1) && m_listeAreteAugmente[i].vaVers(sommet2))
        {
            m_poidsTotAugmente -= m_listeAreteAugmente[i].getPoids();
            m_listeAreteAugmente.erase(m_listeAreteAugmente.begin() + i);
            m_nbAreteAugmente--;
            return;
        }
    }
    // Si l'arête n'a pas été trouvée, on lève une exception
    throw std::invalid_argument("L'arête n'a pas été trouvée dans la liste des arêtes augmentées");
}

void GrapheAugmente::afficher() const
{
    std::cout << "Nombre de sommets : " << m_nbSommet << std::endl;
    std::cout << "Nombre d'arrêtes : " << m_nbArete << std::endl;
    std::cout << "Poids total : " << m_poidsTot << std::endl;
    std::cout << "Liste des sommets : ";
    for (size_t i = 0; i < m_nbSommet; i++)
    {
        std::cout << m_listeSommet[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Liste des arrêtes : " << std::endl;
    for (size_t i = 0; i < m_nbArete; i++)
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
    for (size_t i = 0; i < m_nbAreteAugmente; i++)
    {
        std::cout << "Arete augmentée " << i << " : " << m_listeAreteAugmente[i].getSommet1() << " - " << m_listeAreteAugmente[i].getSommet2() << " (" << m_listeAreteAugmente[i].getPoids() << ")";
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

/*----------------------------------------------------------------------------------------------------*/
// Fonctions

std::vector<int> DFS(std::vector<Arete> &aretes, int sommet, int sommet_arrive, std::unordered_set<int> &visited) {
    if (sommet == sommet_arrive)
        return {sommet};
    
    visited.insert(sommet);
    
    // On mélanges les arêtes pour avoir un chemin aléatoire
    std::random_shuffle(aretes.begin(), aretes.end());

    for (const auto &arete : aretes)
    {
        if (arete.partDe(sommet))
        {
            int prochain_sommet = arete.getSommet1() == sommet ? arete.getSommet2() : arete.getSommet1();
            if (visited.find(prochain_sommet) == visited.end())
            {
                auto chemin = DFS(aretes, prochain_sommet, sommet_arrive, visited);
                if (!chemin.empty())
                {
                    chemin.insert(chemin.begin(), sommet);
                    return chemin;
                }
            }
        }
    }
    
    return {};
}

/* ce code renvoie le chemin sous forme d'une suite d'aretes et non pas une suite de noeuds */
std::vector<Arete> DFS_aretes(std::vector<Arete> &aretes, int sommet, int sommet_arrive, std::unordered_set<int> &visited) {
    if (sommet == sommet_arrive)
        return {};
    
    visited.insert(sommet);
    
    // On mélanges les arêtes pour avoir un chemin aléatoire
    std::random_shuffle(aretes.begin(), aretes.end());

    for (const auto &arete : aretes)
    {
        if (arete.partDe(sommet))
        {
            int prochain_sommet = arete.getSommet1() == sommet ? arete.getSommet2() : arete.getSommet1();
            if (visited.find(prochain_sommet) == visited.end())
            {
                auto chemin = DFS_aretes(aretes, prochain_sommet, sommet_arrive, visited);
                if (!chemin.empty())
                {
                    chemin.insert(chemin.begin(), arete);
                    return chemin;
                }
            }
        }
    }
    
    return {};
}


std::vector<int> trouver_chemin_aleatoire(const GrapheAugmente &g, int sommet_depart, int sommet_arrive, bool augmenteOnly)
{
    // On initialise le générateur de nombres aléatoires de la STL
    std::srand(unsigned(std::time(0)));

    std::unordered_set<int> visited;
    std::vector<Arete> aretes = augmenteOnly ? g.getListeAreteAugmentee() : g.getListeArete();
    return DFS(aretes, sommet_depart, sommet_arrive, visited);
}

std::vector<Arete> trouver_chemin_aleatoire_aretes(const GrapheAugmente &g, int sommet_depart, int sommet_arrive, bool augmenteOnly)
{
    // On initialise le générateur de nombres aléatoires de la STL
    std::srand(unsigned(std::time(0)));

    std::unordered_set<int> visited;
    std::vector<Arete> aretes = augmenteOnly ? g.getListeAreteAugmentee() : g.getListeArete();
    return DFS_aretes(aretes, sommet_depart, sommet_arrive, visited);
}
