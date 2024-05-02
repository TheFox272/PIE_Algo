# -*- coding: utf-8 -*-
"""
Created on Thu May  2 19:09:06 2024

@author: mayeu
"""

import extraction as extrac
import decoupage
import random
import networkx as nx

# Exemple : Paris, centré sur l'île de la cité
lat = 48.8566
lon = 2.3522
rayon = 1000 # 1km

"""
#Exemple : Massy
lat = 48.73000566819985
lon = 2.269128132274682
rayon = 1000 # 1km
"""

#transcription du graphe de la zone original
G = extrac.graphe_depuis_cercle(lat, lon, rayon)

#exemple de noeuds départs:
noeuds = list(G.nodes)
nbre_noeuds = len(noeuds)

depart_1 = random.choice(noeuds)
depart_2 = random.choice(noeuds)
depart_3 = random.choice(noeuds)

#extraction des composantes connnexes du graphe
composantes = list(nx.strongly_connected_components(G))

#graphe de la zone plus grande
delta = rayon
G_etendu = extrac.graphe_depuis_cercle(lat, lon, rayon+delta)
composantes_etendu = list(nx.strongly_connected_components(G_etendu))

#on supprime les noeuds injoinables
for composante_etendu in composantes_etendu:
    if composante_etendu in composantes:
        if(len(composante_etendu)==1):
            G.remove_node(list(composante_etendu)[0])
            
#on recalcule la composante "utile" :
composantes = list(nx.strongly_connected_components(G))

# on affiche le resultat, voir si ça a bien marché
node_color = [0 for node in G.nodes]
composantes_unitaire = []
for composante in composantes:
    if(len(composante)==1):
        composantes_unitaire.append(list(composante)[0])

nodes = list(G.nodes)
for i in range(len(node_color)):
    if(nodes[i] in composantes_unitaire):
        node_color[i] = 200

#on recupere la liste des representants de chaque composante connexe
liste_representants = []
for composante in composantes:
    representant = random.choice(list(composante))
    liste_representants.append(representant)

#on recupere les chemins reliant ces composantes connexes
liste_chemins=[]
for i in range(len(liste_representants)):
    dij = nx.single_source_dijkstra(G_etendu,liste_representants[i])
    
    liste_chemins.append([])
    for j in range(len(liste_representants)):
        (liste_chemins[i]).append(dij[1][liste_representants[j]])

# on ajoute ces chemins au graphe G (on ajoute les aretes
# qui à l'origine n'était pas là)
for i in range(len(liste_representants)):
    
    for j in range(i+1, len(liste_representants)):
        for k in range(len(liste_chemins[i][j])):
            noeud1 = liste_chemins[i][j][k-1]
            noeud2 = liste_chemins[i][j][k]
            
            edge_data = G_etendu.get_edge_data(noeud1, noeud2)
            
            if (not G.has_edge(noeud1,noeud2)):
                if edge_data:
                    G.add_node(noeud1)
                    
                    noeud1_keywords = G_etendu.nodes(data=True)[noeud1]
                    for cle in noeud1_keywords:
                        G.nodes(data = True)[noeud1][cle] = G_etendu.nodes(data=True)[noeud1][cle]
                    
                    G.add_node(noeud2)
                    
                    noeud2_keywords = G_etendu.nodes(data=True)[noeud2]
                    for cle in noeud2_keywords:
                        G.nodes(data = True)[noeud2][cle] = G_etendu.nodes(data=True)[noeud2][cle]
                    
                    G.add_edge(noeud1, noeud2,**(edge_data[0]))
"""
# Visualiser le graphe
ox.plot_graph(G)
plt.show()
"""

conversion = {}
nodes = list(G.nodes)
for i in range(len(nodes)):
    conversion[nodes[i]] = i

liste_graphes = decoupage.partition(G,departs)

for i in range(len(liste_graphes)):
    graphe = liste_graphes[i]
    extrac.transcrire_graphe(G, conversion,nom_fichier=f"graphe_{i}")
