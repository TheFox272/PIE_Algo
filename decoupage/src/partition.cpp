#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;
#include <limits>
#include <filesystem>
namespace fs = std::filesystem;

#include "partition.hpp"

// Point barycentre(Point* part, int n) {
//     float xsum=(part[0]).x;
//     float ysum=(part[0]).y;
//     for (int i=1; i++;i<n) {
//         xsum=xsum+(part[i]).x;
//         ysum=ysum+(part[i]).y;
//     }
//     float xmoy=xsum/n;
//     float ymoy=ysum/n;
//     Point bary;
//     bary.x=xmoy;
//     bary.y=ymoy;
//     return bary;
// }

// int* partition(int* matrice, Point* coord, int k, int n, int* departs) /*matrice = tableau n*n contenant la distance entre 2 noeuds si ils sont reliés, -1 sinon ; 
// coord = tableau des coordonnées des noeuds ; k = nombre de groupes ; n = nombre de noeuds ; departs = tableau des noeuds de départs des groupes (taille k)*/
// {
//     float* distances = dijkstra(matrice,departs, k, k);
//     int* parts = malloc(k*n*sizeof(int));
//     for (int i=0; i++; i<n*k) /*Initialisation des groupes de noeuds, avec le noeud de départ de chaque groupe*/
//     {
//         parts[i]=-1;
//     }
//     for (int i=0; i++; i<k) /*Initialisation des groupes de noeuds, avec le noeud de départ de chaque groupe*/
//     {
//         parts[n*i]=departs[i];
//     }
//     bool* attrib = malloc(n*sizeof(int));
//     for (int i=0; i++; i<n) /*Initialisation du tableau de présence dans un groupe*/
//     {
//         attrib[i]=false;
//     }
//     for (int i=0; i++; i<k) /*Mise à jour du tableau de présence dans un groupe*/
//     {
//         attrib[departs[i]]=true;
//     }
//     bool test=true;
//     for (int i=0; i++; i<n) /*Initialisation du marqueur valant true si tous les noeuds sont attribués*/
//     {
//         test=test*attrib[i];
//     }
//     while (test==false) /*Boucle de répartition des noeuds entre les groupes*/
//     {
//         int noeud=-1; /*Noeud ajouté à un groupe*/
//         float* distancescandidats= malloc(k*sizeof(float));
//         int* candidats=malloc(k*sizeof(int));
//         for (int i=0; i++;i<k) /*Boucle sur les groupes*/
//         {
//             float distance = 0;
//             int candidat = -1;
//             int j=0;
//             while (parts[n*i+j]!=-1) /*Boucle sur les noeuds dans le groupe*/
//             {
//                 int m=0;
//                 for (int l=0;l++;l<n)
//                 {
//                     if (parts)
//                 }
//                 Point* groupe = malloc ;
//                 float maxgroupe = 0;
//                 for (int l=0;i=l++;l<n) /*Boucle sur les voisins de chaque noeud du groupe*/
//                 {
//                     float maxvoisins = 0;
//                     if (matrice[n*j+l]!=-1) /*Sélection des voisins du noeud*/
//                     {
//                         if (maxvoisins<distance(barycentre()))
//                     }
//                 }
//                 j+=1;
//                 int j =
//             }
//         }
//         for (int i=0; i++; i<n) /*Mise à jour du marqueur valant true si tous les noeuds sont attribués*/
//         {
//             test=test*attrib[i];
//         }
//     }
    
// }

vector<vector<float>> dijkstra(vector<vector<int>> matrice, vector<int> departs, int n, int k)
{
    vector<vector<float>> distances(n*k);
    for (int i=0; i<k; i++)
    {
        fill(distances[i].begin(), distances[i].end(), numeric_limits<float>::infinity()); /*Initialisation des distances aux k points de départ*/
        distances[n][departs[i]]=0; /*Initialisation à 0 des distances des k points de départ à eux-mêmes*/
    }
    for (int i=0; i<k;i++)
    {
        cout <<"test"<< endl;
        vector<int> marques(n);
        for (int j=0;j<n;j++)
        {
            marques[j]=0;
        }
        marques[departs[i]]=1;
        int somme=1;
        while (somme!=n)
        {
            float mini=numeric_limits<float>::infinity();
            int sommet=-1;
            for (int s=0; s<n; s++)
            {
                if ((marques[s]!=1)&&(matrice[i][s]<mini)&&(matrice[i][s]!=-1)) 
                {
                    mini=matrice[i][s];
                    sommet=s;
                }
            }
            marques[sommet]=1;
            for (int v=0; v<n; v++)
            {
                if ((marques[v]!=1)&&(matrice[v][sommet]!=-1)) 
                {
                    if (distances[i][v]>distances[i][sommet]+matrice[v][sommet])
                    {
                        distances[i][v]=distances[i][sommet]+matrice[v][sommet];
                    }
                }
            }
            somme=0;
            for (int j=0; j<n; j++)
            {
                somme+=marques[j];
            }
        }
    }
    return distances;
}

int main()
{
    vector<vector<int>> matrice{{-1,2,7,1,-1},{2,-1,3,-1,-1},{7,3,-1,1,2},{1,-1,1,-1,-1},{-1,-1,2,-1,-1}};
    vector<int> departs{0};
    vector<vector<float>> distances=dijkstra(matrice,departs,5,1);
    int taille = sizeof(distances);
    for (int i = 0; i<taille; i++) {
        cout << "Elément à l'index " << i << " : " << distances[i] << endl;
    }
return 0;
}

