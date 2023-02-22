#include <stdio.h>

#define ROWS 10 // nombre de lignes
#define COLS 10 // nombre de colonnes

void afficher_grille(char grille[ROWS][COLS]) {
    printf("   ");
    for (int i = 0; i < COLS; i++) {
        printf(" %2d ", i+1);
    }
    printf("\n");
    printf("   ");
    for (int i = 0; i < COLS; i++) {
        printf("----");
    }
    printf("-\n");

    for (int i = 0; i < ROWS; i++) {
        printf("%2d |", i+1);
        for (int j = 0; j < COLS; j++) {
            printf(" %c |", grille[i][j]);
        }
        printf("\n");
        printf("   ");
        for (int j = 0; j < COLS; j++) {
            printf("----");
        }
        printf("-\n");
    }
}

int main() {
    char grille[ROWS][COLS];

    // initialiser la grille avec des cases vides
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grille[i][j] = '-';
        }
    }

    // afficher la grille
    afficher_grille(grille);

    return 0;
}
