typedef struct paramsThreadVerifValidite paramsThreadVerifValidite;

void generer(char* grille);
char* valideGrille(char* grille);
void verifValidite(paramsThreadVerifValidite* param);
void valide3x3(paramsThreadVerifValidite* param);
void valide9x1(paramsThreadVerifValidite* param);
void valide1x9(paramsThreadVerifValidite* param);
