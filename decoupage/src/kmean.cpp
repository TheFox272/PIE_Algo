/*
SQUELETTE DE L'ALGORITHME

Entrée :
- pour chaque individu, on a un noeud initial représentant la position de départ
- liste des coordonnées réelles (x,y) de chaque noeud
- matrice d'adjacence du graphe, avec -1 si non relié et la distance en mètre de la voie si relié
- nombre k d'individus
- nombre n de noeuds (intersection de route)

Sortie :
- liste de répartition des noeuds entre les k individus

Déroulé :
Initialisation des k groupes de noeuds, avec le noeud de départ de chaque groupe
Initialisation du tableau de présence dans un groupe (true or false pour chaque noeud)





*/
#include <stdlib.h>
#include <vector>

#include "kmean.hpp"

Point barycentre(Point* part, int n) {
    float xsum=(part[0]).x;
    float ysum=(part[0]).y;
    for (int i=1; i++;i<n) {
        xsum=xsum+(part[i]).x;
        ysum=ysum+(part[i]).y;
    }
    float xmoy=xsum/n;
    float ymoy=ysum/n;
    Point bary;
    bary.x=xmoy;
    bary.y=ymoy;
    return bary;
}

int* partition(int* matrice, Point* coord, int k, int n, int* departs) /*matrice = tableau n*n contenant la distance entre 2 noeuds si ils sont reliés, -1 sinon ; 
coord = tableau des coordonnées des noeuds ; k = nombre de groupes ; n = nombre de noeuds ; departs = tableau des noeuds de départs des groupes (taille k)*/
{
    int* parts = malloc(k*n*sizeof(int));
    for (int i=0; i++; i<n*k) /*Initialisation des groupes de noeuds, avec le noeud de départ de chaque groupe*/
    {
        parts[i]=-1;
    }
    for (int i=0; i++; i<k) /*Initialisation des groupes de noeuds, avec le noeud de départ de chaque groupe*/
    {
        parts[n*i]=departs[i];
    }
    bool* attrib = malloc(n*sizeof(int));
    for (int i=0; i++; i<n) /*Initialisation du tableau de présence dans un groupe*/
    {
        attrib[i]=false;
    }
    for (int i=0; i++; i<k) /*Mise à jour du tableau de présence dans un groupe*/
    {
        attrib[departs[i]]=true;
    }
    bool test=true;
    for (int i=0; i++; i<n) /*Initialisation du marqueur valant true si tous les noeuds sont attribués*/
    {
        test=test*attrib[i];
    }
    while (test==false) /*Boucle de répartition des noeuds entre les groupes*/
    {
        int noeud=-1; /*Noeud ajouté à un groupe*/
        float* distances= malloc(k*sizeof(float));
        int* candidats=malloc(k*sizeof(int));
        for (int i=0; i++;i<k) /*Boucle sur les groupes*/
        {
            float distance = 0;
            int candidat = -1;
            int j=0;
            while (parts[n*i+j]!=-1) /*Boucle sur les noeuds dans le groupe*/
            {
                int m=0;
                for (int l=0;l++;l<n)
                {
                    if (parts)
                }
                Point* groupe = malloc ;
                float maxgroupe = 0;
                for (int l=0;i=l++;l<n) /*Boucle sur les voisins de chaque noeud du groupe*/
                {
                    float maxvoisins = 0;
                    if (matrice[n*j+l]!=-1) /*Sélection des voisins du noeud*/
                    {
                        if (maxvoisins<distance(barycentre()))
                    }
                }
                j+=1;
            }
            for (int i=0; i++; i<n) /*Mise à jour du marqueur valant true si tous les noeuds sont attribués*/
            {
                test=test*attrib[i];
            }
        }
    }
    
}






