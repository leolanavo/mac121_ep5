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

void check_path(int** matrix, char** board, int line, int col, char color, int x) {
    if (board[i][j] == color) {
        if ()
    }
    else return;
}

int decision_value (char** board, char color) {
    int i, j, **aux;
    
    aux = malloc(size * sizeof(int*));
    for (i = 0; i < size; i++) {
        aux[i] = malloc(size * sizeof(int));
        for (j = 0; j < size; j++)
            aux[i][j] = -1;
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (board[i][j] == '-' && aux[i][j] == -1) 
                aux[i][j] = i;
            else if (board[i][j] == color) {
                aux[i][j] = i;
                check_path (aux, board, i, j, color, i);
            }
        }
    }

}

void priority(char** board, piece pos, piece *plays, int limit) {

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
        plays[count].value = 0;
        count++;
    } 
    
    if (pos.line < size && pos.col < size) {
        plays[count].lin = pos.lin + 1;
        plays[count].col = pos.col + 1;
        plays[count].value = 3;
        count++;
    }
    
    if (pos.line > 1 && pos.col < size) {
        plays[count].lin = pos.lin - 2;
        plays[count].col = pos.col + 1;
        plays[count].value = 1;
        count++;
    }

    if (pos.line > 0 && pos.col < size - 1) {
        plays[count].lin = pos.lin - 1;
        plays[count].col = pos.col + 2;
        plays[count].value = 2;
        count++;
    }

    if (pos.line < size - 1) {
        plays[count].lin = pos.lin + 2;
        plays[count].col = pos.col;
        plays[count].value = 4;
        count++;
    }

    if (pos.line > 1 && pos.col > 1) {
        plays[count].lin = pos.lin - 2;
        plays[count].col = pos.col + 2;
        plays[count].value = 5;
        count++;
    }

    priority(board, pos, plays, count);

}


int main (int argc, char** argv) {
    int **board;
    board = create_board();
    if (argv[1][0] == 'b');
}
