#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int i, j;
    char grid[5][5];
    int num_bombs = 5;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            grid[i][j] = 'X';
        }
    }

    srand(time(NULL));
    while (num_bombs > 0) {
        int x = rand() % 5;
        int y = rand() % 5;
        if (grid[x][y] != 'B') {
            grid[x][y] = 'B';
            num_bombs--;
        }
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}