#include <windows.h>
#include <stdio.h>
#include "sudoku.h"

#define SOLVE_BUTTON 1
#define GEN_BUTTON 2
#define EMPTY_BUTTON 3
#define DEBUG_BUTTON 4

// Toutes les ressources sont ici : http://msdn.microsoft.com/en-us/library/windows/desktop/ms632586%28v=vs.85%29.aspx

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void gererActions(HWND, UINT, WPARAM, LPARAM);
void FillWindows(HWND);

/* Quelques variables globales */
char szClassName[ ] = "SudokuSolver";
HINSTANCE globHInstance;
HWND hwndButtonSudoku[81];
int grille[81];

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
    HWND hwndButtonGen = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                "Générer",      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                120,         // x position
                10,         // y position
                100,        // Button width
                20,        // Button height
                windowsInstance,     // Parent window
                (HMENU)GEN_BUTTON,
                globHInstance,
                NULL
                );
    HWND hwndButtonClear = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                "Vider",      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                230,         // x position
                10,         // y position
                100,        // Button width
                20,        // Button height
                windowsInstance,     // Parent window
                (HMENU)EMPTY_BUTTON,
                globHInstance,
                NULL
                );
    HWND hwndButtonDebug = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                "Debug",      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                10,         // x position
                40,         // y position
                100,        // Button width
                20,        // Button height
                windowsInstance,     // Parent window
                (HMENU)DEBUG_BUTTON,
                globHInstance,
                NULL
                );
    HWND hwndCredits = CreateWindow(
                "STATIC",
                "NF05 - Projet de Louis et Benjamin",
                SS_SIMPLE | WS_VISIBLE | WS_CHILD,
                140,
                500,
                250,
                30,
                windowsInstance,
                NULL,
                globHInstance,
                NULL
                );

    //HWND hwndButtonSudoku[81]={NULL};

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
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                20+35*(i%9)+j,         // x position
                100+35*(i/9)+k,         // y position
                30,        // Button width
                30,        // Button height
                windowsInstance,     // Parent window
                (HMENU)(10+i),
                globHInstance,
                NULL
                );
    }
}

int updateGrille(int* grille){
    int i=0;
    char tmp[3];
    for(i=0;i<81;i++){
        tmp[0]=grille[i]/10+48;
        tmp[1]=grille[i]%10+48; // ligne utile en mode debug pour afficher le numero de la case
        tmp[2]='\0';
        SetWindowText(hwndButtonSudoku[i],tmp);
    }
    printf("Grille mise a jour\n");
}

int grilleGenDebug(){
    int i=0;
    for(i=0;i<81;i++){
        grille[i]=i;
    }
    updateGrille(grille);
}

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
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


void viderSudoku(){
    int i=0;
    for(i=0;i<81;i++){
        SetWindowText(hwndButtonSudoku[i]," ");
    }
    printf("Grille videe\n");
}


/* Cette fonction va gérer les clics sur les boutons */
void gererActions(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    UINT iId=LOWORD(wParam);
    HWND hCtl=(HWND)lParam;

    switch (iId){
        case SOLVE_BUTTON:
            // Demander à la fonction de résoudre le sudoku
            printf("Appui du bouton resoudre\n");
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
            viderSudoku();
            break;
        default:
            printf("Appui du bouton %d\n",iId);
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
