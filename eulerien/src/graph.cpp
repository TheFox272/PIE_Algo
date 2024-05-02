# include "graph.hpp"

/*----------------------------------------------------------------------------------------------------*/
// Constantes

/*----------------------------------------------------------------------------------------------------*/

// CLASSE ARETE
// Constructeurs
Arete::Arete(): m_sommet1(0), m_sommet2(0), m_poids(0), m_oriente(false) {}

Arete::Arete(const int sommet1, const int sommet2, const int poids, const bool oriente): m_sommet1(sommet1), m_sommet2(sommet2), m_poids(poids), m_oriente(oriente) {}

Arete::Arete(const Arete& autre): m_sommet1(autre.m_sommet1), m_sommet2(autre.m_sommet2), m_poids(autre.m_poids), m_oriente(autre.m_oriente) {}

// Destructeur
Arete::~Arete() {}

// Méthodes
int Arete::getSommet1() const { return m_sommet1; }

int Arete::getSommet2() const { return m_sommet2; }

int Arete::getPoids() const { return m_poids; }

bool Arete::getOriente() const { return m_oriente; }

void Arete::setOriente(bool oriente) { m_oriente = oriente; }

bool Arete::partDe(const int sommet) const
{
    return (m_sommet1 == sommet || (m_sommet2 == sommet && m_oriente == false));
}

bool Arete::vaVers(const int sommet) const
{
    return (m_sommet2 == sommet || (m_sommet1 == sommet && m_oriente == false));
}

bool Arete::incident(const int sommet) const
{
    return m_sommet1 == sommet || m_sommet2 == sommet;
}

int Arete::sommetOppose(const int sommet) const
{
    if (m_sommet1 == sommet)
        return m_sommet2;
    else if (m_sommet2 == sommet)
        return m_sommet1;
    else
    {
        std::cerr << "Le sommet " << sommet << " n'est pas sur l'arête " << m_sommet1 << " - " << m_sommet2 << std::endl;
        return -1;
    }
}

bool Arete::estNulle() const
{
    return m_sommet1 == m_sommet2;
}

bool Arete::operator == (const Arete& autre) const
{
    if (m_poids != autre.m_poids)
        return false;
    // On ne tient pas compte de l'orientation des arêtes, volontairement (les arêtes augmentées sont parfois orientées alors que l'arête d'origine ne l'était pas)
    if (m_oriente && autre.m_oriente)
        return m_sommet1 == autre.m_sommet1 && m_sommet2 == autre.m_sommet2;
    else
        return (m_sommet1 == autre.m_sommet1 && m_sommet2 == autre.m_sommet2) || (m_sommet1 == autre.m_sommet2 && m_sommet2 == autre.m_sommet1);
}

// bool Arete::operator == (const Arete& autre) const
// {
//     if (m_oriente != autre.m_oriente || m_poids != autre.m_poids)
//         return false;
//     if (m_oriente)
//         return m_sommet1 == autre.m_sommet1 && m_sommet2 == autre.m_sommet2;
//     else
//         return (m_sommet1 == autre.m_sommet1 && m_sommet2 == autre.m_sommet2) || (m_sommet1 == autre.m_sommet2 && m_sommet2 == autre.m_sommet1);
// }

bool Arete::operator != (const Arete& autre) const
{
    return !(*this == autre);
}

Arete Arete::operator - () const
{
    return Arete(m_sommet2, m_sommet1, m_poids, m_oriente);
}


// CLASSE Graphe
// Constructeurs
Graphe::Graphe(): m_nbSommet(0), m_nbArete(0), m_poidsTot(0) {}

Graphe::Graphe(Graphe const &g): m_nbSommet(g.m_nbSommet), m_nbArete(g.m_nbArete), m_poidsTot(g.m_poidsTot), m_listeSommet(g.m_listeSommet), m_listeArete(g.m_listeArete), m_matriceAdj(g.m_matriceAdj) {}

// Destructeur
Graphe::~Graphe() {}

// Méthodes
size_t Graphe::getNbSommet() const { return m_nbSommet; }

size_t Graphe::getNbArete() const { return m_nbArete; }

int Graphe::getPoidsTot() const { return m_poidsTot; }

std::vector<int> Graphe::getListeSommet() const { return m_listeSommet; }

std::vector<Arete> Graphe::getListeArete() const { return m_listeArete; }

std::vector<std::vector<std::pair<int, int>>> Graphe::getMatriceAdj() const { return m_matriceAdj; }

