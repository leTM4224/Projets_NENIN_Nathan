'''
Modifications : Prise en compte de toutes les solutions possibles et changement de l'affichage
Version 1.1
'''

import time
import copy

N = 12

class TabGrille:
    def __init__(self):
        self.nbSoluce = 0
        self.solutions = list()

def init_grille(g):
    for i in range(N):
        for j in range(N):
            g[i][j] = 0

def ajouter_solution(g, tab):
    tab.solutions.append(copy.deepcopy(g))
    tab.nbSoluce += 1

def possible(g, num_case):
    ligne = num_case // N
    colonne = num_case % N
    start_ligne = max(ligne - colonne, 0)
    start_colonne = max(colonne - ligne, 0)
    start_ligne_inv = min(ligne + colonne, N - 1)
    start_colonne_inv = max(colonne - (N - 1 - ligne), 0)

    for i in range(N):
        if g[ligne][i] == 1 or g[i][colonne] == 1:
            return False

    verif = 0
    while start_ligne + verif < N and start_colonne + verif < N:
        if g[start_ligne + verif][start_colonne + verif] == 1:
            return False
        verif += 1

    verif = 0
    while start_ligne_inv - verif >= 0 and start_colonne_inv + verif < N:
        if g[start_ligne_inv - verif][start_colonne_inv + verif] == 1:
            return False
        verif += 1

    return True

def backtracking(g, tab, ligne, nb_dames):
    if nb_dames == N:
        ajouter_solution(g, tab)
        return True
    else:
        for colonne in range(N):
            if possible(g, ligne * N + colonne):
                g[ligne][colonne] = 1
                if backtracking(g, tab, ligne + 1, nb_dames + 1):
                    g[ligne][colonne] = 0  # Annuler la modification pour tester d'autres positions
                else:
                    g[ligne][colonne] = 0  # Annuler la modification si la solution n'est pas possible
        return False

def affichage(grid):
    for k in range(N):
        print("+---", end="")
    print("+")
    for i in range(N):
        for j in range(N):
            if grid[i][j] == 1:
                print("| Q ", end="")
            else:
                print("|   ", end="")
        print("|")
        for k in range(N):
            print("+---", end="")
        print("+")

# Main
g = [[0] * N for i in range(N)]
tab = TabGrille()
tab.nbSoluce = 0

begin = time.time()

backtracking(g, tab, 0, 0)

end = time.time()
tmps_cpu = end - begin

# Affichage de toutes les solutions
for i in range(tab.nbSoluce):
        print("Solution n°", i + 1)
        affichage(tab.solutions[i])

print("Il y a {} solutions\nTemps CPU : {:.3f}".format(tab.nbSoluce,tmps_cpu))