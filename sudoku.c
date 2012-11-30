#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

void resoudre(int* grille,int* solution){

}

void generer(int* grille){
    int i=0;
    for(i=0;i<81;i++){
        //grille[i]=(i+1)%3;

    }
    grille[0]=1;
    grille[1]=0;
    grille[2]=3;
    grille[9]=4;
    grille[10]=5;
    grille[11]=6;
    grille[18]=7;
    grille[19]=8;
    grille[20]=9;

    verifValidite(1,grille);
    updateGrille(grille);
}

/*
Fonction retournant une liste de toutes les valeurs possibles de la case
en faisant appel aux fonctions ci-dessous
*/
int* verifValidite(int pos, int* grille){
    valide3x3(pos,grille);
    valide9x1(pos,grille);
    valide1x9(pos,grille);
}
/*
Fonction retournant les valeurs possibles de la case en fonction du carré
*/
int* valide3x3(int pos, int* grille){
    int i=0;
    int ligneGroupe=0;
    int colonneGroupe=0;
    ligneGroupe=pos/27;
    colonneGroupe=(pos%9)/3;
    int procCase=0;
    int *possibilites;
    possibilites=malloc(sizeof(int)*9);
    for(i=0;i<9;i++){
        possibilites[i]=1;
    }

    for(i=0;i<9;i++){
        procCase=ligneGroupe*27+colonneGroupe*3+i%3+(i/3)*9;
        printf("%d - %d \n",procCase,grille[procCase]);
        if(pos!=procCase){
            if(possibilites[grille[procCase]-1]!=0){
                possibilites[grille[procCase]-1]=0;
            }else if(grille[procCase]!=0){
                printf("Erreur : le 3x3 contient deux fois le même nombre : %d\n",grille[procCase]);
                break;
            }
        }
    }

    printf("POSSIBILITES :\n");
    for(i=0;i<9;i++){
        printf("|%d = %d |\n",i+1,possibilites[i]);
    }
    return possibilites;

}
/*
Fonction retournant les valeurs possibles de la case en fonction de la ligne
*/
int* valide9x1(int pos, int* grille){
    int i=0;
    int ligneGroupe=0;
    ligneGroupe=pos/9;
    int procCase=0;
    int *possibilites;
    possibilites=malloc(sizeof(int)*9);
    for(i=0;i<9;i++){
        possibilites[i]=1;
    }

    for(i=0;i<9;i++){
        procCase=ligneGroupe*9+i;
        printf("%d - %d \n",procCase,grille[procCase]);
        if(pos!=procCase){
            if(possibilites[grille[procCase]-1]!=0){
                possibilites[grille[procCase]-1]=0;
            }else if(grille[procCase]!=0){
                printf("Erreur : le 3x3 contient deux fois le même nombre : %d\n",grille[procCase]);
                break;
            }
        }
    }

    printf("POSSIBILITES :\n");
    for(i=0;i<9;i++){
        printf("|%d = %d |\n",i+1,possibilites[i]);
    }
    return possibilites;

}
/*
Fonction retournant les valeurs possibles de la case en fonction de la colonne
*/
int* valide1x9(int pos, int* grille){
    int i=0;
    int colonneGroupe=0;
    colonneGroupe=pos%9;
    int procCase=0;
    int *possibilites;
    possibilites=malloc(sizeof(int)*9);
    for(i=0;i<9;i++){
        possibilites[i]=1;
    }

    for(i=0;i<9;i++){
        procCase=colonneGroupe+i*9;
        printf("%d - %d \n",procCase,grille[procCase]);
        if(pos!=procCase){
            if(possibilites[grille[procCase]-1]!=0){
                possibilites[grille[procCase]-1]=0;
            }else if(grille[procCase]!=0){
                printf("Erreur : le 3x3 contient deux fois le même nombre : %d\n",grille[procCase]);
                break;
            }
        }
    }

    printf("POSSIBILITES :\n");
    for(i=0;i<9;i++){
        printf("|%d = %d |\n",i+1,possibilites[i]);
    }
    return possibilites;

}
