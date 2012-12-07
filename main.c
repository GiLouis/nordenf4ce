#include <windows.h>
#include <Windowsx.h>
#include <stdio.h>
#include "sudoku.h"
#include "bruteforce.h"
#include "grilleText.h"
#include <commctrl.h>

#define SOLVE_BUTTON 1
#define GEN_BUTTON 2
#define EMPTY_BUTTON 3
#define DEBUG_BUTTON 4
#define OK_BUTTON 5
#define ANNUL_BUTTON 6
#define TEXT_EDIT 7

// Toutes les ressources sont ici : http://msdn.microsoft.com/en-us/library/windows/desktop/ms632586%28v=vs.85%29.aspx

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProcedure2 (HWND, UINT, WPARAM, LPARAM);
void gererActions(HWND, UINT, WPARAM, LPARAM);
void FillWindowsCase(HWND windowsInstance);
void FillWindows(HWND);

/* Quelques variables globales */
char szClassName[ ] = "SudokuSolver";
char szClassName2[ ] = "Case";
UINT dernierecasecliquee;

HINSTANCE globHInstance;
HWND hwndButtonSudoku[81];
HWND hwndCtl;
char grille[81];

void FillWindowsCase(HWND windowsInstance){

    char* test = valideGrille(grille);
    //trierCroissantPossib(test);

    /*char tmp[2]={0};
    tmp[0]=grille[dernierecasecliquee-10]+48;
    printf("----------------%d %c\n",dernierecasecliquee,tmp[0]);
    if(tmp[0]==48){
        tmp[0]='\0';
    }
    tmp[1]='\0';


    char possib[70]={0};

    int i=0;
    char tmp2[2];

    char * possibilitesTab;
    possibilitesTab = valideUnecase(dernierecasecliquee-10,grille);

    tmp2[0]=(char)possibilitesTab[0]+48;
    tmp2[1]='\0';

    strcat(possib,tmp2);
    strcat(possib," possibilité(s) : ");

    int premiereVirgule=0;
    for(i=1;i<10;i++){
        if(possibilitesTab[i]==1){
            if(premiereVirgule){
                strcat(possib,", ");
            }
            tmp2[0]=i+48;
            tmp2[1]='\0';
            strcat(possib,tmp2);
            premiereVirgule=1;
        }
        printf("%d = %d\n",i,possibilitesTab[i]);
    }
    printf("%s !\n",possib);
    free(possibilitesTab);

    HWND hwndPossib = CreateWindow(
                "STATIC",
                possib,
                SS_SIMPLE | WS_VISIBLE | WS_CHILD,
                10,
                10,
                250,
                30,
                windowsInstance,
                NULL,
                globHInstance,
                NULL
                );
    SendMessage(hwndPossib, WM_SETFONT, (WPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), TRUE);

    hwndCtl = CreateWindow(
                "EDIT",  // Predefined class; Unicode assumed
                tmp,      // Button text
                WS_VISIBLE | WS_CHILD | ES_NUMBER ,  // Styles
                10,         // x position
                30,         // y position
                100,        // Button width
                20,        // Button height
                windowsInstance,     // Parent window
                (HMENU)TEXT_EDIT,
                globHInstance,
                NULL
                );
    SendMessage(hwndCtl, WM_SETFONT, (WPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), TRUE);

    HWND hwndButtonCaseOk = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                "Valider",      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles
                10,         // x position
                60,         // y position
                100,        // Button width
                20,        // Button height
                windowsInstance,     // Parent window
                (HMENU)OK_BUTTON,
                globHInstance,
                NULL
                );
    SendMessage(hwndButtonCaseOk, WM_SETFONT, (WPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), TRUE);*/

}
void creerWindowsCase(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

    dernierecasecliquee = wParam;

    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    HICON hIcon,hIconSM;     /* La ressource de l'icone */

    hIcon = LoadImage(
               hwnd,
               "icon.ico",
               IMAGE_ICON,
               GetSystemMetrics(SM_CXICON),
               GetSystemMetrics(SM_CYICON),
               LR_DEFAULTCOLOR|LR_LOADFROMFILE
               );
    hIconSM = LoadImage(
               hwnd,
               "icon.ico",
               IMAGE_ICON,
               GetSystemMetrics(SM_CXSMICON),
               GetSystemMetrics(SM_CYSMICON),
               LR_DEFAULTCOLOR|LR_LOADFROMFILE
               );


    /* The Window structure */
    wincl.hInstance = hwnd;
    wincl.lpszClassName = szClassName2;
    wincl.lpfnWndProc = WindowProcedure2;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = hIcon;
    wincl.hIconSm = hIconSM;
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground =  (HBRUSH)GetStockObject(WHITE_BRUSH);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl)){}
    HWND about = CreateWindowEx( WS_EX_TOPMOST,
					szClassName2,
					"Infos sur la case",
					WS_OVERLAPPEDWINDOW ,
					CW_USEDEFAULT, CW_USEDEFAULT,// not yet set correctly
					250, 120,// just testing until I get the correct window
					hwnd, NULL,
					hwnd, NULL );

		ShowWindow( about, SW_SHOW );

}

