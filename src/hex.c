#include <stdio.h>
#include <stdlib.h>
#include <string.h>

define size 14;

/* A struct which will save the position
 * of a piece in the board, and its value. 
 * The value field is either its color or its
 * priority. */
typedef struct {
    int lin;
    int col;
    char color;
    int value;
} piece;

/* Returns a char pointer pointer which will be
 * the 14x14 board for the hex game. */
char** create_board () {
    char** board;
    int lin, col;
    
    board = malloc(size * sizeof(char*));
    for (lin = 0; lin < size; lin++) {
        board[lin] = malloc(size * sizeof(char));
        for (col = 0; col < size; col++)
            board[lin][col] = '-';
    }
    
    return board;
}

void priority(char** board, piece pos, piece *plays, int limit) {
    int i, j, k, opposite;

    for (k = 0; k < limit; k++) {
        i = plays[k].line;
        j = plays[k].col;
        if (matrix[i][j] == pos.color) 
            opposite = (pos.value + 3)%6;
    }

    for (k = 0; k < limit; k++) {
        if (board[plays[k].lin][plays[k].col] == '-') { 
            if (plays[k].value == opposite) plays[k].value = 3;
            else if (plays[k].value == (opposite + 1)%6 ) plays[k].value = 2;
            else if (plays[k].value == (opposite + 2)%6 ) plays[k].value = 1;
            else if (plays[k].value == (opposite - 1)%6 ) plays[k].value = 2;
            else if (plays[k].value == (opposite - 2)%6 ) plays[k].value = 1;
            else if (opposite - 2 < 0 && plays[k].value == 4) plays[k].value = 2;
            else if (opposite - 1 < 0 && plays[k].value == 5) plays[k].value = 1;
        }
        else plays[k].value = -1;
    }
}

/* Receives the game's board and a piece which will be
 * used to make a play according to the bridge 
 * strategy. */
piece* bridge_strat_vector (int** board, piece pos) {
    int count;
    piece *plays;
    
    count = 0;
    plays = malloc(6 * sizeof(piece));
    
    if (pos.lin > 0 && pos.col > 0) {
        plays[count].lin = pos.lin - 1;
        plays[count].col = pos.col - 1;
        plays[count].value = 0;
        count++;
    } 
    
    if (pos.lin < size && pos.col < size) {
        plays[count].lin = pos.lin + 1;
        plays[count].col = pos.col + 1;
        plays[count].value = 3;
        count++;
    }
    
    if (pos.lin > 1 && pos.col < size) {
        plays[count].lin = pos.lin - 2;
        plays[count].col = pos.col + 1;
        plays[count].value = 1;
        count++;
    }

    if (pos.lin > 0 && pos.col < size - 1) {
        plays[count].lin = pos.lin - 1;
        plays[count].col = pos.col + 2;
        plays[count].value = 2;
        count++;
    }

    if (pos.lin < size - 1) {
        plays[count].lin = pos.lin + 2;
        plays[count].col = pos.col;
        plays[count].value = 4;
        count++;
    }

    if (pos.lin > 1 && pos.col > 1) {
        plays[count].lin = pos.lin - 2;
        plays[count].col = pos.col + 2;
        plays[count].value = 5;
        count++;
    }

    priority(board, pos, plays, count);
    return (plays);
}

int main (int argc, char** argv) {
    int **board;
    board = create_board();
    if (argv[1][0] == 'b');
}
