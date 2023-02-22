#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10
#define MINE '*'
#define EMPTY ' '
#define COVERED '-'

void initialize_board(char board[ROWS][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board[i][j] = COVERED;
        }
    }
}

void add_mines_to_board(char board[ROWS][COLS], int num_mines) {
    int i, j, count = 0;
    while (count < num_mines) {
        i = rand() % ROWS;
        j = rand() % COLS;
        if (board[i][j] != MINE) {
            board[i][j] = MINE;
            count++;
        }
    }
}

void calculate_numbers(char board[ROWS][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j] != MINE) {
                int count = 0;
                if (i > 0 && j > 0 && board[i - 1][j - 1] == MINE) count++;
                if (i > 0 && board[i - 1][j] == MINE) count++;
                if (i > 0 && j < COLS - 1 && board[i - 1][j + 1] == MINE) count++;
                if (j > 0 && board[i][j - 1] == MINE) count++;
                if (j < COLS - 1 && board[i][j + 1] == MINE) count++;
                if (i < ROWS - 1 && j > 0 && board[i + 1][j - 1] == MINE) count++;
                if (i < ROWS - 1 && board[i + 1][j] == MINE) count++;
                if (i < ROWS - 1 && j < COLS - 1 && board[i + 1][j + 1] == MINE) count++;
                if (count > 0) {
                    board[i][j] = '0' + count;
                }
                else {
                    board[i][j] = EMPTY;
                }
            }
        }
    }
}

void print_board(char board[ROWS][COLS]) {
    int i, j;
    printf("  ");
    for (i = 0; i < COLS; i++) {
        printf(" %d ", i);
    }
    printf("\n");
    for (i = 0; i < ROWS; i++) {
        printf("%d ", i);
        for (j = 0; j < COLS; j++) {
            printf("|%c|", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char board[ROWS][COLS];
    int num_mines = 10;

    srand(time(NULL));

    initialize_board(board);
    add_mines_to_board(board, num_mines);
    calculate_numbers(board);
    print_board(board);

    return 0;
}