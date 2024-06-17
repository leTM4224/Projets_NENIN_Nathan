#include <stdlib.h>
#include <stdio.h>

/**
* \file src2.c
* \brief Programme pour calculer la somme des éléments d'un tableau
*/

//---------------| Constantes Symboliques |---------------

/**
* \def TAILLE_TABLEAU
* \brief Taille du tableau d'entiers
*/
#define TAILLE_TABLEAU 5

//---------------| Structures |---------------

/**
* \struct Point
* \brief Structure représentant un point en 2D
*/
typedef struct {
    int x; /** Coordonnée x du point */
    int y; /** Coordonnée y du point */
} Point;

/**
* \struct Etudiant
* \brief Structure représentant un étudiant
*/
typedef struct {
    char nom[50]; /** Nom de l'étudiant */
    char groupe_td; /** Groupe TD de l'étudiant */
    int num_tp; /** Numéro de groupe TP de l'étudiant (1 ou 2) */
} Etudiant;

//---------------| Prototypes |---------------

int somme_tableau(int tableau[]);

//---------------| Programme principal |---------------

/**
* \fn int main()
* \brief Fonction principale
* Cette fonction est le point d'entrée du programme. Elle appelle la fonction
* somme_tableau avec le tableau défini et affiche le résultat.
* \return int Code de sortie du programme
*/
int main() {
    /**
    * \var int tableau[TAILLE_TABLEAU]
    * \brief Tableau d'entiers pour tester la fonction de somme
    */
    int tableau[TAILLE_TABLEAU] = {1, 2, 3, 4, 5};

    printf("La somme des éléments du tableau est : %d\n", somme_tableau(tableau));

    return EXIT_SUCCESS;
}

//---------------| Fonctions |---------------

/**
* \fn int somme_tableau(int tableau[])
* \brief Calcule la somme des éléments d'un tableau d'entiers.
*
* Cette fonction prend en entrée un tableau d'entiers
* et retourne la somme de tous ses éléments.
*
* \param tableau Tableau d'entiers
* \return int Somme des éléments du tableau
*/
int somme_tableau(int tableau[]) {
    int somme = 0;

    for (int i = 0; i < TAILLE_TABLEAU; i++) {
        somme += tableau[i];
    }

    return somme;
}