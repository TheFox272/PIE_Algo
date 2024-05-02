# -*- coding: utf-8 -*-
"""
Ce script python permet d'extraire le graphe d'une zone circulaire autour
d'un point géographique sous le format :
    noeud_1 noeud_2 poids booleen_orientation
    
dans le fichier texte (par défaut) graphe.txt (par défaut) du répertoire
courant
"""

import osmnx as ox
import random
import networkx as nx
from shapely.geometry import Point
from pyproj import CRS, Transformer
from shapely.geometry import Polygon
from shapely.ops import transform

def transcrire_graphe(G,conversion,chemin='', nom_fichier='graphe.txt'):
    """
    Transcription du graphe sous la forme
    noeud_1 noeud_2 poids
    """
    
    memoire = []
    with open(chemin + nom_fichier, 'w') as f:
        for u,v,data in list(G.edges(data=True)):
            if not({v,u} in memoire):
                u_converti = conversion[u]
                v_converti = conversion[v]
                if(data['reversed']):
                    memoire.append({u,v})
                    f.write(f"{u_converti} {v_converti} {data['length']} 0\n")
                else:
                    f.write(f"{u_converti} {v_converti} {data['length']} 1\n")
                    
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

def graphe_depuis_cercle(lat,lon,rayon):
    """
    Renvoie le graphe de la zone délimitée (avec données OSM)
    par le cercle de centre (lat,lon) de rayon 'rayon' (en mètre)
    """
    Pl = polygone_zone_circulaire(lat, lon, rayon)
    
    network_types = 'all'
    G = ox.graph_from_polygon(Pl, network_type = network_types)
    return G

def transcrire_zone_cercle(lat, lon, rayon, conversion, chemin='',nom_fichier='graphe.txt'):
    """
    Transcrit directement le cercle de rayon = rayon, de latitude et longitude lon,lat.
    Retourne aussi le graphe
    """
    G = graphe_depuis_cercle(lat,lon,rayon)
    transcrire_graphe(G,conversion, chemin,nom_fichier)

def convertir_chemin(G,conversion,chemin='', nom_fichier='resultat_genetique.txt'):
    chemin_converti = []
    with open(chemin + nom_fichier, 'r') as f:
        for line in f.readlines():
            noeud1 = line.split()
            
            noeud1_reel = [i for i in conversion if conversion[i]==noeud1][0]
            
            lon_1 = G.nodes[noeud1_reel]['x']
            lat_1 = G.nodes[noeud1_reel]['y']
            
            chemin_converti.append([lon_1,lat_1])
            
        f.close()
        
    with open(chemin + nom_fichier, 'w') as f:
        for noeud in chemin_converti:   
            f.write(f"{noeud[0]} {noeud[1]}\n")
            
        f.close()
