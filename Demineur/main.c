#include <stdio.h>
#include <time.h>

#define ROWS 10 // nombre de lignes
#define COLS 10 // nombre de colonnes
#define BOMB 'X' 
#define CACHE '+'
#define EMPTY ' '

#define TRUE 1
#define FALSE 0
typedef short BOOL;

typedef struct tile {
    char bomb;
    char status;
    BOOL hidden;
    int proximity;
    int flag;
}tile;

void afficher_grille(tile grille[ROWS][COLS])
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

            printf(" %c |", CACHE);

        }
        printf("\n");
        printf("   ");
        for (int j = 0; j < COLS; j++) {
            printf("----");
        }
        printf("-\n");
    }
}

void plant_bomb(tile grille[ROWS][COLS], int num_mines)
{
    int i, j, count = 0;
    while (count < num_mines) {
        i = rand() % ROWS;
        j = rand() % COLS;
        if (grille[i][j].bomb != 'B') {
            grille[i][j].bomb = 'B';
            count++;
        }
        printf("bomb = %d %d \n", i + 1, j + 1);
    }
}

void initialize_grille(tile grille[ROWS][COLS])
{
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            grille[i][j].hidden = FALSE;
            grille[i][j].flag = 0;
        }

    }
}

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

void calculate_numbers(char grille[ROWS][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (grille[i][j] != BOMB) {
                int count = 0;
                // trouve les bombes
                if (i > 0 && j > 0 && grille[i - 1][j - 1] == BOMB) count++;
                if (i > 0 && grille[i - 1][j] == BOMB) count++;
                if (i > 0 && j < COLS - 1 && grille[i - 1][j + 1] == BOMB) count++;
                if (j > 0 && grille[i][j - 1] == BOMB) count++;
                if (j < COLS - 1 && grille[i][j + 1] == BOMB) count++;
                if (i < ROWS - 1 && j > 0 && grille[i + 1][j - 1] == BOMB) count++;
                if (i < ROWS - 1 && grille[i + 1][j] == BOMB) count++;
                if (i < ROWS - 1 && j < COLS - 1 && grille[i + 1][j + 1] == BOMB) count++;
                //affiche le nombre de bombe à proximité
                if (count > 0) {
                    grille[i][j] = '0' + count;
                }
                else {
                    grille[i][j] = EMPTY;
                }
                
            }
        }
    }
}



void play(tile grille[ROWS][COLS])
{
    int row, col;

    while (1){
                 
        // Récupère la ligne
        row = GetInputNumber("Entrer le numero de la ligne", 1, ROWS) - 1;
        // Récupère la colonne
        col = GetInputNumber("Entrer le numero de la colonne", 1, COLS) - 1;

        // Vérifie si les coordonnées sont dans le tableau
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            printf("Erreur: La ligne et la colonne doivent etre entre 1 and %d.\n", ROWS);
            continue;
        }

        if (grille[row-1][col-1].hidden != 0) {
            printf("Case deja choisie.\n");
            continue;
        }

        if (grille[row - 1][col - 1].bomb == BOMB) {
            grille[row - 1][col - 1].hidden = TRUE;
            printf("BOOM! Vous avez perdu.\n");
            afficher_grille(grille);
            return;
        }
        else {
            grille[row - 1][col - 1].hidden = 1;
            afficher_grille(grille);
        }

        // Vérifie si le joueur à gagné
        BOOL won = TRUE;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (grille[i][j].hidden == FALSE && grille[i][j].bomb != BOMB) {
                     won = FALSE;
                     break;
                }
            }
            if (won == FALSE) {
                break;
            }
        }

        if (won) {
            printf("Felicitation! Vous avez gagne!\n");
            afficher_grille(grille);
            return;
        }
    }
}




int main()
{
    srand(time(NULL));
    tile grille[ROWS][COLS];
    int num_mines = 10;

    // affiche la grille

    initialize_grille(grille);
    plant_bomb(grille, num_mines);
    afficher_grille(grille);
    calculate_numbers(grille);

    play(grille);

    return 0;
}