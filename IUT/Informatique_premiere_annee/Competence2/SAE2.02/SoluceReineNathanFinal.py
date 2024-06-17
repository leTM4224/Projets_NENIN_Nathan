'''
Modifications : Ajout d'une fonction pour ecrire dans un fichier
Version 1.3.1
'''

import time
import copy

N = 8

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
        print("+---------", end="")
    print("+")
    for i in range(N):
        for k in range(3):
            for j in range(N):
                if grid[i][j] == 1:
                    if k == 0:
                        print("|   _O_   ", end="")
                    elif k == 1:
                        print("|   \\ /   ", end="")
                    elif k == 2:
                        print("|   /_\\   ", end="")
                    else:
                        print("|         ", end="")
                else:
                    print("|         ", end="")
            print("|")
        for k in range(N):
            print("+---------", end="")
        print("+")

def affichageMinimaliste(grid):
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

def write_file(tab):
    with open('solutions.txt', 'w') as f:
        for n in range(tab.nbSoluce):
            f.write("Solution " + str(n + 1) + ":\n")
            for k in range(N):
                f.write("+---------")
            f.write("+\n")
            for i in range(N):
                for k in range(3):
                    for j in range(N):
                        if tab.solutions[n][i][j] == 1:
                            if k == 0:
                                f.write("|   _O_   ")
                            elif k == 1:
                                f.write("|   \\ /   ")
                            elif k == 2:
                                f.write("|   /_\\   ")
                            else:
                                f.write("|         ")
                        else:
                            f.write("|         ")
                    f.write("|\n")
                for k in range(N):
                    f.write("+---------")
                f.write("+\n")
            f.write("\n")

def main():
    g = [[0] * N for i in range(N)]
    tab = TabGrille()
    tab.nbSoluce = 0

    print("Calcul des solutions...")

    begin = time.time()

    backtracking(g, tab, 0, 0)

    end = time.time()
    tmps_cpu = end - begin

    print("{} solutions trouvees\nTemps CPU : {:.3f}".format(tab.nbSoluce,tmps_cpu))

    rep=str()
    while (rep!="4"):
        print("\n1. Afficher toutes les solutions\n2. Afficher une solution\n3. Ecrire les solutions dans un fichier\n4. Quitter")
        rep=input("Entrez votre choix : ")
        
        if rep=="1":
            for i in range(tab.nbSoluce):
                print("Solution ", i + 1)
                affichage(tab.solutions[i])
        
        elif rep=="2":
            num=int(input("Entrez le numéro de la solution à afficher : "))
            if num > tab.nbSoluce or num < 1:
                print("Numéro de solution invalide !")
            else:
                print("Solution n°", num)
                affichage(tab.solutions[num-1])
        
        elif rep == "3":
            print("Ecriture des solutions dans le fichier \"solutions.txt\"...")
            write_file(tab)

        elif rep=="4":
            print("Au revoir !")
        
        else:
            print("Choix invalide !")

main()