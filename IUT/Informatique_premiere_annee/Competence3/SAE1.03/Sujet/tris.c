#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NB_NOTES 8
#define VAL_MAX 21

typedef int t_tablo[NB_NOTES];

typedef struct
{
    char nom[31]; /** Nom de l'etudiant */
    char groupe_td; /** Lettre indiquant le groupe TD de l'étudiant */
    t_tablo notes; /** Liste des notes de l'étudiant de type t_tablo*/
} eleve; /** Structure d'un(e) étudiant(e) */

int maxTab(t_tablo tabNotes);
int indMin(t_tablo tabNotes);
void copie(t_tablo tabIn, t_tablo tabOut);
void triRempCroi(t_tablo tab, t_tablo tabResult);


int main(){
    eleve eleve1;

    strcpy(eleve1.nom, "Michel");
    eleve1.groupe_td='A';
    eleve1.notes={5,9,16,9,3,0,12,18};
}

void remplirTableau(t_tablo tab){
    
}

int maxTab(t_tablo tabNotes){
    int max=0;

    for (int val=0; val<NB_NOTES;val++){
        if (tabNotes[val]>max){
            max=tabNotes[val];
        }
    }

    return max;
}

int indMin(t_tablo tabNotes){
    int indiceMin=0;

    for (int indice=1; indice<NB_NOTES; indice++){
        if (tabNotes[indice]<tabNotes[indiceMin]){
            indiceMin=indice;
        }
    }

    return indiceMin;
}

void copie(t_tablo tabIn, t_tablo tabOut){
    for (int val=0; val<NB_NOTES; val++){
        tabOut[val]=tabIn[val];
    }
}

void triRempCroi(t_tablo tab, t_tablo tabResult){
    int max, indiceMin, val;
    t_tablo tabCopie;

    copie(tab, tabCopie);

    max=maxTab(tab);

    for (val=0; val<NB_NOTES; val++){
        indiceMin=indMin(tabCopie);

        tabResult[val]=tabCopie[indiceMin];

        tabCopie[indiceMin]=max;
    }
}
