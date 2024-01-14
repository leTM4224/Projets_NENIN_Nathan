#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define N 4
#define TAILLE (N*N)

typedef int tGrille[TAILLE][TAILLE];

void chargerGrille(tGrille grille);

bool absentSurLigne(int valeur, tGrille grille, int ligne);
bool absentSurColonne(int valeur, tGrille grille, int colonne);
bool absentSurBloc(int valeur, tGrille grille, int ligne, int colonne);

bool backtracking(tGrille grille, int numeroCase);

void afficherGrille(tGrille grille);

int main(){
    tGrille grilleSudoku;

    chargerGrille(grilleSudoku);

    afficherGrille(grilleSudoku);

    clock_t begin=clock();

    backtracking(grilleSudoku, 0);

    clock_t end=clock();
    double tmpsCPU = (end - begin)*1.0 / CLOCKS_PER_SEC;

    afficherGrille(grilleSudoku);
    printf( "\nTemps CPU = %.3f secondes\n",tmpsCPU);

    return EXIT_SUCCESS;
}

void chargerGrille(tGrille grille){
    char nomFichier[30];
    FILE *f;

    do{
        printf("Nom du fichier ? : ");
        scanf(" %s", nomFichier);
        f=fopen(nomFichier, "rb");

        if (f==NULL){
            printf("Erreur sur le fichier\n", nomFichier);
        }
        else{
            fread(grille, sizeof(int), TAILLE*TAILLE, f);
        }

        fclose(f);

    } while (f==NULL);
}

bool absentSurLigne(int valeur, tGrille grille, int ligne){
    for (int caseLigne=0; caseLigne<TAILLE; caseLigne++){
        if (grille[ligne][caseLigne]==valeur){
            return false;
        }
    }

    return true;
}

bool absentSurColonne(int valeur, tGrille grille, int colonne){
    for (int caseColonne=0; caseColonne<TAILLE; caseColonne++){
        if (grille[caseColonne][colonne]==valeur){
            return false;
        }
    }

    return true;
}

bool absentSurBloc(int valeur, tGrille grille, int ligne, int colonne){
    int startLigne = ligne - (ligne % N); /* Premiere ligne de la sous-case */
    int startColonne = colonne - (colonne % N); /* Premiere colonne de la sous-case */

    for (int lig = 0; lig < N; lig++)
    {
        if ((lig>=startLigne) && (lig<(startLigne+N))){

            for (int col=0; col<N; col++){
                if (grille[lig][col + startColonne] == valeur)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool backtracking(tGrille grille, int numeroCase){
    int ligne, colonne;
    bool resultat;

    resultat=false;
    if (numeroCase==(TAILLE*TAILLE)){
        resultat=true;
    }
    else{
        ligne=numeroCase/TAILLE;
        colonne=numeroCase%TAILLE;
        if (grille[ligne][colonne]!=0){
            resultat=backtracking(grille, numeroCase+1);
        }
        else{
            for (int valeur=1; valeur<=TAILLE; valeur++){
                if (absentSurLigne(valeur, grille, ligne) && absentSurColonne(valeur, grille, colonne) && absentSurBloc(valeur, grille, ligne, colonne)){
                    grille[ligne][colonne]=valeur;

                    if (backtracking(grille, numeroCase+1)){
                        resultat=true;
                    }
                    else{
                        grille[ligne][colonne]=0;
                    }
                }
            }
        }
    }

    return resultat;
}

void afficherGrille(tGrille grille){

    // Affichage des numéros de colonne
    printf("\n   ");
    for (int colCase = 0; colCase < N; colCase++) { // N sous_cases
        for (int numCase = 0; numCase < N; numCase++){ // N colonnes de la sous_case
            printf(" %d ", (numCase+1)+(N*colCase));
        }

        printf(" ");
    }

    // Affichage du contenu de la grille
    for (int ligneCase=0; ligneCase<N; ligneCase++){ // N sous_cases

        // Affichage des bords horizontaux
        printf("\n   +");

        for (int colCase = 0; colCase < N; colCase++){

            for (int numCase = 0; numCase < N; numCase++) {
                printf("----");
            }

            printf("+");
        }

        for (int ligne=0; ligne<N; ligne++){ // N lignes de la sous_case

            printf("\n");

            // Affichage du numéro de ligne
            if ((ligne+1)+(3*ligneCase) < 10){
                printf(" ");
            }
            printf("%d |", (ligne+1)+(3*ligneCase));

            for (int valCase = 0; valCase<N; valCase++){ // N sous_cases

                for (int val = 0; val < N; val++){ // N valeurs de la ligne de la sous-cases
                    if (grille[ligne+(3*ligneCase)][val+(3*valCase)] < 10){
                        printf(" ");
                    }

                    // Affichage de la valeur (ou d'un point si la case est vide)
                    if (grille[ligne+(3*ligneCase)][val+(3*valCase)] == 0){
                        printf(" . ");
                    }
                    else{
                        printf(" %d ", grille[ligne+(3*ligneCase)][val+(3*valCase)]);
                    }
                }

                printf("|"); // Affichage des bords verticaux
            }
        }
            
    }

    // Affichage du bord inférieur de la grille
    printf("\n   +");

    for (int colCase = 0; colCase < N; colCase++){

        for (int numCase = 0; numCase < N; numCase++) {
            printf("----");
        }

        printf("+");
    }
}