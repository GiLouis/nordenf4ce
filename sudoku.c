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

    // SUDOKU 20MINUTES
    grille[0]=6;
    grille[1]=5;
    grille[6]=2;
    grille[9]=1;
    grille[10]=8;
    grille[11]=9;
    grille[14]=2;
    grille[16]=3;
    grille[21]=5;
    grille[22]=8;
    grille[24]=1;
    grille[25]=6;
    grille[26]=9;
    grille[27]=8;
    grille[30]=7;
    grille[31]=9;
    grille[33]=6;
    grille[36]=7;
    grille[39]=4;
    grille[41]=8;
    grille[44]=3;
    grille[47]=5;
    grille[49]=6;
    grille[50]=3;
    grille[53]=2;
    grille[54]=4;
    grille[55]=6;
    grille[56]=7;
    grille[58]=5;
    grille[59]=9;
    grille[64]=3;
    grille[66]=8;
    grille[69]=9;
    grille[70]=5;
    grille[71]=7;
    grille[74]=8;
    grille[79]=4;
    grille[80]=6;

    verifValidite(1,grille);
    updateGrille(grille);
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

    printf("POSSIBILITES FIN :\n");
    for(i=0;i<9;i++){
        printf("->%d = %d \n",i+1,possibilites_fin[i]);
    }
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
