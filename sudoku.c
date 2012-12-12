#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "sudoku.h"

typedef struct paramsThreadVerifValidite{
    char pos;
    char* grille;
    char* debutTabPossib;
};

void generer(char* grille){

    //genererEaster(grille); // Bruteforce -> 0.01sec
    //generer20Min(grille); // Bruteforce ->0.014sec
    //genererTwoLigne(grille); // Bruteforce_moy ->0.01sec
    //genererNearWorstCaseInv(grille); // Bruteforce -> 0.1sec
    //genererNearWorstCase (grille);
    genererStarBurstLeo(grille); //Bruteforce->2sec
    updateGrille(grille);
}


int compteCaseVides(char* grille){
    int i=0;
    int compte=0;
    for(i=0;i<81;i++){
        if(grille[i]==0){
            compte++;
        }
    }
    return compte;
}
/*
Fonction renvoyant un tableau avec toutes les possibilites et leur compte des cases de la grille
*/
char* valideGrille(char* grille){
    int i = 0;
    HANDLE caseThread[81];
    paramsThreadVerifValidite var[81];

    char* tabPossibilites = malloc(81*(10*sizeof(char)));

    for(i=0;i<81;i++){
        var[i].pos=i;
        var[i].grille=grille;
        var[i].debutTabPossib = &(tabPossibilites[i*10]);
        //printf("%d %x | %x\n",i,var[i].debutTabPossib,&(var[i]));
        // ATTENTION DEBUG : EN PASSANT PAR LES THREAD, CELA NE MARCHE PAS... Mutex à faire ? Car la fonction appelée n'a pas les mêmes variables...



        caseThread[i] = CreateThread(NULL,0,verifValidite,&(var[i]),0,NULL);
        WaitForMultipleObjects(1,&(caseThread[i]),TRUE,INFINITE);


    }

    //WaitForMultipleObjects(81,caseThread,TRUE,INFINITE);

    return tabPossibilites;
}
/*
Fonction renvoyant un tableau avec toutes les possibilites et leur compte d'une des case de la grille
*/
char* valideUnecase(char pos,char* grille){
    HANDLE caseThread;
    char* tabPossibilites = malloc((10*sizeof(char)));
    //printf("Adresse : %x\n",tabPossibilites);
    paramsThreadVerifValidite var;
    var.grille=grille;
    var.pos=pos;
    var.debutTabPossib = tabPossibilites;

    verifValidite(&var);

    return tabPossibilites;
}

char* trierCroissantPossib(char* tabPossibilites){
    int i = 0;
    int j = 0;
    char min=0;
    int compte=0;
    char* tabPossibOrdonne = malloc(81*sizeof(char));
    for(i=0;i<81;i++){
        tabPossibOrdonne[i]=-1;
    }
    for(i=0;i<81;i++){

        min=tabPossibilites[i*10];
        compte=0;
        for(j=0;j<81;j++){
            if(tabPossibilites[i*10]>tabPossibilites[j*10] && i!=j){
                compte++;
            }
        }
        while(tabPossibOrdonne[compte]!=-1){
            compte++;
        }
        tabPossibOrdonne[compte]=i;
    }

    /*for(i=0;i<81;i++){
        printf("%d/ case %d avec %d possibilites\n",i,tabPossibOrdonne[i],tabPossibilites[tabPossibOrdonne[i]*10]);
    }*/
    return tabPossibOrdonne;
}

char*  supprCRempliesDuTri(char* tabPossibOrdonne,int* tailleFin,char* grille){
    int i = 0;
    int j = 0;

    int compte = compteCaseVides(grille);
    char* tabPossibOrdonneClean = malloc(compte*sizeof(char));

    for(i=0;i<81;i++){
        if(grille[tabPossibOrdonne[i]]==0){
            tabPossibOrdonneClean[j]=tabPossibOrdonne[i];
            j++;
        }
    }
    *tailleFin = compte;

    /*for(i=0;i<*tailleFin;i++){
        printf("%d/ case %d\n",i,tabPossibOrdonneClean[i]);
    }*/
    return tabPossibOrdonneClean;
}

// NE PAS UTILISER DIRECTEMENT LES FONCTIONS CI-DESSOUS

