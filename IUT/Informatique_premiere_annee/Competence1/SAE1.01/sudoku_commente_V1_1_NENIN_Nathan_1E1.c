/*!
 * @brief Jeu de sudoku
 *
 * @author NENIN Nathan
 *
 * @version 1.1
 *
 * @date 26/11/23
 *
 * Ce programme demande une grille au joueur puis lance une partie de sudoku avec le fichier chargé.
 * Le programme affiche la grille dans le terminal, demande les coordonnées de la case choisie par le joueur et la valeur à placer, et recommence jusqu'à ce que le joueur perde ou que la grille soit remplie
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//------------| DEFINITIONS DE TYPES |------------

#define N 3 /*! @def N @brief Pour une TAILLE de grille de sudoku de N^2 */
typedef int grilleSudoku[N * N][N * N];
/*!
 * @typedef grilleSudoku[N*N][N*N]
 *
 * @brief Tableau de tableaux d'entiers de taille (N*N)*(N*N) (grille du sudoku)
 */

//------------| CONSTANTES |------------

// Constantes d'entiers
const int TAILLE = N * N; /*! @def TAILLE @brief Taille de la grille de N*N */

// Constantes de caractère
const char REJOUER_OUI = 'O'; /*! @def REJOUER_OUI @brief Caractère pour rejouer */
const char REJOUER_NON = 'n'; /*! @def REJOUER_NON @brief Caractère pour arrêter de jouer */

// Constantes de chaines de caractères
const char FORMAT_DEMANDE_VALEUR[] = "\nMettez la valeur %s\n";         /*! @def FORMAT_DEMANDE_VALEUR @brief Format de demande de valeur*/
const char FORMAT_AFFICHAGE_VALEURS[] = "\nLigne : %d\nColonne : %d\n"; /*! @def FORMAT_AFFICHAGE_VALEURS @brief Format de d'affichage de valeur*/
const char FORMAT_MESSAGE_ERREUR[] = "\nMessage d'erreur : %s\n";       /*! @def FORMAT_MESSAGE_ERREUR @brief Format de message d'erreur*/
const char FORMAT_SAISIE_VALEUR[] = "\nSaisie de valeur : ";            /*! @def FORMAT_SAISIE_VALEUR @brief Format de saisie de valeur*/

const char DEMANDE_FICHIER[] = "\nNom du fichier ? : ";                                                 /*! @def DEMANDE_FICHIER @brief Texte pour la demande de chargement d'un fichier*/
const char ERREUR_FICHIER[] = "\nERREUR sur le fichier %s\nVeuillez mettre un nom de fichier valide\n"; /*! @def ERREUR_FICHIER @brief Texte pour l'erreur d'un chargement d'un fichier*/

const char DEMANDE_LIGNE[] = "de ligne";     /*! @def DEMANDE_LIGNE @brief Texte de la demande d'une valeur de ligne*/
const char DEMANDE_COLONNE[] = "de colonne"; /*! @def DEMANDE_COLONNE @brief Texte de la demande d'une valeur de colonne*/
const char DEMANDE_VALEUR[] = "a placer";    /*! @def DDEMANDE_VALEUR @brief Texte de la demande d'une valeur à placer dans une case*/

const char CASE_PLEINE[] = "IMPOSSIBLE car la case n'est pas libre"; /*! @def CASE_PLEINE @brief Texte d'erreur lors du choix de coordonnées d'une case pleine*/

const char TROP_LONGUE[] = "Entrée trop longue";                                 /*! @def TROP_LONGUE @brief Texte d'erreur lorsque que l'entrée d'une valeur est trop longue*/
const char INFERIEUR[] = "Valeur trop petite";                                   /*! @def INFERIEUR @brief Texte d'erreur lorsque que la valeur entrée est trop petite*/
const char SUPERIEUR[] = "Valeur trop grande";                                   /*! @def SUPERIEUR @brief Texte d'erreur lorsque que la valeur entrée est trop grande*/
const char CONVERSION_ECHOUEE[] = "Entrée invalide (mettez une valeur entière)"; /*! @def CONVERSION_ECHOUEE @brief Texte d'erreur lorsque la valeur entrée n'est pas un entier*/

const char VALEUR_PRESENTE_LIGNE[] = "\nLa valeur %d est déjà présente sur la même ligne.\n";     /*! @def VALEUR_PRESENTE_LIGNE @brief Texte d'erreur lorsque la valeur entrée est déjà présente sur la ligne*/
const char VALEUR_PRESENTE_COLONNE[] = "\nLa valeur %d est déjà présente sur la même colonne.\n"; /*! @def VALEUR_PRESENTE_COLONNE @brief Texte d'erreur lorsque la valeur entrée est déjà présente sur la colonne*/
const char VALEUR_PRESENTE_CASE[] = "\nLa valeur %d est déjà présente dans la même sous-case.\n"; /*! @def VALEUR_PRESENTE_CASE @brief Texte d'erreur lorsque la valeur entrée est déjà présente dans la sous-case*/