void Graphe::ajouterSommet(int sommet)
{
    if (std::find(m_listeSommet.begin(), m_listeSommet.end(), sommet) == m_listeSommet.end())
    {
        m_listeSommet.push_back(sommet);
        for (size_t i = 0; i < m_nbSommet; i++)
        {
            m_matriceAdj[i].push_back(std::make_pair(0, 0));
        }
        m_nbSommet++;
        m_matriceAdj.push_back(std::vector<std::pair<int, int>>(m_nbSommet, std::make_pair(0, 0)));
    }
}

void Graphe::ajouterArete(int sommet1, int sommet2, int poids, bool oriente)
{
    m_listeArete.push_back(Arete(sommet1, sommet2, poids, oriente));
    m_nbArete++;
    m_poidsTot += poids;
    ajouterSommet(sommet1);
    ajouterSommet(sommet2);
    
    // On met à jour la matrice d'adjacence
    int i = std::find(m_listeSommet.begin(), m_listeSommet.end(), sommet1) - m_listeSommet.begin();
    int j = std::find(m_listeSommet.begin(), m_listeSommet.end(), sommet2) - m_listeSommet.begin();
    m_matriceAdj[i][j].first = poids;
    m_matriceAdj[i][j].second++;
    if (!oriente)
    {
        m_matriceAdj[j][i].first = poids;
        m_matriceAdj[j][i].second++;
    }
}

