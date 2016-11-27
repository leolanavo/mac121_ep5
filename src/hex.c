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
    coord posi;
    int value;
} piece;

typedef struct {
    coord right;
    coord left;
} bridge;

const coord neigh[] = {
    { -1,  0 }, 
    { -1,  1 },
    {  0, -1 },
    {  0,  1 },
    {  1, -1 },
    {  1,  0 },
};

const coord neigh_full[] = {
    { -1,  0 }, 
    { -1,  1 },
    {  0, -1 },
    {  0,  1 },
    {  1, -1 },
    {  1,  0 },
    { -2,  1 }, 
    { -1, -1 },
    { -1,  2 },
    {  1, -2 },
    {  1,  1 },
    {  2, -1 }
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
        for (count = i; count > 0; count--) fprintf(stderr, " ");
        for (j = 0; j < SIZE; j++) fprintf(stderr, "%c ", board[i][j]);
        fprintf(stderr, "\n");
    }
}

int in_board (coord pos) {
    if (pos.lin < 0 || pos.lin >= SIZE) return 0;
    if (pos.col < 0 || pos.col >= SIZE) return 0;
    return 1;
}

coord secure_bridges (char** board, char color, bridge* bridges, int n) {
    int i;
    coord failed;
    failed.lin = -1;
    failed.col = -1;

    for (i = 0; i < n; i++) {
        if (board[bridges[i].right.lin][bridges[i].right.col] == color)
            return(bridges[i].left);

        else if (board[bridges[i].left.lin][bridges[i].left.col] == color)
            return(bridges[i].right);
    }
    return failed;
}

coord play (char** board, char color, bridge* bridges, int *n, coord last, int end) {
    int i, dist, move;
    coord pos, neighbor;
    
    if (last.lin == -1 && last.col == -1) {
        if(color == 'b') {
            pos.lin = 0;
            pos.col = 13;
        }
        else {
            pos.lin = 13;
            pos.col = 0;
        }
        
    }
    else {
        for (i = 0, dist = 0; i < 12; i++) {
            
            neighbor.lin = last.lin + neigh_full[i].lin;
            neighbor.col = last.col + neigh_full[i].col;

            if (in_board(neighbor)) {
                if (color == 'b' && 13 - neighbor.lin >= 0 && 
                    13 - neighbor.lin > dist 
                    && board[neighbor.lin][neighbor.col] == '-') {
                        dist = 13 - neighbor.lin;
                        pos.lin = neighbor.lin;
                        pos.col = neighbor.col;
                }
                else if (color == 'p' && 13 - neighbor.col >= 0 && 
                         13 - neighbor.col > dist 
                         && board[neighbor.lin][neighbor.col] == '-') {
                    dist = 13 - neighbor.col;
                    pos.lin = neighbor.lin;
                    pos.col = neighbor.col;
                }
            }
        }
    }

    if (i > 5 && i < 12 && end == 0) {
        if (i == 6)  {
            bridges[*n].right.lin = pos.lin - 1;
            bridges[*n].right.col = pos.col + 1;
            bridges[*n].left.lin = pos.lin - 1;
            bridges[*n].left.col = pos.col;
        }
        else if (i == 7)  {
            bridges[*n].right.lin = pos.lin - 1;
            bridges[*n].right.col = pos.col;
            bridges[*n].left.lin = pos.lin;
            bridges[*n].left.col = pos.col - 1;
        }
        else if (i == 8)  {
            bridges[*n].right.lin = pos.lin ;
            bridges[*n].right.col = pos.col + 1;
            bridges[*n].left.lin = pos.lin - 1;
            bridges[*n].left.col = pos.col + 1;
        }
        else if (i == 9)  {
            bridges[*n].right.lin = pos.lin;
            bridges[*n].right.col = pos.col - 1;
            bridges[*n].left.lin = pos.lin + 1;
            bridges[*n].left.col = pos.col - 1;
        }
        else if (i == 10)  {
            bridges[*n].right.lin = pos.lin + 1;
            bridges[*n].right.col = pos.col;
            bridges[*n].left.lin = pos.lin;
            bridges[*n].left.col = pos.col + 1;
        }
        else if (i == 11)  {
            bridges[*n].right.lin = pos.lin + 1;
            bridges[*n].right.col = pos.col - 1;
            bridges[*n].left.lin = pos.lin + 1;
            bridges[*n].left.col = pos.col;
        }
    }

    else if (end) {
        move = 0;
        while (move == 0 && *n < 196)
            if (board[bridges[*n].right.lin][bridges[*n].right.col] == '-'
                && board[bridges[*n].left.lin][bridges[*n].left.col] == '-') {
                pos.lin = bridges[*n].right.lin;
                pos.col = bridges[*n].right.col;
                (*n)++;
                move = 1;
                printf("completando\n");
           }
    }
    
    return pos;
}

