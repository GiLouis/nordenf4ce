#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grilleText.h"

int genererSdk(char *grille, int difficulte) {
    viderSudoku(grille);
    genererTwoLigne(grille); // Bruteforce_moy ->0.01sec
    resoudreBruteForce(grille);
    enleverCases(grille, difficulte);
}

void genererEaster(char* grille){

    // Easter Monster
    grille[0]=1;
    grille[7]=8;
    grille[8]=9;
    grille[14]=9;
    grille[17]=2;
    grille[24]=4;
    grille[25]=5;
    grille[29]=7;
    grille[30]=6;
    grille[37]=3;
    grille[40]=4;
    grille[45]=9;
    grille[50]=2;
    grille[53]=5;
    grille[56]=4;
    grille[58]=7;
    grille[63]=5;
    grille[68]=8;
    grille[70]=1;
    grille[73]=6;
    grille[75]=3;

    return grille;
}
void generer20Min(char* grille){

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

    return grille;
}
void genererTwoLigne(char* grille){ // Générateur non parfait : il peut y avoir un incidence sur le premier 3x3

    printf("Generation en cours\n");
    int i=0;
    int j=0;
    int v=0;
    int retry=0;
    int nbaleat=0;
    int presence[9]={0};
    grille[0]=rand()%9+1;
    presence[0]=grille[0];
    for(i=1;i<9;i++){
        do{
            retry=0;
            nbaleat=rand()%9+1;
            j=0;
            for(j=0;j<9;j++){
                if(nbaleat==presence[j]){
                    retry=1;
                }
            }
        }while(retry);
        grille[i]=nbaleat;
        presence[i]=grille[i];
    }
    for(i=1;i<9;i++){
        presence[i]=0;
    }
    for(i=1;i<9;i++){
        do{
            retry=0;
            nbaleat=rand()%9+1;
            j=0;
            for(j=0;j<9;j++){
                if(nbaleat==presence[j]){
                    retry=1;
                }
            }
        // On s'assure que il n'y a pas d'identique dans la premiere case
         if(i<3) {
               for(v=1;v<3;v++) {
                    if(nbaleat==grille[v]){
                        retry=1;
                    }
                }
            }
        }while(retry);
        grille[i*9]=nbaleat;
        presence[i]=nbaleat;
    }

    return grille;
}
void genererNearWorstCase (char* grille) {
    printf("generation near worst case for Bruteforce\n");

    grille[14]=3;
    grille[16]=8;
    grille[17]=5;
    grille[20]=1;
    grille[22]=2;
    grille[30]=5;
    grille[32]=7;
    grille[38]=4;
    grille[42]=1;
    grille[46]=9;
    grille[54]=5;
    grille[61]=7;
    grille[62]=3;
    grille[65]=2;
    grille[67]=1;
    grille[76]=4;
    grille[80]=9;


}
void genererNearWorstCaseInv (char* grille) {


    printf("generation near worst case for Bruteforce INVERSE\n");

    grille[14]=7;
    grille[16]=2;
    grille[17]=5;
    grille[20]=9;
    grille[22]=8;
    grille[30]=5;
    grille[32]=3;
    grille[38]=6;
    grille[42]=9;
    grille[46]=1;
    grille[54]=5;
    grille[61]=3;
    grille[62]=7;
    grille[65]=8;
    grille[67]=9;
    grille[76]=6;
    grille[80]=1;

    return grille;

}
void genererStarBurstLeo (char* grille) {

    printf("Generation Star Burst Leo");

    grille[0]=9;
    grille[3]=1;
    grille[5]=4;
    grille[8]=2;
    grille[10]=8;
    grille[13]=6;
    grille[16]=7;
    grille[27]=4;
    grille[35]=1;
    grille[37]=7;
    grille[43]=3;
    grille[45]=3;
    grille[53]=7;
    grille[64]=3;
    grille[67]=7;
    grille[70]=8;
    grille[72]=1;
    grille[75]=2;
    grille[77]=9;
    grille[80]=4;

    return grille;
}
