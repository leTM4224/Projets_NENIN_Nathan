/**
 * @brief Programme qui auto-complete une grille de sudoku en cherchant des singletons
 * 
 * @authors @leTM4224 @Paul-Elouan
 * 
 * @version 1.0
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/****************************************************/
/*******|         Constantes & Types         |*******/
/****************************************************/

#define N 3
#define TAILLE (N*N)

typedef struct {
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;

typedef tCase1 tGrille[TAILLE][TAILLE];


/********************************************************/
/***|         Initialisation des prototypes          |***/
/********************************************************/

void chargerGrille(tGrille grille, char nom[30]);
void afficherGrille(tGrille grille);

bool possible(tGrille grille, int ligne, int colonne, int valeur);
void placerValeursPossible(tGrille grille);
void placerValeurSingleton(tGrille grille, bool *continu);

int calculCasesVides(tGrille grille);
int calculNbCandidats(tGrille grille);


/********************************************************/
/**************|         [MAIN]          |***************/
/********************************************************/

int main()
{
    tGrille grilleSudoku;
    bool continu=true;
    char nomGrille[30];
    int CasesVidesInit, nbCasesVides, nbCandidatInit, nbCandidat, nbTours=0;

    chargerGrille(grilleSudoku, nomGrille);

    clock_t begin=clock();

    CasesVidesInit=calculCasesVides(grilleSudoku);

    while(continu)
    {
        continu=false;
        nbTours++;

        printf("Numero du tour : %d\n", nbTours);
        afficherGrille(grilleSudoku);
        printf("\n\n-----------------------------------------------\n\n"); /* Affiche une ligne de separation entre chaque grilles */

        placerValeursPossible(grilleSudoku);
        placerValeurSingleton(grilleSudoku, &continu);

        /* Stats */

        if (nbTours==1){
            nbCandidatInit=calculNbCandidats(grilleSudoku);
        }
    }

    /* Stats */
    nbCasesVides=calculCasesVides(grilleSudoku);
    nbCandidat=calculNbCandidats(grilleSudoku);

    printf("***** Stats pour la grille %s *****\n\nNombre de cases remplies = %d sur %d\tTaux de remplissage = %.3f%%\n\nNombre de candidats elimines = %d\tPourcentage d'elimination = %.3f%%\n\nNombre de tours : %d\n\n",
    nomGrille,
    (CasesVidesInit-nbCasesVides),
    CasesVidesInit,
    ((CasesVidesInit-nbCasesVides)/(CasesVidesInit*1.0))*100,
    (nbCandidatInit-nbCandidat),
    ((nbCandidatInit-nbCandidat)/(nbCandidatInit*1.0))*100,
    nbTours
    );

    clock_t end = clock();
    double tmpsCPU = (end - begin)*1.0 / CLOCKS_PER_SEC;
    printf( "Temps CPU = %.3f secondes\n",tmpsCPU);

    return EXIT_SUCCESS;
}


/********************************************************/
/*****|        Definitions des prototypes          |*****/
/********************************************************/

/**
 * @brief Charge une grille de sudoku.
 * 
 * @param grille Grille du sudoku.
*/
void chargerGrille(tGrille grille, char nom[30])
{
    char nomFichier[30];
    FILE *file;
    int grilleTemp[TAILLE][TAILLE];

    do
    {
        printf("Nom du fichier ? ");
        scanf("%s", nomFichier);

        file = fopen(nomFichier, "rb");
        if (file == NULL)
        {
            printf("\n ERREUR sur le fichier %s\n", nomFichier);
        }
        else
        {
            fread(grilleTemp, sizeof(int), TAILLE*TAILLE, file);

            for (int lig=0;lig<TAILLE;lig++)
            {
                for (int col=0;col<TAILLE;col++)
                {
                    grille[lig][col].valeur=grilleTemp[lig][col];
            }}

            strcpy(nom, nomFichier);
        }

        fclose(file);

    } while (file == NULL);
}

/**
 * @brief Verifie si une valeur peut etre ajoutee dans une case de la grille, AKA respecte les regles du sudoku.
 * 
 * @param grille[TAILLE][TAILLE] Grille du sudoku de taille TAILLE.
 * @param ligne Numero de ligne de la case.
 * @param colonne Numero de colonne de la case.
 * @param valeur Valeur à inserer.
 * 
 * @returns False si la valeur ne peut pas etre placee True sinon.
*/
bool possible(tGrille grille, int ligne, int colonne, int valeur)
{

    /* Verification de la ligne */
    for (int lig = 0; lig < TAILLE; lig++)
    {
        if (grille[ligne][lig].valeur == valeur)
        {
            return false;
    }}

    /* Verification de la colonne */
    for (int col = 0; col < TAILLE; col++)
    {
        if (grille[col][colonne].valeur == valeur)
        {
            return false;
    }}

    /* Verification de la sous-case */
    int startLigne = ligne - (ligne % N); /* Premiere ligne de la sous-case */
    int startColonne = colonne - (colonne % N); /* Premiere colonne de la sous-case */
    for (int lig = 0; lig < N; lig++)
    {
        for (int col = 0; col < N; col++)
        {
            if (grille[lig + startLigne][col + startColonne].valeur == valeur)
            {
                return false;
    }}}

    /* Si aucune erreur est trouvee, renvoie true */
    return true;
}

/**
 * @brief Liste les valeurs possible dans le tableau.
 * 
 * @param grille Grille du sudoku.
*/
void placerValeursPossible(tGrille grille)
{
    for (int ligne=0; ligne<TAILLE; ligne++)
    {
        for (int colonne=0; colonne<TAILLE; colonne++)
        {
            grille[ligne][colonne].nbCandidats=0; /* Reinitialise le nombre de valeurs possibles */

            for (int valeur=1; valeur<=TAILLE; valeur++) /* Parcours de toutes les valeurs possibles */
            {
                if (possible(grille, ligne, colonne, valeur) && grille[ligne][colonne].valeur==0)
                {
                    grille[ligne][colonne].candidats[grille[ligne][colonne].nbCandidats]=valeur;
                    grille[ligne][colonne].nbCandidats++;
}}}}}

/**
 * @brief Trouve un singleton et le place si il existe.
 * 
 * @param grille Grille du sudoku.
 * @param continu(Adresse) True or False si on continue ou non.
*/
void placerValeurSingleton(tGrille grille, bool *continu)
{
    for (int ligne=0; ligne<TAILLE; ligne++)
    {
        for (int colonne=0; colonne<TAILLE; colonne++)
        {
            if ((grille[ligne][colonne].nbCandidats)==1)
            {
                (grille[ligne][colonne].valeur)=(grille[ligne][colonne].candidats[0]);
                *continu=true;
}}}}

/**
    * @brief Affiche la grille inscrite en paramètre.
    * 
    * @param grille Grille du sudoku.
*/
void afficherGrille(tGrille grille)
{
    /* Affichage des numeros de colonne */
    printf("\n   ");
    for (int colCase = 0; colCase < N; colCase++) /* N colonnes de la sous_case */
    {
        for (int numCase = 0; numCase < N; numCase++) /* N sous_cases */
        {
            printf(" %d ", (numCase+1)+(N*colCase));
        }
        printf(" ");
    }

    /* Affichage du contenu de la grille */
    for (int ligneCase=0; ligneCase<N; ligneCase++) /* N sous_cases */
    {
        /* Affichage des bords horizontaux */
        printf("\n  +");

        for (int colCase = 0; colCase < N; colCase++)
        {

            for (int numCase = 0; numCase < N; numCase++)
            {
                printf("---");
            }

            printf("+");
        }

        for (int ligne=0; ligne<N; ligne++) /* N lignes de la sous_case*/
        {

            /* Affichage du numero de ligne */
            printf("\n%d |", (ligne+1)+(3*ligneCase));

            for (int valCase = 0; valCase<N; valCase++) /* N sous_cases */
            {
                for (int val = 0; val < N; val++) /* N valeurs de la ligne de la sous-cases */
                {
                    /* Affichage de la valeur (ou d'un point si la case est vide) */
                    if (grille[ligne+(3*ligneCase)][val+(3*valCase)].valeur == 0)
                    {
                        printf(" . ");
                    }
                    else
                    {
                        printf(" %d ", grille[ligne+(3*ligneCase)][val+(3*valCase)].valeur);
                }}
                printf("|"); /* Affichage des bords verticaux */
    }}}

    /* Affichage du bord inferieur de la grille */
    printf("\n  +");

    for (int colCase = 0; colCase < N; colCase++)
    {
        for (int numCase = 0; numCase < N; numCase++)
        {
            printf("---");
        }

        printf("+");
}}

/**
    * @brief Renvoie le nombre de cases vides d'une grille de sudoku
    * 
    * @param grille Grille du sudoku.
*/
int calculCasesVides(tGrille grille){
    int nb=0;

    for (int l=0; l<TAILLE; l++){
        for (int c=0; c<TAILLE; c++){
            if (grille[l][c].valeur==0){
                nb++;
            }
        }
    }

    return nb;
}

/**
    * @brief Renvoie le nombre de candidats total d'une grille de sudoku
    * 
    * @param grille Grille du sudoku.
*/
int calculNbCandidats(tGrille grille){
    int nb=0;

    for (int l=0; l<TAILLE; l++){
        for (int c=0; c<TAILLE; c++){
            nb+=grille[l][c].nbCandidats;
        }
    }

    return nb;
}
