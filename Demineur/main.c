#include <stdio.h>

#define ROWS 10 // nombre de lignes
#define COLS 10 // nombre de colonnes
#define BOMB 'B' 
#define CACHE '+'
#define EMPTY ' '

#define TRUE 1
#define FALSE 0
typedef short BOOL;

typedef struct tile{
    char bomb;
    BOOL brick;
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



void plant_bomb(tile grille[ROWS][COLS] , int num_mines)
{
    int i, j, count = 0;
    while (count < num_mines) {
        i = rand() % ROWS;
        j = rand() % COLS;
        if (grille[i][j].bomb != 'B') {
            grille[i][j].bomb = 'B';
            count++;
        }
        printf("bomb = %d %d \n", i+1, j+1);
    }
}

void initialize_grille(tile grille[ROWS][COLS])
{
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            grille[i][j].brick = FALSE;
            grille[i][j].flag = 0;
        }
        
    }
}

void play(tile grille[ROWS][COLS])
{
    int row, col;
    int conversions;
    
    while (1) {
        printf("Entrer les coordonnees de la ligne: ");
        conversions = scanf_s("%d", &row);
        if (conversions != 1) {
            printf("Erreur: Entrez un entier pour la ligne.\n");
            return;
        }

        printf("Entrer les coordonnees de la colonne:");
        conversions = canf_s("%d", &col);
        if (conversions != 1) {
            printf("Erreur: Entrez un entier pour la colonne.\n");
            return;
        }

        if (row < 1 || row > ROWS || col < 1 || col > COLS) {
            printf("Erreur. Coordonnees invalides.\n");
            continue;
        }

        if (grille[row - 1][col - 1].flag != 0) {
            printf("Case deja choisie.\n");
            continue;
        }

        if (grille[row - 1][col - 1].bomb == BOMB) {
            grille[row - 1][col - 1].brick = TRUE;
            printf("BOOM! Vous avez perdu.\n");
            afficher_grille(grille);
            return;
        }
        else {
            grille[row - 1][col - 1].flag = 1;
            afficher_grille(grille);
        }

        // Check if player has won
        BOOL won = TRUE;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (grille[i][j].brick == FALSE && grille[i][j].bomb != BOMB) {
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
    tile grille[ROWS][COLS];
    int num_mines = 10;


    // afficher la grille
   
    initialize_grille(grille);
    plant_bomb(grille, num_mines);
    afficher_grille(grille);
    play(grille);

    return 0; 
}
