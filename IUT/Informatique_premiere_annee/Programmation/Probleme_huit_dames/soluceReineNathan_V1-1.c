/**
 * @brief Prise en compte de toutes les solutions possibles et changement de l'affichage
 * @version 1.1
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define N 8

typedef int grille[N][N];

typedef struct
{
    int nbSoluce;
    grille solutions[100]; // (N*0.143)^N ? -> nbSolutions à revoir
} tabGrille;

bool possible(grille g, int numCase);
bool backtracking(grille g, tabGrille *tab, int numCase, int nbDames);
void affichage(grille grid);
void initGrille(grille g);
void ajouterSolution(grille g, tabGrille *tab);

int main()
{
    grille g;
    tabGrille tab; // tabGrille contient toutes les solutions
    tab.nbSoluce = 0;
    initGrille(g);

    clock_t begin = clock();

    backtracking(g, &tab, 0, 0);

    clock_t end = clock();
    double tmpsCPU = (end - begin) * 1.0 / CLOCKS_PER_SEC;

    // Affichage des solutions
    for (int i = 0; i < tab.nbSoluce; i++)
    {
        printf("Solution %d :\n", i + 1);
        affichage(tab.solutions[i]);
    }

    printf("Temps CPU : %.3f s\n", tmpsCPU);

    return EXIT_SUCCESS;
}

void initGrille(grille g)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            g[i][j] = 0;
        }
    }
}

void ajouterSolution(grille g, tabGrille *tab)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            tab->solutions[tab->nbSoluce][i][j] = g[i][j];
        }
    }
    tab->nbSoluce++;
}

bool possible(grille g, int numCase)
{
    int ligne = numCase / N;
    int colonne = numCase % N;
    int startLigne, startColonne, startLigneInv, startColonneInv;
    // vérifie si le chiffre 1 est présent dans la ligne, la colonne ou les diagonales
    for (int i = 0; i < N; i++)
    {
        if (g[ligne][i] == 1 || g[i][colonne] == 1)
        {
            return false;
        }
    }
    // verification des diagonales
    if (ligne - colonne < 0)
    {
        startLigne = 0;
    }
    else
    {
        startLigne = ligne - colonne;
    }

    if (colonne - ligne < 0)
    {
        startColonne = 0;
    }
    else
    {
        startColonne = colonne - ligne;
    }

    if (ligne + colonne >= N)
    {
        startLigneInv = N - 1;
    }
    else
    {
        startLigneInv = ligne + colonne;
    }

    if (colonne - ((N - 1) - ligne) < 0)
    {
        startColonneInv = 0;
    }
    else
    {
        startColonneInv = colonne - ((N - 1) - ligne);
    }

    int verif = 0;

    // Diagonale haut gauche / bas droite
    while ((startLigne + verif < N && startColonne + verif < N))
    {
        if (g[startLigne + verif][startColonne + verif] == 1)
        {
            return false;
        }
        verif++;
    }

    verif = 0;

    // Diagonale bas gauche / haut droite
    while (startLigneInv - verif >= 0 && startColonneInv + verif < N)
    {
        if (g[startLigneInv - verif][startColonneInv + verif] == 1)
        {
            return false;
        }
        verif++;
    }
    return true;
}

bool backtracking(grille g, tabGrille *tab, int ligne, int nbDames)
{
    if (nbDames == N)
    {
        ajouterSolution(g, tab);
        return true;
    }
    else
    {
        for (int colonne = 0; colonne < N; colonne++)
        {
            if (possible(g, ligne * N + colonne))
            {
                g[ligne][colonne] = 1;
                if (backtracking(g, tab, ligne + 1, nbDames + 1))
                {
                    g[ligne][colonne] = 0; // Annuler la modification pour tester d'autres positions
                }
                else
                {
                    g[ligne][colonne] = 0; // Annuler la modification si la solution n'est pas possible
                }
            }
        }
        return false;
    }
}

void affichage(grille grid)
{
    for (int k = 0; k < N; k++)
    {
        printf("+---");
    }
    printf("+\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (grid[i][j] == 1)
            {
                printf("| Q ");
            }

            else
            {
                printf("|   ");
            }
        }
        printf("|\n");
        for (int k = 0; k < N; k++)
        {
            printf("+---");
        }
        printf("+\n");
    }
}