const char MESSAGE_PARTIE_GAGNE[] = "\nGrille pleine, fin de partie :)\n"; /*! @def MESSAGE_PARTIE_GAGNE @brief Message de victoire*/
const char MESSAGE_PARTIE_PERDU[] = "\nVous avez perdu :(\n";              /*! @def MESSAGE_PARTIE_PERDU @brief Message de défaite*/

const char MESSAGE_REJOUER[] = "\nVoulez-vous rejouer ? O/n : "; /*! @def MESSAGE_REJOUER @brief Texte pour demander si le joueur veut rejouer*/

//------------| DEFINITIONS DES PROTOTYPES |------------

void viderBuffer();
void chargerGrille(grilleSudoku grille);
void afficherGrille(grilleSudoku grille);
void saisir(int *valeur);

bool possible(grilleSudoku grille, int ligne, int colonne, int valeur);
bool grillePleine(grilleSudoku grille);

//------------| PROGRAMME PRINCIPAL |------------

int main()
{
    grilleSudoku grille;
    int numLigne, numColonne, valeur;
    char rejouer;
    bool perdu;

    do
    {
        perdu = false;

        chargerGrille(grille);

        while ((grillePleine(grille) == false) && (perdu != true))
        {

            afficherGrille(grille);

            // Demande des valeurs de ligne et de colonne
            printf(FORMAT_DEMANDE_VALEUR, DEMANDE_LIGNE);
            saisir(&numLigne);

            printf(FORMAT_DEMANDE_VALEUR, DEMANDE_COLONNE);
            saisir(&numColonne);

            // Conversion en coordonnées de tableau
            numLigne -= 1;
            numColonne -= 1;

            if (grille[numLigne][numColonne] != 0)
            { // Si la case est pleine
                printf(FORMAT_MESSAGE_ERREUR, CASE_PLEINE);
            }

            else
            {
                // Affichage des coordonées choisies
                printf(FORMAT_DEMANDE_VALEUR, DEMANDE_VALEUR);
                printf(FORMAT_AFFICHAGE_VALEURS, numLigne + 1, numColonne + 1);

                saisir(&valeur);

                if (possible(grille, numLigne, numColonne, valeur))
                {
                    grille[numLigne][numColonne] = valeur;
                }

                else
                { // Si la valeur a placer n'est pas bonne, le jeu prend fin
                    printf(MESSAGE_PARTIE_PERDU);
                    perdu = true;
                }
            }
        }

        if (grillePleine(grille) == true)
        {
            printf(MESSAGE_PARTIE_GAGNE);
        }

        // Demande si le joueur veut rejouer
        do
        {
            printf(MESSAGE_REJOUER);
            scanf(" %c", &rejouer);
        } while ((rejouer != REJOUER_OUI) && (rejouer != REJOUER_NON));

    } while (rejouer != REJOUER_NON);

    return EXIT_SUCCESS;
}

//------------| DEFINITIONS DES PROCEDURES |------------

void viderBuffer()
{
    /*!
     * @fn viderBuffer
     *
     * @brief Vide le buffer
     */
    while (getchar() != '\n')
        ;
}

void chargerGrille(grilleSudoku grille)
{
    /*!
     * @fn chargerGrille
     *
     * @brief Charge une grille inscrite par l'utilisateur
     *
     * @param grille : (S OU E/S) grille du sudoku
     */
    char nomFichier[30];
    FILE *f;

    do
    {
        printf(DEMANDE_FICHIER);
        scanf(" %s", nomFichier);
        f = fopen(nomFichier, "rb");

        if (f == NULL)
        {
            printf(ERREUR_FICHIER, nomFichier);
        }
        else
        {
            fread(grille, sizeof(int), TAILLE * TAILLE, f);
        }

        fclose(f);

    } while (f == NULL);

    viderBuffer();
}

void afficherGrille(grilleSudoku grille)
{
    /*!
     * @fn afficherGrille
     *
     * @brief Affiche la grille inscrite en paramètre
     *
     * @param grille : (E) grille du sudoku
     */

    // Affichage des numéros de colonne
    printf("\n   ");
    for (int colCase = 0; colCase < N; colCase++)
    { // N sous_cases
        for (int numCase = 0; numCase < N; numCase++)
        { // N colonnes de la sous_case
            printf(" %d ", (numCase + 1) + (N * colCase));
        }

        printf(" ");
    }

    // Affichage du contenu de la grille
    for (int ligneCase = 0; ligneCase < N; ligneCase++)
    { // N sous_cases

        // Affichage des bords horizontaux
        printf("\n  +");

        for (int colCase = 0; colCase < N; colCase++)
        {

            for (int numCase = 0; numCase < N; numCase++)
            {
                printf("---");
            }

            printf("+");
        }

        for (int ligne = 0; ligne < N; ligne++)
        { // N lignes de la sous_case

            // Affichage du numéro de ligne
            printf("\n%d |", (ligne + 1) + (3 * ligneCase));

            for (int valCase = 0; valCase < N; valCase++)
            { // N sous_cases

                for (int val = 0; val < N; val++)
                { // N valeurs de la ligne de la sous-cases

                    // Affichage de la valeur (ou d'un point si la case est vide)
                    if (grille[ligne + (3 * ligneCase)][val + (3 * valCase)] == 0)
                    {
                        printf(" . ");
                    }
                    else
                    {
                        printf(" %d ", grille[ligne + (3 * ligneCase)][val + (3 * valCase)]);
                    }
                }

                printf("|"); // Affichage des bords verticaux
            }
        }
    }

    // Affichage du bord inférieur de la grille
    printf("\n  +");

    for (int colCase = 0; colCase < N; colCase++)
    {

        for (int numCase = 0; numCase < N; numCase++)
        {
            printf("---");
        }

        printf("+");
    }
}

