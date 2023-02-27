#include <stdio.h>

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



void plant_bomb(tile grille[ROWS][COLS], int)
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
            grille[i][j].brick = FALSE;
            grille[i][j].flag = 0;
        }

    }
}

int GetInputNumber(const char* message, int min, int max)
{
    printf("Entrer un nombre entre 0 et %2d", ROWS);
    return;

}

void calculate_numbers(char grille[ROWS][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (grille[i][j] != BOMB) {
                int count = 0;
                // all possibilities to find bomb at proximity
                if (i > 0 && j > 0 && grille[i - 1][j - 1] == BOMB) count++;
                if (i > 0 && grille[i - 1][j] == BOMB) count++;
                if (i > 0 && j < COLS - 1 && grille[i - 1][j + 1] == BOMB) count++;
                if (j > 0 && grille[i][j - 1] == BOMB) count++;
                if (j < COLS - 1 && grille[i][j + 1] == BOMB) count++;
                if (i < ROWS - 1 && j > 0 && grille[i + 1][j - 1] == BOMB) count++;
                if (i < ROWS - 1 && grille[i + 1][j] == BOMB) count++;
                if (i < ROWS - 1 && j < COLS - 1 && grille[i + 1][j + 1] == BOMB) count++;
                //print the number of bomb at proximity
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

void update_grille(char grille[ROWS][COLS]) {
    int i = 0;
    int j = 0;
    int find_bomb = calculate_numbers(char grille[ROWS][COLS]);

    if (i, j == find_bomb)
        return 1;
    if (find_bomb != 0)

        i, j = find_bomb + 1;
    return 0;

    i, j = EMPTY;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (i - 1 != 0 || j - 1 != 0) {
                if ((i + i - 1 >= 0 && i + i - 1 < grille[ROWS][COLS] && j + j - 1 >= 0 && j + j - 1 < grille[ROWS][COLS]) && grille[i + i - 1][j + j - 1] == CACHE)




            }

            void play(tile grille[ROWS][COLS])
            {
                int row, col;
                int conversions;


                while (1) {
                    printf("Entrer les coordonnees de la ligne: ");
                    conversions = scanf_s("%d", &row);
                    while (getchar() != '\n');
                    if (conversions != 1) {
                        printf("Erreur: Entrez un entier pour la ligne.\n");
                        continue;
                    }


                    printf("Entrer les coordonnees de la colonne:");
                    conversions = scanf_s("%d", &col);
                    while (getchar() != '\n');
                    if (conversions != 1) {
                        printf("Erreur: Entrez un entier pour la colonne.\n");

                        continue;
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
                srand(time(NULL));
                tile grille[ROWS][COLS];
                int num_mines = 10;


                // afficher la grille

                initialize_grille(grille);
                plant_bomb(grille, num_mines);
                afficher_grille(grille);
                calculate_numbers(grille);
                play(grille);

                return 0;
            }