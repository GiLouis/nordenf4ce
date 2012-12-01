#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"



void generer(int* grille){


   // genererEaster(grille);
     generer20Min(grille);
   // genererTwoLigne(grille);
    updateGrille(grille);
}


void resoudre(int* grille,int* solution){

}
/*
Fonction retournant une liste de toutes les valeurs possibles de la case
en faisant appel aux fonctions ci-dessous
*/
int* verifValidite(int pos, int* grille){
    int* possibilites[3];
    possibilites[0] = valide3x3(pos,grille);
    possibilites[1] = valide9x1(pos,grille);
    possibilites[2] = valide1x9(pos,grille);

    int* possibilites_fin;
    possibilites_fin = malloc(sizeof(int)*9);

    int i=0;
    int j=0;

    for(i=0;i<9;i++){
        possibilites_fin[i]=1;
    }

    for(i=0;i<3;i++){
        for(j=0;j<9;j++){
            if(possibilites[i][j]==0){
                possibilites_fin[j]=0;
            }
        }
        free(possibilites[i]);
    }

 /*   printf("POSSIBILITES FIN :\n");
    for(i=0;i<9;i++){
        printf("->%d = %d \n",i+1,possibilites_fin[i]);
    } */
    return possibilites_fin;
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
        //printf("%d - %d \n",procCase,grille[procCase]);
        if(pos!=procCase){
            if(possibilites[grille[procCase]-1]!=0){
                possibilites[grille[procCase]-1]=0;
            }else if(grille[procCase]!=0){
                printf("Erreur : le 3x3 contient deux fois le même nombre : %d\n",grille[procCase]);
                break;
            }
        }
    }

   /* printf("POSSIBILITES :\n");
    for(i=0;i<9;i++){
        printf("|%d = %d |\n",i+1,possibilites[i]);
    } */
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
        //printf("%d - %d \n",procCase,grille[procCase]);
        if(pos!=procCase){
            if(possibilites[grille[procCase]-1]!=0){
                possibilites[grille[procCase]-1]=0;
            }else if(grille[procCase]!=0){
                printf("Erreur : le 3x3 contient deux fois le même nombre : %d\n",grille[procCase]);
                break;
            }
        }
    }

   /* printf("POSSIBILITES :\n");
    for(i=0;i<9;i++){
        printf("|%d = %d |\n",i+1,possibilites[i]);
    }*/
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
        //printf("%d - %d \n",procCase,grille[procCase]);
        if(pos!=procCase){
            if(possibilites[grille[procCase]-1]!=0){
                possibilites[grille[procCase]-1]=0;
            }else if(grille[procCase]!=0){
                printf("Erreur : le 3x3 contient deux fois le même nombre : %d\n",grille[procCase]);
                break;
            }
        }
    }

  /*  printf("POSSIBILITES :\n");
    for(i=0;i<9;i++){
        printf("|%d = %d |\n",i+1,possibilites[i]);
    }*/
    return possibilites;

}