int winner(char** board, coord pos, char color, int end, coord *ignore, int *count) {
    int i, j, flag;
    coord next;
    
    flag = 1;
    for (i = 0; i < 6; i++) {
        
        next.lin = pos.lin + neigh[i].lin;
        next.col = pos.col + neigh[i].col;
        
        for (j = *(count) - 1; j >= 0 && flag == 1; j--)
            if (next.col == ignore[j].col && next.lin == ignore[j].lin)
                flag = 0;
        
        if (in_board(next) && flag)
            if (board[next.lin][next.col] == color) {
                if (color == 'b' && next.lin == end) return 1;
                if (color == 'p' && next.col == end) return 1;
                
                ignore[(*count)] =  next;
                (*count)++;
                
                if (winner(board, next, color, end, ignore, count))
                    return 1;
            }
    }
    return 0;
}

int main (int argc, char** argv) {
    int whtwin, blkwin, i, count, pflag, end_flag;
    char color, enemy, **board;
    coord wht, blk, pos, *blacklist, last;
    bridge* bridges;

    board = create_board();
    blacklist = malloc(196 * sizeof(coord));
    bridges = malloc(196 * sizeof(bridge));
    color = count = 0;
    
    if (argc > 1) color = argv[1][0];
    
    if (color == 'b') enemy = 'p';
    else enemy = 'b';

    if (argc > 2 && argv[2][0] == 'd') pflag = 1;
    else pflag = 0;
    
    blkwin = whtwin = count = end_flag = 0;
    pos.lin = pos.col = -1;
    last.lin = last.col = -1;

    while (blkwin == 0 && whtwin == 0) {
        if (scanf("%d %d", &pos.lin, &pos.col));
        
        if (pos.lin >= 0 && pos.lin < 14 && pos.col >= 0 && pos.col < 14 
            && board[pos.lin][pos.col] == '-') {
            board[pos.lin][pos.col] = enemy;
            
            if (pflag) print_board(board);
            
	        pos = secure_bridges(board, enemy, bridges, count);
            
            if (pos.lin == -1 && pos.col == -1)
                pos = play(board, color, bridges, &count, last, end_flag);
            
            if((color == 'b' && pos.lin == 13) || (color == 'p' && pos.col == 13)) {
                end_flag = 1;
                count = 0;
            }
           
            last.lin = pos.lin; last.col = pos.col;
            board[pos.lin][pos.col] = color;

            if (pflag) print_board(board);
            
            for (i = wht.lin = wht.col = blk.lin = blk.col = 0; i < SIZE; 
	             i++, blk.lin++, wht.col++) {
	            
                whtwin = winner(board, wht, 'b', 13, blacklist, &count);
	            if (whtwin) printf("b ganhou \n");
	            
                blkwin = winner(board, blk, 'p', 13, blacklist, &count);
	            if (blkwin) printf("p ganhou \n");
	        }
            printf("%d %d\n", pos.lin, pos.col);
        }
    }

    for (i = 0; i < SIZE; i++) free(board[i]);
    
    free(board);
    free(bridges);
    free(blacklist);
    
    return 0;
}
