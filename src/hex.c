#include <stdio.h>
#include <stdlib.h>
#include <string.h>

define SIZE 14

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

typedef struct {
    piece right;
    piece left;
} bridge;

/* Returns a char pointer pointer which will be
 * the 14x14 board for the hex game. */
char** create_board () {
    char** board;
    int lin, col;
    
    board = malloc(SIZE * sizeof(char*));
    for (lin = 0; lin < SIZE; lin++) {
        board[lin] = malloc(SIZE * sizeof(char));
        for (col = 0; col < SIZE; col++)
            board[lin][col] = '-';
    }
    
    return board;
}

piece check_brigdes (char** board, bridge* bridges, int limit) {
    int i, failed;
    failed.lin = failed.col = -1;
    
    for (i = 0; i < limit; i++) {
        if (board[bridges[i].right.lin][bridges[i].right.col] == p) {
            board[bridges[i].left.lin][bridges[i].left.col] =  b;
            return (bridges[i].left);
        }
        
        if (board[bridges[i].left.lin][bridges[i].left.col] ==  p) {
            board[bridges[i].right.lin][bridges[i].right.col] = b;
            return (bridges[i].right);
        }
    }
    
    return failed;
}

int** flood (char** board) {
    int **aux, i;
    aux = malloc(SIZE * sizeof(int*));
    for (i = 0; i < SIZE; i++)
        aux[i] = calloc(SIZE, sizeof(int));


    
}

void priority(char** board, piece pos, piece *plays, int limit) {
    int i, j, k, opposite;
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
