#include <stdio.h>
#include <stdlib.h>
#include <string.h>

define SIZE 14

typedef struct {
    int lin;
    int col;
} coord;

/* A struct which will save the position
 * of a piece in the board, and its value. 
 * The value field is either its color or its
 * priority. */
typedef struct {
    coord pos;
    char color;
    int value;
} piece;

typedef struct {
    piece right;
    piece left;
} bridge;

const coord_neigh[] = {
    { -2,  1 }, 
    { -1, -1 },
    { -1,  0 },
    { -1,  1 },
    { -1,  2 },
    {  0, -1 },
    {  0,  1 },
    {  1, -2 },
    {  1, -1 },
    {  1,  0 },
    {  1,  1 },
    {  2, -1 }
};

const coord_tower_down[] = {
    {   2, -3  },
    {   2, -2  },
    {   2,  0  },
    {   2,  1  },
    {   1, -2  },
    {   1, -1  },
    {   1,  0  },
    {   1,  1  },
    {   0, -2  },
    {   0, -1  }
}

const coord_tower_left[] = {
    {  -1, -2  },
    {   0, -2  },
    {   2, -2  },
    {   3, -2  },
    {  -1, -1  },
    {   0, -1  },
    {   1, -1  },
    {   2, -1  },
    {  -1,  0  },
    {   1,  0  }
}
const coord_tower_up[] = {
    {  -2, -1  },
    {  -2,  0  },
    {  -2,  2  },
    {  -2,  3  },
    {  -1, -1  },
    {  -1,  0  },
    {  -1,  1  },
    {  -1,  2  },
    {   0, -1  },
    {   0,  1  },
}
const coord_tower_right[] = {
    {  -3, 2  },
    {  -2, 2  },
    {   0, 2  },
    {   1, 2  },
    {  -2, 1  },
    {  -1, 1  },
    {   0, 1  },
    {   1, 1  },
    {  -1, 0  },
    {   1, 0  },
}
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

int** flood (char** board) {
    int **aux, i;
    aux = malloc(SIZE * sizeof(int*));
    for (i = 0; i < SIZE; i++)
        aux[i] = calloc(SIZE, sizeof(int));
    
    for (i = 0; i < SIZE; i++) {
        if (board[0][i] != 'b') aux[0][i] = 1;
        if (board[13][i] != 'b') aux[13][i] = 1;
    }

    for (i = 0; i < SIZE - 1; i++) {
        if (aux[0][i] == 1 && aux[0][i + 1] == 1)
            aux[1][i] = 1;
        if (aux[13][i] == 1 && aux[13][i + 1] == 1)
            aux[12][i] = 1;
    }
}

int in_board (coord pos) {
    if (pos.lin < 0 || pos.lin >= SIZE) return 0;
    if (pos.col < 0 || pos.col >= SIZE) return 0;
    return 1;
}

void markdown (char** board, coord pos, int** plays, char color) {
    int i;
    coord aux;
    for (i = 0; i < 10; i++) {
        aux.lin = pos.lin + coord_neigh[i].lin;
        aux.col = pos.col + coord_neigh[i].col;
        if (in_board(aux)) {
            if (board[aux.lin][aux.col] == color)
                markdown(board, pos, plays, color);
            if (board[aux.lin][aux.col] == '-')
                plays[aux.lin][aux.col] = 1;
        }
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
