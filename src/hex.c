#include <stdio.h>
#include <stdlib.h>
#include <string.h>

define size 14;

/* A struct which will save the position
 * of a piece in the board, and its value. 
 * The value field is either its color or its
 * priority. */
typedef struct {
    int line;
    int col;
    int value;
} piece;

/* Returns a char pointer pointer which will be
 * the 14x14 board for the hex game. */
char** create_board () {
    int **board, lin, col;
    board = malloc(size * sizeof(int*));
    for (lin = 0; lin < size; lin++) {
        board[lin] = malloc(size * sizeof(int));
        for (col = 0; col < size; col++)
            board[lin][col] = '-';
    }
    return board;
}

void priority(int** board, piece pos, piece *plays, int limit) {
    int i;
    piece diff;
    for (i = 0; i < limit; i++)
        if (board[plays[i].line][plays[i].col] == pos.value)
            break;

    if ((i < limit) || 
        (i == limit && board[plays[i].line][plays[i].col] == pos.value)) {
            diff.line = pos.line - plays[i].line;
            diff.col = pos.col - plays[i].col;

    }

}

/* Receives the game's board and a piece which will be
 * used to make a play according to the bridge 
 * strategy. */
piece* bridge_strat_vector (int** board, piece pos) {
    int count, index;
    piece *plays;
    
    count = 0;
    plays = malloc(6 * sizeof(piece));
    
    if (pos.line > 0 && pos.col > 0) {
        plays[count].lin = pos.lin - 1;
        plays[count].col = pos.col - 1;
        count++;
    } 
    
    if (pos.line < size && pos.col < size) {
        plays[count].lin = pos.lin + 1;
        plays[count].col = pos.col + 1;
        count++;
    }
    
    if (pos.line > 1 && pos.col < size) {
        plays[count].lin = pos.lin - 2;
        plays[count].col = pos.col + 1;
        count++;
    }

    if (pos.line > 0 && pos.col < size - 1) {
        plays[count].lin = pos.lin - 1;
        plays[count].col = pos.col + 2;
        count++;
    }

    if (pos.line < size - 1) {
        plays[count].lin = pos.lin + 2;
        plays[count].col = pos.col;
        count++;
    }

    if (pos.line > 1 && pos.col > 1) {
        plays[count].lin = pos.lin - 2;
        plays[count].col = pos.col + 2;
        count++;
    }

    priority(board, pos, plays, count);

}


int main (int argc, char** argv) {
    int **board;
    board = create_board();
    if (argv[1][0] == 'b');
}
