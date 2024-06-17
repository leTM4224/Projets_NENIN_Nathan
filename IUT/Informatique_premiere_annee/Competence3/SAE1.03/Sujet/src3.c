#include <stdlib.h>
#include <stdio.h>

/**
* \file max_tableau.c
* \brief Programme pour trouver le maximum dans un tableau d'entiers
*/

//---------------| Constantes Symboliques |---------------

/**
* \def TAILLE_TABLEAU
* \brief Taille du tableau d'entiers
*/
#define TAILLE_TABLEAU 8

/**
* \def NB_ETUDIANTS
* \brief Nombre d'étudiants dans le groupe
*/
#define NB_ETUDIANTS 6

//---------------| Structures |---------------

/**
* \struct Coordonnees
* \brief Structure représentant les coordonnées d'un point en 3D
*/
typedef struct {
    int x; /** Coordonnée x du point */
    int y; /** Coordonnée y du point */
    int z; /** Coordonnée z du point */
} Coordonnees;

/**
* \struct Etudiant
* \brief Structure représentant un étudiant
*/
typedef struct {
    char nom[50]; /** Nom de l'étudiant */
    char groupe_td; /** Groupe TD de l'étudiant */
    int num_tp; /** Numéro de groupe TP de l'étudiant (1 ou 2) */
    int notes[5]; /** Liste des notes de l'étudiant */
} Etudiant;

//---------------| Prototypes |---------------

int trouve_maximum(int tableau[]);

//---------------| Programme principal |---------------

/**
* \fn int main()
* \brief Fonction principale
* Cette fonction est le point d'entrée du programme. Elle appelle la fonction
* trouve_maximum avec le tableau défini et affiche le résultat.
* \return int Code de sortie du programme
*/
int main() {
    /**
    * \var int tableau[TAILLE_TABLEAU]
    * \brief Tableau d'entiers pour tester la fonction de recherche du maximum
    */
    int tableau[TAILLE_TABLEAU] = {15, 23, 7, 42, 18, 35, 29, 10};

    printf("Le maximum dans le tableau est : %d\n", trouve_maximum(tableau));

    return EXIT_SUCCESS;
}

//---------------| Fonctions |---------------

/**
* \fn int trouve_maximum(int tableau[])
* \brief Trouve le maximum dans un tableau d'entiers.
*
* Cette fonction prend en entrée un tableau d'entiers
* et retourne la valeur maximale du tableau.
*
* \param tableau Tableau d'entiers
* \return int Valeur maximale du tableau
*/
int trouve_maximum(int tableau[]) {
    int maximum = tableau[0];

    for (int i = 1; i < TAILLE_TABLEAU; i++) {
        if (tableau[i] > maximum) {
            maximum = tableau[i];
        }
    }

    return maximum;
}