void saisir(int *valeur)
{
    /*!
     * @fn saisir
     *
     * @brief Cette procédure lit une valeur comprise entre 1 et n^2 (TAILLE) -> peut être une ligne, une colonne ou une valeur à placer
     *
     * @param valeur : (S OU E/S) Prend la valeur saisie (si elle est bonne)
     */

    bool bonneValeur = false;

    do
    {
        char valTest[10]; // Valeur de test avant la conversion

        printf(FORMAT_SAISIE_VALEUR);
        fgets(valTest, sizeof(valTest), stdin);

        // Enleve le retour a la ligne de l'entree
        int longueur = strlen(valTest);
        if (longueur > 0 && valTest[longueur - 1] == '\n')
        {
            valTest[longueur - 1] = '\0';
        }
        else // si l'entree est trop longue
        {
            printf(FORMAT_MESSAGE_ERREUR, TROP_LONGUE);
            viderBuffer();
            continue; // Pour que le message d'erreur ne se repete pas
        }

        if (sscanf(valTest, "%d", valeur) != 0)
        { // Conversion reussie

            if (*valeur <= 0)
            {
                printf(FORMAT_MESSAGE_ERREUR, INFERIEUR);
            }
            else if (*valeur > TAILLE)
            {
                printf(FORMAT_MESSAGE_ERREUR, SUPERIEUR);
            }
            else
            {
                bonneValeur = true;
            }
        }

        else
        { // Conversion echouee
            printf(FORMAT_MESSAGE_ERREUR, CONVERSION_ECHOUEE);
        }

    } while (!bonneValeur);
}

//------------| DEFINITIONS DES FONCTIONS |------------

bool possible(grilleSudoku grille, int ligne, int colonne, int valeur)
{
    /*!
     * @fn possible
     *
     * @brief Vérifie si une valeur peut être ajoutée dans une case particulière de la grille, c’est-à-dire si ça respecte les règles du sudoku :
     * - la valeur n’est pas déjà présente sur la même ligne que la case
     * - la valeur n’est pas déjà présente sur la même colonne que la case
     * - la valeur n’est pas déjà présente dans le même bloc que la case
     *
     * @param grille[TAILLE][TAILLE] : (E) grille du sudoku de taille TAILLE
     * @param ligne : (E) numero de ligne de la case
     * @param colonne : (E) numero de colonne de la case
     * @param valeur : (E) valeur à insérer
     *
     * @return false si la valeur ne peut pas être placée true sinon
     */

    // Vérification de la ligne
    for (int lig = 0; lig < TAILLE; lig++)
    {
        if (grille[ligne][lig] == valeur)
        {
            printf(VALEUR_PRESENTE_LIGNE, valeur);
            return false;
        }
    }

    // Vérification de la colonne
    for (int col = 0; col < TAILLE; col++)
    {
        if (grille[col][colonne] == valeur)
        {
            printf(VALEUR_PRESENTE_COLONNE, valeur);
            return false;
        }
    }

    // Vérification de la sous-case
    int startLigne = ligne - (ligne % N);       // Première ligne de la sous-case
    int startColonne = colonne - (colonne % N); // Première colonne de la sous-case
    for (int lig = 0; lig < N; lig++)
    {
        for (int col = 0; col < N; col++)
        {
            if (grille[lig + startLigne][col + startColonne] == valeur)
            {
                printf(VALEUR_PRESENTE_CASE, valeur);
                return false;
            }
        }
    }

    // Si aucune erreur est trouvée, renvoie true
    return true;
}

bool grillePleine(grilleSudoku grille)
{
    /*!
     * @fn grillePleine
     *
     * @brief Vérifie si la grille est pleine
     *
     * @param grille[TAILLE][TAILLE] : (E) grille du sudoku de taille TAILLE
     *
     * @return false si la grille n'est pas pleine true sinon
     */

    // Parcours de la grille
    for (int ligne = 0; ligne < TAILLE; ligne++)
    {
        for (int colonne = 0; colonne < TAILLE; colonne++)
        {
            if (grille[ligne][colonne] == 0)
            { // si il y a une case vide
                return false;
            }
        }
    }

    // La grille est pleine
    return true;
}
