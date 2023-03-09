#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define ROWS 10 // nombre de lignes
#define COLS 10 // nombre de colonnes
#define BOMB '*' 
#define CACHE '+'
#define FLAG 'P'


// La structure de données pour représenter une case de la grille
typedef struct tile {
    char bomb; // true si la case est une bombe
    bool hidden; // true si la case est cachée
    int proximity; // nombre de bombes adjacentes à cette case
    bool flag; // true si la case a un drapeau
}tile;

void afficher_grille(tile grille[ROWS][COLS]);
void plant_bomb(tile grille[ROWS][COLS], int num_mines);
void initialize_grille(tile grille[ROWS][COLS]);
int GetInputNumber(const char* message, int min, int max);
int inTable(int i, int  j);
void proximity(tile grille[ROWS][COLS]);
void revelio(tile grille[ROWS][COLS], int i, int j);
void play(tile grille[ROWS][COLS]);
void affiche_win(tile grille[ROWS][COLS]);
void affiche_lose(tile grille[ROWS][COLS]);

int main()
{
    srand(time(NULL));// initialiser le générateur de nombres aléatoires
    tile grille[ROWS][COLS];
    int num_mines = 10;

    // afficher la grille

    initialize_grille(grille);
    plant_bomb(grille, num_mines);
    afficher_grille(grille);
    proximity(grille);
    play(grille);

    return 0;
}

// Affiche la grille actuelle
void afficher_grille(tile grille[ROWS][COLS])
{
    // Affiche le numéro de chaque colonne
    printf("   ");
    for (int i = 0; i < COLS; i++) {
        printf(" %2d ", i + 1);
    }
    printf("\n");
    // Affiche une ligne horizontale
    printf("   ");
    for (int i = 0; i < COLS; i++) {
        printf("----");
    }
    printf("-\n");

    // Affiche chaque ligne de la grille
    for (int i = 0; i < ROWS; i++) {
        printf("%2d |", i + 1);
        for (int j = 0; j < COLS; j++) {
            if (grille[i][j].hidden == true && grille[i][j].flag == true)
                printf(" P |");
            else if (grille[i][j].hidden == false && grille[i][j].bomb == BOMB)
                printf(" %c |", BOMB);
            else if (grille[i][j].hidden == false && grille[i][j].proximity == 0)
                printf("   |");
            else if (grille[i][j].hidden == false && grille[i][j].proximity > 0)
                printf(" %d |", grille[i][j].proximity);
            else {
                printf(" %c |", CACHE);
            }
        }
        printf("\n");
        printf("   ");
        for (int j = 0; j < COLS; j++) {
            printf("----");
        }
        printf("-\n");
    }
}

//place aléatoirement des bombes dans la grille
void plant_bomb(tile grille[ROWS][COLS], int num_mines)
{
    int i, j, count = 0;
    // Boucle jusqu'à ce que le nombre de bombes soit atteint
    while (count < num_mines) {
        // Génère des coordonnées aléatoires pour la position de la bombe
        i = rand() % ROWS;
        j = rand() % COLS;
        if (grille[i][j].bomb != BOMB) {
            grille[i][j].bomb = BOMB;
            count++;
        }
    }
}

//Initialise la grille
void initialize_grille(tile grille[ROWS][COLS])
{
    int i, j;
    // On parcourt toutes les cases de la grille
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            // On initialise chaque case à sa valeur par défaut
            grille[i][j].hidden = true;
            grille[i][j].bomb = false;
            grille[i][j].flag = false;
            grille[i][j].proximity = 0;
        }

    }
}

//Vérifie si la saisie est valide
int GetInputNumber(const char* message, int min, int max)
{
    int input;
    while (1) {
        printf("%s (%d-%d): ", message, min, max);
        int error = scanf_s("%d", &input);
        while (getchar() != '\n');

        if (error != 1) {
            // la saisie n'est pas valide
            printf("Erreur: Veuillez entrer un nombre.\n");
            continue;
        }
        else
            if (input < min || input > max) {
                printf("Erreur: Entrer un nombre entre %d and %d.\n", min, max);
                continue;
            }

        // la saisie est valide
        return input;
    }
}

//Vérifie les coordonnées
int inTable(int i, int  j)
{
    if (i >= 0 && i < ROWS && j >= 0 && j < COLS)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void proximity(tile grille[ROWS][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (grille[i][j].bomb != BOMB) {
                int count = 0;
                // trouve les bombes
                if (inTable(i - 1, j - 1, ROWS, COLS) == 1 && grille[i - 1][j - 1].bomb == BOMB) count++;

                if (inTable(i - 1, j, ROWS, COLS) == 1 && grille[i - 1][j].bomb == BOMB) count++;

                if (inTable(i - 1, j + 1, ROWS, COLS) == 1 && grille[i - 1][j + 1].bomb == BOMB) count++;

                if (inTable(i, j - 1, ROWS, COLS) == 1 && grille[i][j - 1].bomb == BOMB) count++;

                if (inTable(i, j + 1, ROWS, COLS) == 1 && grille[i][j + 1].bomb == BOMB) count++;

                if (inTable(i + 1, j - 1, ROWS, COLS) == 1 && grille[i + 1][j - 1].bomb == BOMB) count++;

                if (inTable(i + 1, j, ROWS, COLS) == 1 && grille[i + 1][j].bomb == BOMB) count++;

                if (inTable(i + 1, j + 1, ROWS, COLS) == 1 && grille[i + 1][j + 1].bomb == BOMB) count++;

                //affiche le nombre de bombe à proximité
                if (count > 0) {
                    grille[i][j].proximity = count;
                }
                else {
                    grille[i][j].proximity = 0;
                }

            }
        }
    }
}

