#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bruteforce.h"
#include <conio.h>




int avancerDunCaseVide(int pos, int *grilleFixe){
    pos = pos + 1;
    while (grilleFixe[pos] == 1 && pos != 80) {
        pos = pos + 1;
    }
    return pos;
}
int reculerDunCaseVide(int pos, int *grilleFixe){
    if( pos > 2) { // Le probleme est-il caus� par ca?
        pos =  pos - 1;
        while (grilleFixe[pos] == 1 && pos>1) {
            pos = pos - 1;
        }

    }
    return pos;
}

int* fixerGrille(int *grille, int *grilleFixe) {
    int i;
    for(i=0;i<81;i++) {
        if(grille[i]!= NULL) {
            grilleFixe[i] = 1;
        }
        else {
            grilleFixe[i] = 0;
        }
        /*printf("%d ",grilleFixe[i]);
        if((i+1)%3==0){printf("|");}
        if((i+1)%9==0){printf("\n");} */
    }
    return grilleFixe;

}

void resoudreBruteForce (int *grille) { //int *solution?

    float temps;
    clock_t t1, t2;
    t1 = clock();

    printf("Resolution en cours \n");
    int grilleFixe[81];
    fixerGrille(grille, grilleFixe);
    int pos = 0;
    int i;
   /* for(i=0;i<81;i++) {
        printf("%d ",grilleFixe[i]);
        if((i+1)%3==0){printf("|");}
        if((i+1)%9==0){printf("\n");}
    }*/

    // On va sur la premiere case � remplir
    while (grilleFixe[pos] == 1) {
        // printf("on avance pos : %d\n", pos);
        pos = avancerDunCaseVide(pos, grilleFixe);
    }
    //printf("\n || pos = %d || \n", pos);
    // Quels sont les validit�s de la case
    int * possibilitesTab;
    possibilitesTab = verifValidite(pos,grille);
    for(i=0;i<9;i++){
    // On va mettre un nombre parmis les diff�rentes possibilit�s.
        if(possibilitesTab[i] == 1){//&& i>grille[pos]
            grille[pos] = i+1;
        }
        updateGrille(grille);
    }

    int v;
    int valeurPossible;
    pos = avancerDunCaseVide(pos, grilleFixe);
    while(pos<81) {
        // assigne la premiere option
        valeurPossible = 0;
        possibilitesTab = verifValidite(pos,grille);
        v = grille[pos];
        if (v == NULL || v<0) { v = -1; }
        i = v;

        while(valeurPossible == 0 && i<8) {
            i++;
            //printf("posTab(%d) = %d \n",i, possibilitesTab[i]);
        // On va mettre un nombre parmis les diff�rentes possibilit�s.
            if(possibilitesTab[i] == 1){ // && i>grille[pos]
                grille[pos] = i+1;
                valeurPossible = 1;
            }


        }
        updateGrille(grille);
        if (valeurPossible == 0){
            grille[pos] = NULL;
            pos = reculerDunCaseVide(pos, grilleFixe);
        }
        else {
            pos = avancerDunCaseVide(pos, grilleFixe);
        }

        //printf("_________ pos = %d \n", pos);
    }


    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);

}