void Graphe::ajouterArete(Arete arete)
{
    ajouterArete(arete.getSommet1(), arete.getSommet2(), arete.getPoids(), arete.getOriente());
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

void Graphe::afficherListeSommets() const
{
    for(int sommet : m_listeSommet)
    {
        std::cout << sommet << ";";
    }
    std::cout << std::endl;
}
void Graphe::afficherMatriceAdj() const
{
    int n = m_matriceAdj.size();

    for(int i = 0; i<n; ++i)
    {
        for(int j = 0; j<n; ++j)
        {
            std::cout << "(" << m_matriceAdj[i][j].first << "," << m_matriceAdj[i][j].second << ")" << " ";
        }
        std::cout << std::endl;
    }
}

// CLASSE GrapheAugmente
// Constructeurs
GrapheAugmente::GrapheAugmente(): Graphe(), m_nbAreteAugmente(0), m_poidsTotAugmente(0) {}
GrapheAugmente::GrapheAugmente(Graphe g): Graphe(g), m_nbAreteAugmente(0), m_poidsTotAugmente(0) {}
GrapheAugmente::GrapheAugmente(GrapheAugmente const &g, bool copieAreteAugmente): Graphe(g)
{
    m_listeAreteAugmente = g.m_listeAreteAugmente;
    if (copieAreteAugmente)
    {
        m_nbAreteAugmente = g.m_nbAreteAugmente;
        m_poidsTotAugmente = g.m_poidsTotAugmente;
    }
    else
    {
        m_nbAreteAugmente = 0;
        m_poidsTotAugmente = 0;
        // on supprime les arêtes augmentées
        for (Arete arete : g.getListeAreteAugmentee())
        {
            supprimerAreteAugmentee(arete);
        }
    }

}

// Destructeur
GrapheAugmente::~GrapheAugmente() {}

// Méthodes
int GrapheAugmente::getPoidsTotAugmente() const { return m_poidsTotAugmente; }

std::vector<Arete> GrapheAugmente::getListeAreteAugmentee() const { return m_listeAreteAugmente; }

std::vector<Arete> GrapheAugmente::getListeAreteTotale() const
{
    std::vector<Arete> listeAreteTotale = m_listeArete;
    listeAreteTotale.insert(listeAreteTotale.end(), m_listeAreteAugmente.begin(), m_listeAreteAugmente.end());
    return listeAreteTotale;
}

std::vector<Arete> GrapheAugmente::getCheminEulerien() const { return m_cheminEulerien; }

void GrapheAugmente::ajouterAreteAugmentee(Arete arete)
{
    m_listeAreteAugmente.push_back(arete);
    m_poidsTotAugmente += arete.getPoids();
    m_nbAreteAugmente++;

    // On met à jour la matrice d'adjacence
    int i = std::find(m_listeSommet.begin(), m_listeSommet.end(), arete.getSommet1()) - m_listeSommet.begin();
    int j = std::find(m_listeSommet.begin(), m_listeSommet.end(), arete.getSommet2()) - m_listeSommet.begin();
    m_matriceAdj[i][j].second++;
    if (!arete.getOriente())
    {
        m_matriceAdj[j][i].second++;
    }
}

void GrapheAugmente::ajouterAreteAugmentee(int sommet1, int sommet2, int poids, bool oriente)
{
    Arete arete(sommet1, sommet2, poids, oriente);
    ajouterAreteAugmentee(arete);
}

void GrapheAugmente::supprimerAreteAugmentee(Arete arete)
{
    // On utilise les fonctions de vector pour supprimer l'arête
    auto it = std::find(m_listeAreteAugmente.begin(), m_listeAreteAugmente.end(), arete);
    if (it != m_listeAreteAugmente.end())
    {
        m_poidsTotAugmente -= it->getPoids();
        m_listeAreteAugmente.erase(it);
        m_nbAreteAugmente--;

        // On met à jour la matrice d'adjacence
        int i = std::find(m_listeSommet.begin(), m_listeSommet.end(), arete.getSommet1()) - m_listeSommet.begin();
        int j = std::find(m_listeSommet.begin(), m_listeSommet.end(), arete.getSommet2()) - m_listeSommet.begin();
        m_matriceAdj[i][j].second--;
        if (!arete.getOriente())
        {
            m_matriceAdj[j][i].second--;
        }

        return;
    }

    // debug
    std::cout << "arete non trouvee " << arete.getSommet1() << "->" << arete.getSommet2() << " " << arete.getPoids() << std::endl;

    // Si l'arête n'a pas été trouvée, on lève une exception
    throw std::invalid_argument("L'arête n'a pas été trouvée dans la liste des arêtes augmentées");
}

void GrapheAugmente::setCheminEulerien(std::vector<Arete> chemin)
{
    m_cheminEulerien = chemin;
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

    if (m_nbAreteAugmente == 0)
        std::cout << "Aucune (graphe déjà eulérien ?)" << std::endl;
}

/*----------------------------------------------------------------------------------------------------*/
// Fonctions

std::vector<Arete> DFS(std::vector<Arete> aretes, int sommet_actuel, int sommet_arrive, std::unordered_set<int> &visited) {
    // Si on est arrivé à destination, on renvoie une arête nulle (pour indiquer qu'on a trouvé le sommet)
    if (sommet_actuel == sommet_arrive)
    {
        // Si on n'a pas visité de sommets, on renvoie un vecteur vide
        if (visited.empty())
            return {};
        // Sinon, on renvoie une arête nulle pour que le DFS sait qu'on a trouvé le sommet
        Arete endArete = Arete();
        return {endArete};
    }
    
    // On ajoute le sommet actuel à la liste des sommets visités
    visited.insert(sommet_actuel);
    
    // On mélanges les arêtes pour avoir un chemin aléatoire
    std::random_shuffle(aretes.begin(), aretes.end());

    for (const Arete &arete : aretes)
    {
        if (arete.partDe(sommet_actuel))
        {
            int prochain_sommet = arete.sommetOppose(sommet_actuel);
            // On fait une copie de l'arête actuelle, en la directionnant vers le sommet suivant (sens dans lequel on la parcourt)
            Arete arete_actuelle(sommet_actuel, prochain_sommet, arete.getPoids(), true);
            // Arete arete_actuelle = arete;

            // Si le sommet suivant n'a pas été visité, on continue le DFS
            if (visited.find(prochain_sommet) == visited.end())
            {
                std::vector<Arete> chemin = DFS(aretes, prochain_sommet, sommet_arrive, visited);
                if (!chemin.empty())
                {
                    // Si on a trouvé le sommet d'arrivée, on renvoie le chemin (attention à ne pas ajouter l'arête nulle)
                    if (chemin[0].estNulle())
                        chemin.erase(chemin.begin());
                    chemin.insert(chemin.begin(), arete_actuelle);
                    return chemin;
                }
            }
        }
    }
    
    return {};
}


std::vector<Arete> trouver_chemin_aleatoire(const GrapheAugmente &g, int sommet_depart, int sommet_arrive, bool augmenteOnly)
{
    if (sommet_depart == sommet_arrive)
        return {};

    // On initialise le générateur de nombres aléatoires de la STL
    std::srand(unsigned(std::time(0)));

    std::unordered_set<int> visited;
    std::vector<Arete> aretes = augmenteOnly ? g.getListeAreteAugmentee() : g.getListeArete();
    return DFS(aretes, sommet_depart, sommet_arrive, visited);
}

/*----------------------------------------------------------------------------------------------------*/

void afficher_chemin(const std::vector<Arete> &chemin)
{
    if (chemin.empty())
    {
        std::cout << "{}" << std::endl;
    }
    else
    {
        for (size_t i = 0; i < chemin.size(); i++)
        {
            std::cout << chemin[i].getSommet1() << (chemin[i].getOriente() ? "->" : "<>") << chemin[i].getSommet2() << " ";
        }
    }
    std::cout << std::endl;
}
