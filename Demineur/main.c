#include <stdio.h>
#include <time.h>

#define ROWS 10 // nombre de lignes
#define COLS 10 // nombre de colonnes
#define BOMB '*' 
#define CACHE '+'


#define TRUE 1
#define FALSE 0
typedef short BOOL;

typedef struct tile {
    char bomb;
    BOOL hidden;
    int proximity;
    int flag;
}tile;

void afficher_grille(tile grille[ROWS][COLS]);
void plant_bomb(tile grille[ROWS][COLS], int num_mines);
void initialize_grille(tile grille[ROWS][COLS]);
int GetInputNumber(const char* message, int min, int max);
int inTable(int i, int  j);
void proximity(tile grille[ROWS][COLS]);
void reveal_case(tile grille[ROWS][COLS], int i, int j);
void play(tile grille[ROWS][COLS]);
void affiche_win(tile grille[ROWS][COLS]);

int main()
{
    srand(time(NULL));
    tile grille[ROWS][COLS];
    int num_mines = 10;

    // affiche la grille

    initialize_grille(grille);
    plant_bomb(grille, num_mines);
    afficher_grille(grille);
    proximity(grille);
    play(grille);

    return 0;
}

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
            if (grille[i][j].hidden == TRUE && grille[i][j].flag == TRUE)
                printf(" P |");
            else if (grille[i][j].hidden == FALSE && grille[i][j].bomb == BOMB)
                printf(" %c |", BOMB);
            else if (grille[i][j].hidden == FALSE && grille[i][j].proximity == 0)
                printf("   |");
            else if (grille[i][j].hidden == FALSE && grille[i][j].proximity > 0)
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

void plant_bomb(tile grille[ROWS][COLS], int num_mines)
{
    int i, j, count = 0;
    while (count < num_mines) {
        i = rand() % ROWS;
        j = rand() % COLS;
        if (grille[i][j].bomb != BOMB) {
            grille[i][j].bomb = BOMB;
            count++;
        }
    }
}

void initialize_grille(tile grille[ROWS][COLS])
{
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            grille[i][j].hidden = TRUE;
            grille[i][j].bomb = FALSE;
            grille[i][j].flag = FALSE;
            grille[i][j].proximity = 0;
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

int inTable(int i, int  j)
{
    if (i >= 0 && i < ROWS && j >= 0 && j < COLS)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

void proximity(tile grille[ROWS][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (grille[i][j].bomb != BOMB) {
                int count = 0;
                // trouve les bombes
                if (inTable(i - 1,j - 1,ROWS,COLS)==1 && grille[i - 1][j - 1].bomb == BOMB) count++;

                if (inTable(i - 1, j, ROWS, COLS) == 1 && grille[i - 1][j].bomb == BOMB) count++;

                if (inTable(i - 1, j + 1, ROWS, COLS) == 1 && grille[i - 1][j + 1].bomb == BOMB) count++;

                if (inTable(i, j - 1, ROWS, COLS) == 1 && grille[i][j - 1].bomb == BOMB) count++;

                if (inTable(i, j +1, ROWS, COLS) == 1 && grille[i][j + 1].bomb == BOMB) count++;

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

void reveal_case(tile grille[ROWS][COLS], int i, int j)
{
    // verifier que c'est dans le tableau

    if (inTable(i ,j ,ROWS ,COLS) == 0)
        return;

    //verifier si c'est deja reveal
    if (grille[i][j].hidden == FALSE)
        return;

    //révéler la case
    grille[i][j].hidden = FALSE;

    if (grille[i][j].proximity != 0)
        return;

    //révéler les cases adjacentes

    reveal_case(grille, i - 1, j - 1);
    reveal_case(grille, i - 1, j);
    reveal_case(grille, i - 1, j + 1);
    reveal_case(grille, i, j - 1);
    reveal_case(grille, i, j + 1);
    reveal_case(grille, i + 1, j - 1);
    reveal_case(grille, i + 1, j);
    reveal_case(grille, i + 1, j + 1);
    
}

void choix(tile grille[ROWS][COLS]) {

}

void play(tile grille[ROWS][COLS])
{
    int row, col;

    while (1){
                 
        // Récupère la ligne
        row = GetInputNumber("Entrer le numero de la ligne", 1, ROWS) - 1;
        // Récupère la colonne
        col = GetInputNumber("Entrer le numero de la colonne", 1, COLS) - 1;

        if (grille[row][col].hidden != TRUE) {
            printf("Case deja choisie.\n");
            continue;
        }

        if (grille[row][col].bomb == BOMB) {
            printf("BOOM! Vous avez perdu.\n");
            afficher_grille(grille);
            return;
        }
        else {
            reveal_case(grille,  row, col);
            if (win(grille) == TRUE)
            {
                printf("BRAVO! Vous avez gagne");
                affiche_win(grille);
                return;
            }
            afficher_grille(grille);
        }

    }
}


int win(tile grille[ROWS][COLS])
{
    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (grille[i][j].hidden == FALSE && grille[i][j].bomb == FALSE)
            {
                count++;
            }
        }
    }
    if (count == 90)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
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
            if (grille[i][j].proximity == FALSE && grille[i][j].flag == TRUE)
                printf(" X |");
            else
            if (grille[i][j].proximity == TRUE && grille[i][j].flag == TRUE)
                printf(" P |");
            else
            if (grille[i][j].proximity == TRUE)
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