void revelio(tile grille[ROWS][COLS], int i, int j)
{
    // verifier que c'est dans le tableau

    if (inTable(i, j, ROWS, COLS) == 0)
        return;

    //verifier si c'est deja reveal
    if (grille[i][j].hidden == false)
        return;

    //révéler la case
    grille[i][j].hidden = false;

    if (grille[i][j].proximity != 0)
        return;

    //révéler les cases adjacentes

    revelio(grille, i - 1, j - 1);
    revelio(grille, i - 1, j);
    revelio(grille, i - 1, j + 1);
    revelio(grille, i, j - 1);
    revelio(grille, i, j + 1);
    revelio(grille, i + 1, j - 1);
    revelio(grille, i + 1, j);
    revelio(grille, i + 1, j + 1);

}

void play(tile grille[ROWS][COLS])
{
    int row, col, choice;
    while (1) {
        choice = GetInputNumber("Choisir une action : 1 jouer 2 drapeau", 1, 2);
        if (choice == 1) {
            while (1) {

                // Récupère la ligne
                row = GetInputNumber("Entrer le numero de la ligne", 1, ROWS) - 1;
                // Récupère la colonne
                col = GetInputNumber("Entrer le numero de la colonne", 1, COLS) - 1;

                // Vérifie si la case a déjà été jouée
                if (grille[row][col].hidden != true) {
                    printf("Case deja choisie.\n");
                    continue;
                }

                // Vérifie si la case contient une bombe
                if (grille[row][col].bomb == BOMB) {
                    affiche_lose(grille);
                    printf("BOOM! Vous avez perdu.\n");
                    return;
                }
                else {
                    // Vérifie si le joueur a gagné
                    revelio(grille, row, col);
                    if (win(grille) == true)
                    {   
                        affiche_win(grille);
                        printf("BRAVO! Vous avez gagne");
                        return;
                    }
                    afficher_grille(grille);
                }
                break;

            }
        }

        if (choice == 2) {
            while (1) {
                // Récupère la ligne
                row = GetInputNumber("Entrer le numero de la ligne", 1, ROWS) - 1;
                // Récupère la colonne
                col = GetInputNumber("Entrer le numero de la colonne", 1, COLS) - 1;

                if (grille[row][col].hidden != true) {
                    printf("Case deja choisie.\n");
                    continue;
                }

                // Vérifie si la case contient un drapeau
                if (grille[row][col].flag != false) {
                    printf("Drapeau deja choisie.\n");
                    continue;
                }
                if (grille[row][col].hidden == true) {
                    //plante le drapeau
                    grille[row][col].flag = true;
                    afficher_grille(grille);
                 
                }
                break;
            }


        }
     
    }
}

//Vérifie si toutes les cases non minées ont été révélées
int win(tile grille[ROWS][COLS])
{
    int count = 0;//compte le nombre de cases révélées
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (grille[i][j].hidden == false && grille[i][j].bomb == false)
            {
                count++;// on incrémente le compteur
            }
        }
    }
    if (count == 90)
    {
        return true;//le joueur a gagné
    }
    else
    {
        return false;
    }
}

void affiche_win(tile grille[ROWS][COLS])
{

    printf("   ");
    for (int i = 0; i < COLS; i++) {
        printf(" %2d ", i + 1);
    }
    printf("\n");
    printf("   ");
    for (int i = 0; i < COLS; i++) {
        printf("----");
    }
    printf("-\n");

    for (int i = 0; i < ROWS; i++) {
        printf("%2d |", i + 1);
        for (int j = 0; j < COLS; j++) {
            if (grille[i][j].proximity == 0 && grille[i][j].flag == true)
                printf(" X |");
            else
                if (grille[i][j].proximity > 0 && grille[i][j].flag == true)
                    printf(" P |");
                else
                    if (grille[i][j].proximity == true)
                        printf(" * |");
                    else
                    {
                        printf("   |");
                    }
        }
        printf("\n");
        printf("   ");
        for (int j = 0; j < COLS; j++) {
            printf("----");
        }
        printf("-\n");
    }
}

void affiche_lose(tile grille[ROWS][COLS])
{

    printf("   ");
    for (int i = 0; i < COLS; i++) {
        printf(" %2d ", i + 1);
    }
    printf("\n");
    printf("   ");
    for (int i = 0; i < COLS; i++) {
        printf("----");
    }
    printf("-\n");

    for (int i = 0; i < ROWS; i++) {
        printf("%2d |", i + 1);
        for (int j = 0; j < COLS; j++) {
            if (grille[i][j].hidden == true && grille[i][j].flag == true)
                printf(" P |");
            else
                if (grille[i][j].bomb == true)
                    printf(" %c |", BOMB);
                else
                    if (grille[i][j].hidden == true)
                        printf(" %c |", CACHE);
                    else
                        if (grille[i][j].hidden == false && grille[i][j].proximity == 0)
                            printf("   |");
                        else
                            if (grille[i][j].hidden == false && grille[i][j].proximity > 0)
                                printf(" %d |", grille[i][j].proximity);
            
        }
        printf("\n");
        printf("   ");
        for (int j = 0; j < COLS; j++) {
            printf("----");
        }
        printf("-\n");
    }
}