void FillWindows(HWND windowsInstance){
    HWND hwndButtonRes = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                "Résoudre",      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                10,         // x position
                10,         // y position
                100,        // Button width
                20,        // Button height
                windowsInstance,     // Parent window
                (HMENU)SOLVE_BUTTON,
                globHInstance,
                NULL
                );
    SendMessage(hwndButtonRes, WM_SETFONT, (WPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    HWND hwndButtonGen = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                "Générer",      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles
                120,         // x position
                10,         // y position
                100,        // Button width
                20,        // Button height
                windowsInstance,     // Parent window
                (HMENU)GEN_BUTTON,
                globHInstance,
                NULL
                );
    SendMessage(hwndButtonGen, WM_SETFONT, (WPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    HWND hwndButtonClear = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                "Vider",      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles
                230,         // x position
                10,         // y position
                100,        // Button width
                20,        // Button height
                windowsInstance,     // Parent window
                (HMENU)EMPTY_BUTTON,
                globHInstance,
                NULL
                );
    SendMessage(hwndButtonClear, WM_SETFONT, (WPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    HWND hwndButtonDebug = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                "Debug",      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles
                10,         // x position
                40,         // y position
                100,        // Button width
                20,        // Button height
                windowsInstance,     // Parent window
                (HMENU)DEBUG_BUTTON,
                globHInstance,
                NULL
                );
    SendMessage(hwndButtonDebug, WM_SETFONT, (WPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), TRUE);

    int i=0;
    int j=0;
    int k=0;
    char nomBtn[81][2]={0};
    for(i=0;i<81;i++){
        if(i%3==0){
            j+=10;
        }
        if(i%9==0){
            j=0;
        }
        if(i%27==0){
            k+=10;
        }
        nomBtn[i][0]=(char) (i%9)+48+1;
        nomBtn[i][1]='\0';

        hwndButtonSudoku[i] = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                (LPCTSTR) &(nomBtn[i]),      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles
                20+35*(i%9)+j,         // x position
                100+35*(i/9)+k,         // y position
                30,        // Button width
                30,        // Button height
                windowsInstance,     // Parent window
                (HMENU)(10+i),
                globHInstance,
                NULL
                );
        SendMessage(hwndButtonSudoku[i], WM_SETFONT, (WPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), TRUE);

    }
}

int updateGrille(char* grille){
    int i=0;
    char tmp[3];
    for(i=0;i<81;i++){
        tmp[0]=grille[i]/10+48;
        if(tmp[0]==48){
            tmp[0]=' ';
        }
        tmp[1]=grille[i]%10+48; // ligne utile en mode debug pour afficher le numero de la case
        if(tmp[1]==48 && tmp[0]==' '){
            tmp[1]=' ';
        }
        tmp[2]='\0';
        SetWindowText(hwndButtonSudoku[i],tmp);
    }
    //printf("Grille mise a jour\n");
}

int grilleGenDebug(){
    int i=0;
    for(i=0;i<81;i++){
        grille[i]=i;
    }
    updateGrille(grille);
    for(i=0;i<81;i++){
        grille[i]=0;
    }
}

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{

//    InitCommonControls();

    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    HICON hIcon,hIconSM;     /* La ressource de l'icone */

    globHInstance = hThisInstance;

    hIcon = LoadImage(
               hThisInstance,
               "icon.ico",
               IMAGE_ICON,
               GetSystemMetrics(SM_CXICON),
               GetSystemMetrics(SM_CYICON),
               LR_DEFAULTCOLOR|LR_LOADFROMFILE
               );
    hIconSM = LoadImage(
               hThisInstance,
               "icon.ico",
               IMAGE_ICON,
               GetSystemMetrics(SM_CXSMICON),
               GetSystemMetrics(SM_CYSMICON),
               LR_DEFAULTCOLOR|LR_LOADFROMFILE
               );


    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = hIcon;
    wincl.hIconSm = hIconSM;
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground =  (HBRUSH)GetStockObject(WHITE_BRUSH);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Nordenface: Générateur/Solveur de Sudoku",       /* Title Text */
           WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           375,                 /* The programs width */
           544,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    SendMessage(hwnd, WM_SETFONT, (WPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), TRUE);

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


void viderSudoku(int *grille){
    int i=0;
    for(i=0;i<81;i++){
        grille[i] = 0;
        SetWindowText(hwndButtonSudoku[i]," ");
    }
    printf("Grille videe\n");
}


/* Cette fonction va gérer les clics sur les boutons */
void gererActions(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    UINT iId=LOWORD(wParam);
    HWND hCtl=(HWND)lParam;
    char lpch[2];
    switch (iId){
        case SOLVE_BUTTON:
            // Demander à la fonction de résoudre le sudoku
            printf("Appui du bouton resoudre\n");
            resoudreBruteForce(grille);
            break;
        case GEN_BUTTON:
            // Demander à la fonction de générer un sudoku
            printf("Appui du bouton generer\n");
            generer(grille);
            break;
        case DEBUG_BUTTON:
            // Demander à la fonction de générer un sudoku
            printf("Appui du bouton debug\n");
            grilleGenDebug();
            break;
        case EMPTY_BUTTON:
            // Demander à la fonction de vider la grille
            viderSudoku(grille);
            break;
        case OK_BUTTON:
            Edit_GetText(hwndCtl,lpch,2);
            printf("Numero %s a stocker dans la case %d\n",lpch,dernierecasecliquee-10);
            if((lpch[0]-48)>0 && (lpch[0]-48)<=10){
                printf("Enregistre\n");
                grille[dernierecasecliquee-10]=lpch[0]-48;
                updateGrille(grille);
            }else if((lpch[0]-48)==0){
                printf("Supprime\n");
                grille[dernierecasecliquee-10]=0;
                updateGrille(grille);
            }
            DestroyWindow(hwnd);
            break;
        default:
            printf("Appui du bouton %d\n",iId);
            if(iId>=10 && iId<=90){ // Cas d'une case du Sudoku
                creerWindowsCase(hwnd, message, wParam, lParam);
            }
            break;
    }
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            printf("Fenetre generee\n");
            FillWindows (hwnd);         /* On remplit la fenêtre */
            break;
        case WM_COMMAND:
            gererActions(hwnd, message, wParam, lParam); /* Dès qu'un bouton est appuyé, on appelle cette fonction */
            break;
        case WM_DESTROY:
            printf("ByeBye\n");
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
LRESULT CALLBACK WindowProcedure2 (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            printf("Fenetre case generee\n");
            FillWindowsCase(hwnd);         /* On remplit la fenêtre */
            break;
        case WM_COMMAND:
            gererActions(hwnd, message, wParam, lParam); /* Dès qu'un bouton est appuyé, on appelle cette fonction */
            break;
        case WM_DESTROY:
            printf("Case fermee\n");
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
