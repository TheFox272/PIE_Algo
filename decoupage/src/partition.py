import osmnx as ox
import random
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

def partition(departs, G):
    k=len(departs)
    matrice=nx.to_numpy_array(G, weight='length')
    n=len(matrice)
    positions=[]
    nodes=G.nodes(data=True)
    for node_id, node_data in nodes:
        positions+=[node_data['y'],node_data['x']]
    distances=[0 for i in range(k)]
    for i in range(k):
        distances[i]=nx.single_source_dijkstra(G,departs[i])[0]
    attribution=[[0 for j in range(n)] for i in range(k)]
    marques=[]
    for i in range(k):
        attribution[departs[i]]=i
        marques+=[departs[i]]
    while (len(marques)!=n):
        candidats=[0 for j in range(n)]
        for i in range(k):
            candidatsg=[0 for j in range(n)]
            distcandidats=[0 for j in range(n)]
            for j in range(n):
                if(j in attribution[i]):
                    for v in range(n):
                        if ((matrice[j][v]!=0) and (marques[v]==0) and (not (v in attribution[i]))):
                            candidatsg[v]=1
            for j in len(candidatsg):
                if candidatsg[j]==1:
                    distcandidats+=dist(candidatsg(j),i,positions)
            if distcandidats!=[]:
                index=argmin(distcandidats)
                candidats[i]=[candidatsg[index],i]
            else:
                candidats[i]=-1
        index=argmin(distancestotales(candidats,attribution,matrice))
        noeud=candidats[index][0]
        marques[noeud]=1
        attribution[candidats[index]][noeud]+=1
    return attribution
    

def argmin(sequence):
    min_index, min_value = 0, sequence[0]
    for index, value in enumerate(sequence):
        if value < min_value:
            min_index, min_value = index, value
    return min_index

def dist(v,i,matrice,positions):
    rue=matrice[i][v]
    voldoiseau=np.sqrt((positions[i][0]-positions[v][0])**2+(positions[i][1]-positions[v][1])**2)
    print(rue)
    print(voldoiseau)
    return rue + voldoiseau

    
def distancestotales(candidats,attribution,matrice):
    sommerues=[]
    for i in len(candidats):
        groupe=attribution[i]+[candidats[i]]
        for noeudj in groupe:
            for noeudk in groupe:
                if noeudj>=noeudk:
                    if (matrice[noeudj][noeudk]!=0):
                        sommerues[i]+=matrice[noeudj][noeudk]
                    else:
                        sommerues[i]+=matrice[noeudj][noeudk]
    return sommerues
                


######Tests

# # Création d'un graphe vide
# G = nx.Graph()
# for i in range(1, 11):
#     # Générer des coordonnées aléatoires (latitude entre -90 et 90, longitude entre -180 et 180)
#     latitude = random.uniform(-90, 90)
#     longitude = random.uniform(-180, 180)
#     G.add_node(i)
#     G.nodes(data=True)[i]['y'] = latitude
#     G.nodes(data=True)[i]['x'] = longitude
# edges = [(1, 2), (2, 3), (3, 4), (4, 5), (1, 6), (6, 7), (7, 8), (8, 9), (9, 10), (10, 1), (5, 10), (5, 8)]
# G.add_edges_from(edges)
# nx.draw(G, with_labels=True, node_color='skyblue', node_size=700, edge_color='k', font_weight='bold')
# plt.show()
# print(partition([1,9],G))