void verifValidite(paramsThreadVerifValidite* param){
    HANDLE possibThread[3];
    paramsThreadVerifValidite paramCase[3];
    char* possibilites;
    possibilites = malloc(3*9*sizeof(char));

    paramCase[0].grille=param->grille;
    paramCase[0].pos=param->pos;
    paramCase[0].debutTabPossib=&(possibilites[0]);
    possibThread[0] = CreateThread(NULL,0,valide3x3,&(paramCase[0]),0,NULL);
    //valide3x3(&(paramCase[0]));

    paramCase[1].grille=param->grille;
    paramCase[1].pos=param->pos;
    paramCase[1].debutTabPossib=&(possibilites[9]);
    possibThread[1] = CreateThread(NULL,0,valide9x1,&(paramCase[1]),0,NULL);
    //valide1x9(&(paramCase[1]));


    paramCase[2].grille=param->grille;
    paramCase[2].pos=param->pos;
    paramCase[2].debutTabPossib=&(possibilites[18]);
    possibThread[2] = CreateThread(NULL,0,valide1x9,&(paramCase[2]),0,NULL);
    //valide9x1(&(paramCase[2]));

    WaitForMultipleObjects(3,possibThread,TRUE,INFINITE);

    int i=0;
    int j=0;
    for(i=1;i<10;i++){
        param->debutTabPossib[i]=1;
    }
    (param->debutTabPossib)[0]=0;
    for(j=1;j<10;j++){
        if(possibilites[j-1]==0 || possibilites[j+9-1]==0 || possibilites[j+18-1]==0){
            (param->debutTabPossib)[j]=0;
        }else{
            (param->debutTabPossib)[0]+=1;
        }
    }

    free(possibilites);

}

void valide3x3(paramsThreadVerifValidite* param){
    int i=0;
    int ligneGroupe=0;
    int colonneGroupe=0;
    ligneGroupe=param->pos/27;
    colonneGroupe=(param->pos%9)/3;
    int procCase=0;

    for(i=0;i<9;i++){
        param->debutTabPossib[i]=1;
    }

    for(i=0;i<9;i++){
        procCase=ligneGroupe*27+colonneGroupe*3+i%3+(i/3)*9;
        if(param->pos!=procCase && (param->grille)[procCase]!=0){
            if((param->debutTabPossib)[(param->grille)[procCase]-1]!=0){
                (param->debutTabPossib)[(param->grille)[procCase]-1]=0;
            }else if(param->grille[procCase]!=0){
                printf("Erreur : le 3x3 contient deux fois le même nombre : %d\n",(param->grille)[procCase]);
                break;
            }
        }
    }
}


void valide9x1(paramsThreadVerifValidite* param){
    int i=0;
    int ligneGroupe=0;
    ligneGroupe=param->pos/9;
    int procCase=0;

    for(i=0;i<9;i++){
        param->debutTabPossib[i]=1;
    }

    for(i=0;i<9;i++){
        procCase=ligneGroupe*9+i;
        if(param->pos!=procCase && (param->grille)[procCase]!=0){
            if((param->debutTabPossib)[(param->grille)[procCase]-1]!=0){
                (param->debutTabPossib)[(param->grille)[procCase]-1]=0;
            }else if(param->grille[procCase]!=0){
                printf("Erreur : le 9x1 contient deux fois le même nombre : %d\n",(param->grille)[procCase]);
                break;
            }
        }
    }
}


void valide1x9(paramsThreadVerifValidite* param){
    int i=0;
    int colonneGroupe=0;
    colonneGroupe=param->pos%9;
    int procCase=0;

    for(i=0;i<9;i++){
        param->debutTabPossib[i]=1;
    }

    for(i=0;i<9;i++){
        procCase=colonneGroupe+i*9;
        if(param->pos!=procCase && (param->grille)[procCase]!=0){
            if((param->debutTabPossib)[(param->grille)[procCase]-1]!=0){
                (param->debutTabPossib)[(param->grille)[procCase]-1]=0;
            }else if(param->grille[procCase]!=0){
                printf("Erreur : le 1x9 contient deux fois le même nombre : %d\n",(param->grille)[procCase]);
                break;
            }
        }
    }
}
