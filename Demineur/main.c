#include <stdio.h>

#define ROWS 10 // nombre de lignes
#define COLS 10 // nombre de colonnes
#define BOMB 'B' 
#define CACHE '+'
#define EMPTY ' '

void afficher_grille(char grille[ROWS][COLS])
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
            if (grille[i][j] == BOMB) {
                printf(" %c |", CACHE);
            }
            else {
                printf(" %c |", grille[i][j]);
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


void plant_bomb(char grille[ROWS][COLS] , int num_mines)
{
    int i, j, count = 0;
    while (count < num_mines) {
        i = rand() % ROWS;
        j = rand() % COLS;
        if (grille[i][j] != BOMB ) {
            grille[i][j] = BOMB  ;
            count++;
        }
    }
}

void initialize_grille(char grille[ROWS][COLS])
{
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            grille[i][j] = CACHE;
        }
    }
}


int main() 
{
    char grille[ROWS][COLS];
    int num_mines = 10;


    // afficher la grille
   
    initialize_grille(grille);
    plant_bomb(grille, num_mines);
    afficher_grille(grille);

    return 0;
}
