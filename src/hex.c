#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** create_board () {
    int **board, lin, col;
    board = malloc(14 * sizeof(int*));
    for (lin = 0; lin < 14; lin++) {
        board[lin] = malloc(14 * sizeof(int));
        for (col = 0; col < 14; col++)
            board[lin][col] = '-';
    }
    return board;
}

int main (int argc, char** argv) {
    int **board;
    board = create_board();
    if (argv[1][0] == 'b');
}
