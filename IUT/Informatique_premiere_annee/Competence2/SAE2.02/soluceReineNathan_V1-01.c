/**
 * @brief Optimisation du backtracking (for pour la ligne et plus pour toute la grille)
 * @version 1.01
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define N 4

typedef int grille[N][N];

bool possible(grille g, int numCase);
bool backtracking(grille g, int numCase, int nbDames);
void affichage(grille grid);
void initGrille(grille g);

int main()
{
    grille g;
    initGrille(g);

    clock_t begin = clock();

    backtracking(g, 0, 0);

    clock_t end = clock();
    double tmpsCPU = (end - begin) * 1.0 / CLOCKS_PER_SEC;

    affichage(g);
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

bool backtracking(grille g, int numCase, int nbDames)
{
    if (nbDames == N)
    {
        return true;
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            if (possible(g, (numCase + i)))
            {
                int ligne = (numCase + i) / N;
                int colonne = (numCase + i) % N;
                g[ligne][colonne] = 1;
                if (backtracking(g, numCase + N, nbDames + 1))
                {
                    return true;
                }
                else
                {
                    g[ligne][colonne] = 0;
                }
            }
        }
        return false;
    }
}

void affichage(grille grid)
{
    int ligne;
    printf("+");
    for (ligne = 0; ligne < N; ligne++)
    {
        printf("---------+");
    }
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            for (int j = 0; j < N; j++)
            {
                if (grid[i][j] == 1)
                {
                    switch (k)
                    {
                    case 0:
                        printf("|   _O_   ");
                        break;
                    case 1:
                        printf("|   \\ /   ");
                        break;
                    case 2:
                        printf("|   /_\\   ");
                        break;

                    default:
                        break;
                    }
                }

                else
                {
                    printf("|         ");
                }
            }
            printf("|\n");
        }
        printf("+");
        for (ligne = 0; ligne < N; ligne++)
        {
            printf("---------+");
        }
        printf("\n");
    }
}