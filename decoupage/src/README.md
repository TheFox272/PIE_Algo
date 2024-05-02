##### SQUELETTE DE L'ALGORITHME DE PARTITIONNEMENT

### Entrée :
- pour chaque individu, on a un noeud initial représentant la position de départ
- liste des coordonnées réelles (x,y) de chaque noeud
- matrice d'adjacence du graphe, avec -1 si non relié et la distance en mètre de la voie si relié
- nombre k d'individus
- nombre n de noeuds (intersection de route)

### Sortie :
- liste de répartition des noeuds entre les k individus

### Déroulé :
Initialiser le tableau d'attribution des noeuds dans les k groupes (avec le noeud de départ de chaque groupe)
Initialiser le vecteur de présence dans un groupe
_Tant que_ tous les noeuds ne sont pas attribués à un groupe (taille du vecteur de présence inférieure à n) :
    _Pour_ chaque groupe g :
        _Pour_ chaque noeud N du groupe g :
            _Pour_ chaque noeud voisin v du noeud N qui n'est pas déjà dans un groupe :
                Ajouter le voisin à une liste de candidats potentiels
        Calculer la "distance" de chaque v au groupe g
        Retenir le voisin v* minimisant cette distance comme candidat de g
    Retenir le candidat minimisant cette distance parmi tous les groupes
    Ajouter ce noeud au groupe lié
    Mettre à jour le tableau de présence
    Mettre à jour le tableau d'attribution en ajoutant le noeud sélectionné
Retourner le tableau d'attribution des noeuds






