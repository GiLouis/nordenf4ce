#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void resoudre(int* grille,int* solution){

}

void generer(int* grille){
    int i=0;
    for(i=0;i<81;i++){
        grille[i]=i;

    }

    updateGrille(grille);
}

/*
Fonction retournant une liste de toutes les valeurs possibles de la case
en faisant appel aux fonctions ci-dessous
*/
void verifValidite(int pos, int* grille){
    int i=0;
    int ligneGroupe=0;
    int colonneGroupe=0;
    ligneGroupe=pos/27;
    colonneGroupe=(pos%9)/3;
    int procCase=0;
    for(i=0;i<9;i++){
        procCase=ligneGroupe*27+colonneGroupe*3+i%3+(i/3)*9;
        printf("%d - %d : %d \n",ligneGroupe,colonneGroupe,procCase);
    }



}
/*
Fonction retournant les valeurs possibles de la case en fonction du carré
*/
int* valide3x3(int pos, int* grille){


}
/*
Fonction retournant les valeurs possibles de la case en fonction de la ligne
*/
int* valide9x1(int pos, int* grille){


}
/*
Fonction retournant les valeurs possibles de la case en fonction de la colonne
*/
int* valide1x9(int pos, int* grille){


}
