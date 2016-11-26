#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 14

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

const coord coord_neigh[] = {
    { -2,  1 }, 
    { -1, -1 },
    { -1,  0 },
    { -1,  1 },
    { -1,  2 },
    {  0, -1 },
};

const coord coord_neigh_full[] = {
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

const coord tower_down[] = {
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
};

const coord tower_left[] = {
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
};

const coord tower_up[] = {
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
};

const coord tower_right[] = {
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
};

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

void print_board (char** board) {
    int i, j, count;
    for (i = 0; i < SIZE; i++) {
        for (count = i; count > 0; count--) printf(" ");
        for (j = 0; j < SIZE; j++) printf("%c ", board[i][j]);
        printf("\n");
    }
}

void print_matrix (int** matrix) {
    int i, j, count;
    for (i = 0; i < SIZE; i++) {
        for (count = i; count > 0; count--) printf(" ");
        for (j = 0; j < SIZE; j++) printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int in_board (coord pos) {
    if (pos.lin < 0 || pos.lin >= SIZE) return 0;
    if (pos.col < 0 || pos.col >= SIZE) return 0;
    return 1;
}

void flood_towers(char** board, char color, int** plays) {
    int i, j, flag;
    coord pos;
    
    if (color == 'b') {
        for(i = 2, flag = 1; i < SIZE - 1 && flag == 1; i++, flag = 1)
            if (board[11][i] == color) plays[11][i] = 1;
            else {
                for (j = 0; j < 10; j++) {
                    pos.col = i + tower_down[j].col;
                    pos.lin = 11 + tower_down[j].lin;
                    if (plays[pos.lin][pos.col] < 0) flag = 0;
                }
                if (flag) plays[11][i] = 0;
                else plays[11][i] = -1;
            }
        
        for (i = 1; i < SIZE - 3; i++)
            if (board[2][i] == color) plays[2][i] = 1;
            else {
                for (j = 0; j < 10; j++) {
                    pos.col = i + tower_up[j].col;
                    pos.lin = 2 + tower_up[j].lin;
                    if (plays[pos.lin][pos.col] < 0) flag = 0;
                }
                if (flag) plays[2][i] = 0;
                else plays[2][i] = -1;
            }
    }

    else {
        for(i = 2, flag = 1; i < SIZE - 1 && flag == 1; i++, flag = 1)
            if (board[i][11] == color) plays[i][11] = 1;
            else {
                for (j = 0; j < 10; j++) {
                    pos.col = i + tower_down[j].col;
                    pos.lin = 11 + tower_down[j].lin;
                    if (plays[pos.lin][pos.col] < 0) flag = 0;
                }
                if (flag) plays[i][11] = 0;
                else plays[i][11] = -1;
            }
        
        for (i = 1; i < SIZE - 3; i++)
            if (board[i][2] == color) plays[i][2] = 1;
            else {
                for (j = 0; j < 10; j++) {
                    pos.col = i + tower_up[j].col;
                    pos.lin = 2 + tower_up[j].lin;
                    if (plays[pos.lin][pos.col] < 0) flag = 0;
                }
                if (flag) plays[i][2] = 0;
                else plays[i][2] = -1;
            }
    }
}

void markdown (char** board, coord pos, int** plays, char color) {
    int i;
    coord aux;
    for (i = 0; i < 10; i++) {
        aux.lin = pos.lin + coord_neigh_full[i].lin;
        aux.col = pos.col + coord_neigh_full[i].col;
        if (in_board(aux)) {
            if (board[aux.lin][aux.col] == color)
                markdown(board, aux, plays, color);
            else if (board[aux.lin][aux.col] == '-')
                plays[aux.lin][aux.col] = 0;
            else
                plays[aux.lin][aux.col] = -1;
            }
        }
}

int** flood (char** board, char color) {
    int **plays, i, j;
    coord pos;

    plays = malloc(SIZE * sizeof(int*));
    for (i = 0; i < SIZE; i++) {
        plays[i] = malloc(SIZE * sizeof(int));
            for (j = 0; j < SIZE; j++) plays[i][j] = 4;
    }
   
    board[0][0] = 'p';
    board[1][1] = 'p';
    if(color == 'b') {
        for (i = 0; i < SIZE; i++) {
            if (board[0][i] == '-') plays[0][i] = 0;
            else if (board[0][i] == color) plays[0][i] = 1;
            else plays[0][i] = -1;
        
            if (board[13][i] == '-') plays[13][i] = 0;
            else if (board[13][i] == color) plays[13][i] = 1;
            else board[13][i] = -1;
        }

        for (i = 0; i < SIZE - 1; i++) {
            if (board[1][i] == color) plays[1][i] = 1;
            else if (plays[0][i] == -1 || plays[0][i + 1] == -1) 
                plays[1][i] = -1;
            else plays[1][i] = 0;
        
            if (board[12][i] == color) plays[12][i] = 1;
            else if (plays[13][i] == -1 || plays[13][i + 1] == -1) 
                plays[1][i] = -1;
            else plays[12][i] = 0;
        }
    }
    
    else {
        for (i = 0; i < SIZE; i++) {
            if (board[i][0] == '-') plays[i][0] = 0;
            else if (board[i][0] == color) plays[i][0] = 1;
            else plays[i][0] = -1;
        
            if (board[i][13] == '-') plays[i][13] = 0;
            else if (board[i][13] == color) plays[i][13] = 1;
            else plays[i][13] = -1;
        }
        
        for (i = 0; i < SIZE - 1; i++) {
            if (board[i][1] == color) plays[i][1] = 1;
            else if (plays[i][0] == -1 || plays[i + 1][0] == -1) 
                plays[i][1] = -1;
            else plays[i][1] = 0;
        }
        
        for (i = 1; i < SIZE - 1; i++) {
            if (board[i][12] == color) plays[i][12] = 1;
            else if (plays[i][13] == -1 || plays[i + 1][13] == -1) 
                plays[i][12] = -1;
            else plays[i][12] = 0;
        }
    }
    
    flood_towers(board, color, plays);
    if (color == 'b')
        for (i = 0; i < SIZE; i++, pos.col = i) {
            pos.lin = 0;
            markdown(board, pos, plays, color);
            pos.lin = 13;
            markdown(board, pos, plays, color);
            
        }
    else  
        for (i = 0; i < SIZE; i++, pos.lin = i) {
            pos.col = 0;
            markdown(board, pos, plays, color);
            pos.col = 13;
            markdown(board, pos, plays, color);   
        }
    return plays;
}

int winner(char** board, coord pos, char color, int end, coord *ignore, int *count) {
    int i, j, flag;
    coord next;
    flag = 1;
    for (i = 0; i < 6; i++) {
        next.lin = pos.lin + coord_neigh[i].lin;
        next.col = pos.col + coord_neigh[i].col;
        for (j = count - 1; j >= 0 && flag == 1; j--)
            if (next.col == ignore[j].col && next.lin == ignore[j].lin)
                flag = 0;
        if (in_board(next) && flag)
            if (board[next.lin][next.col] == color) {
                if (color == 'b' && next.lin == destiny) return 1;
                if (color == 'p' && next.col == destiny) return 1;
                ignore[(*count)] =  next;
                (*count)++;
                if (winner(board, next, color, end, ignore, count))
                    return 1;;
            }
        }
    return 0;
}

int main (int argc, char** argv) {
    int **plays, whtwin, blkwin, i;
    char color, enemy, **board;
    coord wht, blk, pos;

    board = create_board();
    color = 0;
    
    if (argc > 1) color = argv[1][0];
    if (color == 'b') enemy = 'p';
    else enemy 'b';

    if (argc > 2 && argv[2][0] == 'd')
        print_board(board);
    plays = flood(board, color);
    print_matrix(plays);
    
    while (1) {
        scanf("%d %d", pos.lin, pos.col);
        if (pos.lin > 0 && pos.lin < 14 && pos.col > 0 && pos.col < 14)
            board[pos.lin][pos.col] = enemy;
            flood(board, color);
    }
    
    for (i = wht.lin = wht.col = blk.lin = blk.col = 0; i < SIZE; 
         i++, blk.lin++, wht.col++) {
        whtwin = winner(board, wht, 'b', 13);
        if (whtwin) {
            printf("b ganhou \n");
            return 0;
        }
        blkwin = winner(board, blk, 'p', 13);
        if (blkwin) {
            printf("p ganhou \n");
            return 0;
        }
    }
    return 0;
}
