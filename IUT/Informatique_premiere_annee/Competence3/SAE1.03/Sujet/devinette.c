#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
* \file devinette.c
* \brief Jeu de devinette : trouver un nombre secret dans une plage donnée.
*/

//---------------| Constantes Symboliques |---------------

/**
* \def PLAGE_MIN
* \brief Valeur minimale de la plage de nombres
*/
#define PLAGE_MIN 1

/**
* \def PLAGE_MAX
* \brief Valeur maximale de la plage de nombres
*/
#define PLAGE_MAX 100

//---------------| Prototypes |---------------

int generer_nombre_secret();
void jouer_jeu();

//---------------| Programme principal |---------------

/**
* \fn int main()
* \brief Fonction principale
* Cette fonction est le point d'entrée du programme. Elle initialise le générateur de nombres aléatoires
* et appelle la fonction jouer_jeu pour démarrer le jeu.
* \return int Code de sortie du programme
*/
int main() {
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
    jouer_jeu();       // Démarrage du jeu
    return EXIT_SUCCESS;
}

//---------------| Fonctions |---------------

/**
* \fn int generer_nombre_secret()
* \brief Génère un nombre secret aléatoire dans la plage donnée.
*
* \return int Nombre secret généré
*/
int generer_nombre_secret() {
    return rand() % (PLAGE_MAX - PLAGE_MIN + 1) + PLAGE_MIN;
}

/**
* \fn void jouer_jeu()
* \brief Fonction principale du jeu de devinette.
* L'utilisateur doit deviner un nombre secret généré aléatoirement.
*/
void jouer_jeu() {
    int nombre_secret = generer_nombre_secret();
    int tentative;
    int essais = 0;

    printf("Bienvenue dans le jeu de devinette !\n");
    printf("Trouvez le nombre secret entre %d et %d.\n", PLAGE_MIN, PLAGE_MAX);

    do {
        printf("Entrez votre proposition : ");
        scanf("%d", &tentative);

        essais++;

        if (tentative < nombre_secret) {
            printf("Le nombre secret est plus grand.\n");
        } else if (tentative > nombre_secret) {
            printf("Le nombre secret est plus petit.\n");
        } else {
            printf("Bravo ! Vous avez trouvé le nombre secret en %d essais.\n", essais);
        }

    } while (tentative != nombre_secret);

    printf("Fin du jeu. Merci d'avoir joué !\n");
}