# -*- coding: utf-8 -*-
"""
Ce script python permet d'extraire le graphe d'une zone circulaire autour
d'un point géographique sous le format :
    noeud_1 noeud_2 poids
    
dans le fichier texte (par défaut) graphe.txt (par défaut) du répertoire
courant
"""

import sys
import osmnx as ox
import random
import networkx as nx
import matplotlib.pyplot as plt
from shapely.geometry import Point
from pyproj import CRS, Transformer
from shapely.geometry import Polygon
from shapely.ops import transform


def dfs(graphe,depart, noeuds_visite):

    noeuds_visite.add(depart)
    print(depart)  # Afficher le nœud visité
    for noeud_suivant in graphe[depart]:
        if noeud_suivant not in noeuds_visite:
            dfs(graphe, noeud_suivant, noeuds_visite)

def graphe_est_connexe(graphe):
    noeuds_visite = set()
    depart = random.choice(list(G.nodes()))
    dfs(graphe, depart,noeuds_visite)
    
    if(len(list(graphe.nodes()))== len(noeuds_visite)):
        return True
    else:
        return False

def agrandir_pour_connexe(lat, lon, rayon, eps=10):
    Pl = polygone_zone_circulaire(lat, lon, rayon)
    graphe = ox.graph_from_polygon(Pl)
    
    rayon_decale = rayon
    while(not graphe_est_connexe(graphe)):
        rayon_decale = rayon_decale + eps
        Pl = polygone_zone_circulaire(lat, lon, rayon_decale)
        graphe = ox.graph_from_polygon(Pl)
    
    return graphe
        

def graphe_depuis_point(point_centre, radius):
    """
    Graphe carré autour d'un point
    """
    center_point = (48.8566, 2.3522)  # Exemple : Paris
    radius = 1000
    
    G = ox.graph_from_point(center_point, dist=radius)
    ox.plot_graph(G, figsize=(10, 10), bgcolor='w')
    
    return G

def transcrire_graphe(G,chemin='', nom_fichier='graphe.txt'):
    """
    Transcription du graphe sous la forme
    noeud_1 noeud_2 poids
    """
    with open(chemin + nom_fichier, 'w') as f:
        for u,v,data in G.edges(data=True):
            f.write(f"{u} {v} {data['length']} 1\n")
            
def polygone_zone_circulaire(lat, lon, rayon):
    """
    Créer un cercle à partir du point de latitude = lat, longitude = lon
    et de rayon = rayon !(en mètre)!
    """
    # Azimuthal equidistant projection
    aeqd_proj = CRS.from_proj4(f"+proj=aeqd +lat_0={lat} +lon_0={lon} +x_0=0 +y_0=0")
    tfmr = Transformer.from_proj(aeqd_proj, aeqd_proj.geodetic_crs)
    buf = Point(0, 0).buffer(rayon)  # distance in miles
    return Polygon(transform(tfmr.transform, buf).exterior.coords[:])

def transcrire_zone_cercle(lat, lon, rayon, chemin='',nom_fichier='graphe.txt'):
    """
    Transcrit directement le cercle de rayon = rayon, de latitude et longitude lon,lat.
    Retourne aussi le graphe
    """
    Pl = polygone_zone_circulaire(lat, lon, rayon)
    G = ox.graph_from_polygon(Pl)
    transcrire_graphe(G,chemin,nom_fichier)
    
    return G

# Exemple : Paris, centré sur l'île de la cité
lat = 48.8566
lon = 2.3522 
rayon = 1000 # 1km

#transcription du graphe 
G = transcrire_zone_cercle(lat, lon, rayon)

# Visualiser le graphe extrait
ox.plot_graph(G, figsize=(10,10), bgcolor='w')
plt.show()
"""
def main(lat, lon, rayon):
    # Exemple : Paris, centré sur l'île de la cité
    lat = 48.8566
    lon = 2.3522 
    rayon = 1000 # 1km

    #transcription du graphe 
    G = transcrire_zone_cercle(lat, lon, rayon)

    # Visualiser le graphe extrait
    ox.plot_graph(G, figsize=(10,10), bgcolor='w')
    plt.show()

if __name__ == "__main__":
    #Pour lancer le script python de manière
    #externe extraction.py lon lat rayon
    
    # Vérifiez si les trois arguments ont été fournis
    if len(sys.argv) != 4:
        print("Usage: python main.py <a> <b> <c>")
        sys.exit(1)
    
    # Récupérez les arguments de la ligne de commande
    lat = sys.argv[1]
    lon = sys.argv[2]
    rayon = sys.argv[3]

    main(lon, lat, rayon)
"""