#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bruteforce.h"
#include <conio.h>




int avancerDunCaseVide(int pos, int *grilleFixe){
    pos = pos + 1;
    while (grilleFixe[pos] == 1 && pos != 81) {
        pos = pos + 1;
    }
    if (pos == 81) { printf("sortie du grille");}
    return pos;
}
int reculerDunCaseVide(int pos, int *grilleFixe){
    if( pos > 1) { // Le probleme est-il causé par ca?
        pos =  pos - 1;
        while (grilleFixe[pos] == 1 && pos>1) {
            pos = pos - 1;
        }
    }
    return pos;
}

int* fixerGrille(char *grille, int *grilleFixe) {
    int i;
    for(i=0;i<81;i++) {
        if((int)(grille[i])!= NULL) {
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
void resoudreBruteForce(char *grille) {
    // On initiale les var usuelle
    int i;
    int pos = 0, iterations = 0;

    // Set the timer
    float temps, tempsTval, tempsTvalSom = 0;
    clock_t t1, t2, tval1, tval2;
    t1 = clock();

    printf("Resolution en cours \n");
    /* L'ensemble de la fonction */
    // On crée la grille fixe
    int grilleFixe[81];
    fixerGrille(grille, grilleFixe);
    for(i=0;i<81;i++) {
        printf("%d ",grilleFixe[i]);
        if((i+1)%3==0){printf("|");}
        if((i+1)%9==0){printf("\n");}
    }// End grille fixe

    // On se déplace sur la premiere case --> On peut pas supprimer ensuite?
    while (grilleFixe[pos] == 1) {
        // printf("on avance pos : %d\n", pos);
        pos = avancerDunCaseVide(pos, grilleFixe);
    } // On est sur la premiere case non vide ! [Test : printf("\n || pos = %d || \n", pos); ]


    // On fait la boucle ultime
    int valeurPossible;
    char *possibilitesTab; // attention maintenant, c'est char et sa renvoie 1, ou 2...

    while(pos<81) { // Rappel : 81 sur ?
        iterations++;
        // On remet les valeurs clé à 0
        valeurPossible = 0;
        tval1 = clock();

        possibilitesTab = valideUnecase(pos, grille);
        tval2 = clock();
        tempsTval = (float)(tval2-tval1)/CLOCKS_PER_SEC;
        tempsTvalSom = tempsTvalSom + tempsTval;

        i = (int)(grille[pos]); // On récupère en int la valeur déjà mise
        if (i == NULL ) { i = 0; } // Si il n'y a rien, on donne à i la valeur 0

        while(valeurPossible == 0 && i<9) {
            i++;
            //printf("pos[%d] : possibilitesTab[%d] = %d\n",pos, i, possibilitesTab[i]);
            if(possibilitesTab[i] != 0){
                grille[pos] = (char)(i);
                valeurPossible = 1;
            }
        }
        free(possibilitesTab);

        if(valeurPossible == 0) {
            grille[pos] = (char)(NULL);
            pos = reculerDunCaseVide(pos, grilleFixe);
        }
        else {
            pos = avancerDunCaseVide(pos, grilleFixe);
        }


    }
    updateGrille(grille);

    // On affiche le temps
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);

    printf("tempsTvalSom = %f\n", tempsTvalSom); // On a une preuve que c'est le programme de Louis qui bouffe la ram :P
}


