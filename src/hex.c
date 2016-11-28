#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 14

/* Sturct to store a matrix's position. */
typedef struct {
    int lin;
    int col;
} coord;

/* Struct to store the matrix's positions
 * of the two tiles which connect to 
 * pieces by a bridge. */
typedef struct {
    coord right;
    coord left;
} bridge;

/* Vector of offsets that added to a position
 * in the matrix, allows the program to find
 * its immediate neighbors. */
const coord neigh[] = {
    { -1,  0 }, 
    { -1,  1 },
    {  0, -1 },
    {  0,  1 },
    {  1, -1 },
    {  1,  0 },
};

/* Vector of offsets that added to a position
 * in the matrix, allows the program to find
 * its immediate neighbors and positions which 
 * are connected with the original position 
 * by a bridge. */
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

/* Vector of offsets that added to a position
 * in the matrix, allows the program to find 
 * the positions that makes the bridge to
 * connect two positions. */
const bridge bdg_offset[] = {
    { {-1, 1}, {-1, 0} },
    { {-1, 0}, { 0,-1} },
    { { 0, 1}, {-1, 1} },
    { { 0,-1}, { 1,-1} },
    { { 1, 0}, { 0, 1} },
    { { 1,-1}, { 1, 0} },
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

/* Receives a matrix and will print it according
 * to the specification. */
void print_board (char** board) {
    int i, j, count;
    for (i = 0; i < SIZE; i++) {
        for (count = i; count > 0; count--) fprintf(stderr, " ");
        for (j = 0; j < SIZE; j++) fprintf(stderr, "%c ", board[i][j]);
        fprintf(stderr, "\n");
    }
}

/* Receives a position in the matrix. Returns
 * 1 if the position is in the matrix,
 * 0 otherwise. */
int in_board (coord pos) {
    if (pos.lin < 0 || pos.lin >= SIZE) return 0;
    if (pos.col < 0 || pos.col >= SIZE) return 0;
    return 1;
}

/* Receives the board of the game, the color which the
 * program is playing with, a vector with all the bridges 
 * and the size of this vector.
 * 
 * Checks with the opponent tried to block a bridge and
 * secure that bridge by placing a piece in the proper
 * position. 
 *
 * Return a valid position with a bridge needs
 * to be secured, (-1,-1), otherwise.*/
coord secure_bridges (char** board, char color, bridge* bridges, int n) {
    int i;
    coord failed;
    
    failed.lin = -1;
    failed.col = -1;

    for (i = 0; i < n; i++) {
        if (board[bridges[i].right.lin][bridges[i].right.col] == color
            && board[bridges[i].left.lin][bridges[i].left.col] == '-')
            return(bridges[i].left);

        else if (board[bridges[i].left.lin][bridges[i].left.col] == color 
            && board[bridges[i].right.lin][bridges[i].right.col] == '-')
            return(bridges[i].right);
    }
    return failed;
}

/* Receives the board of the game, the color which the
 * program is playing with, a vector with all the bridges
 * the first empty space of this vector, the position of
 * the last move and a flag which signals that it can 
 * start just completing the bridges to finish the game.
 * 
 * Retruns the position where my piece should be put
 * according to the bridge strategy defined in the report.
 * 
 * If the function did a bridge play, it inserts on the vector
 * the two positions that connect the last piece and the current
 * one that's going to be placed. */
coord play (char** board, char color, bridge* bridges, int *n, coord last, int end) {
    int i, dist, move, index;
    coord pos, aux;

    if (last.lin == -1 && last.col == -1) {
            pos.lin = 13;
            pos.col = 0;
    }

    else {
        for (i = 0, dist = 14; i < 12; i++) {
            
            aux.lin = last.lin + neigh_full[i].lin;
            aux.col = last.col + neigh_full[i].col;

            if (in_board(aux)) {
                if (color == 'b' && 13 - aux.lin >= 0 && 
                    13 - aux.lin < dist 
                    && board[aux.lin][aux.col] == '-') {
                        dist = 13 - aux.lin;
                        pos.lin = aux.lin;
                        pos.col = aux.col;
                        move = i;
                }
                else if (color == 'p' && 13 - aux.col >= 0 && 
                         13 - aux.col < dist 
                         && board[aux.lin][aux.col] == '-') {
                    dist = 13 - aux.col;
                    pos.lin = aux.lin;
                    pos.col = aux.col;
                    move = i;
                }
            }
        }
    }

    if (move > 5 && move < 12 && end == 0) {
        index = move - 6;
        bridges[*n].right.lin = last.lin + bdg_offset[index].right.lin;
        bridges[*n].right.col = last.col + bdg_offset[index].right.col;
        bridges[*n].left.lin = last.lin + bdg_offset[index].left.lin;
        bridges[*n].left.col = last.col + bdg_offset[index].left.col;
        (*n)++;
    }

    else if (end) {
        move = 0;
       
        while (move == 0 && *n < 196) {
            pos.lin = bridges[*n].right.lin;
            pos.col = bridges[*n].right.col;
            aux.lin = bridges[*n].left.lin;
            aux.col = bridges[*n].left.col;
            if (board[pos.lin][pos.col] == '-' 
                || board[aux.lin][aux.col] == '-') {
                move = 1;
            }
            (*n)++;
        }
    }
    return pos;
}

/* Receives the board of the game, a color of piece, the end
 * line or column (depends the color, but the value is alway
 * set to be 13), a vector of position that should be ignored
 * when evaluting the path, and the size of this vector.
 *
 * Returns 1 if a player managed to win the game with the given
 * color, 0 otherwise. */
int winner(char** board, coord pos, char color, int end_pos, coord *ignore, int count) {
    int i, j, flag;
    coord next;
    
    ignore[count] = pos;
    for (i = 0; i < 6; i++) {
        
        next.lin = pos.lin + neigh[i].lin;
        next.col = pos.col + neigh[i].col;
        
        for (j = count - 1, flag = 1; j >= 0 && flag == 1; j--)
            if (next.lin == ignore[j].lin && next.col == ignore[j].col)
                flag = 0;
        
        if (in_board(next) && flag)
            if (board[next.lin][next.col] == color) {
                if (color == 'b' && next.lin == end_pos) return 1;
                if (color == 'p' && next.col == end_pos) return 1;
                
                count++;
                if (winner(board, next, color, end_pos, ignore, count))
                    return 1;
            }
    }
    return 0;
}

/* Receives the color which the program will play with, and
 * if the second argument of the command line is 'd', it will
 * print the board after every play made by both players. */
int main (int argc, char** argv) {
    int whtwin, blkwin, i, count, pflag, end_flag, first;
    char color, enemy, **board;
    coord wht, blk, pos, *blacklist, last;
    bridge *bridges;

    board = create_board();
    bridges = malloc(196 * sizeof(bridge));
    color = count = 0;
    
    if (argc > 1) color = argv[1][0];

    if (argc > 2 && argv[2][0] == 'd') pflag = 1;
    else pflag = 0;
    
    if (color == 'b') {
        enemy = 'p';
        last.lin = 0; last.col = 13;
        board[last.lin][last.col] = color;
        first = 1;
        printf("%d %d\n", last.lin, last.col);
        if (pflag) print_board(board);
    }
    else {
        enemy = 'b';
        first = 0;
        last.lin = last.col = -1;
    }

    blkwin = whtwin = count = end_flag = 0;
    pos.lin = pos.col = -1;
    

    while (blkwin == 0 && whtwin == 0) {

        if (scanf("%d %d", &pos.lin, &pos.col));
        
        if (first == 0) {
            first = -1;
            if (pos.lin == 0 && pos.col == 13) {
                color = 'b'; enemy = 'p';
                board[pos.lin][pos.col] = color;
                printf("%d %d\n", pos.lin, pos.col);
                if (pflag) print_board(board);
            }
        }

        else if (first == 1 && pos.lin == last.lin && pos.col == last.col) {
            first = -1;
            color = 'p'; enemy = 'b';
            board[pos.lin][pos.col] = color;
        }
        
        
        else if (pos.lin >= 0 && pos.lin < 14 && pos.col >= 0 && pos.col < 14 
            && board[pos.lin][pos.col] == '-') {
            board[pos.lin][pos.col] = enemy;
            
            for (i = wht.lin = wht.col = blk.lin = blk.col = 0; i < SIZE; 
                 i++, blk.lin++, wht.col++) {
                
                blacklist = malloc(196 * sizeof(coord));
                whtwin = winner(board, wht, 'b', 13, blacklist, 0);
                if (whtwin) {
                    printf("b ganhou \n");
                    break;
                }
                free(blacklist);

                blacklist = malloc(196 * sizeof(coord));
                blkwin = winner(board, blk, 'p', 13, blacklist, 0);
                if (blkwin) {
                    printf("p ganhou \n");
                    break;
                }
                free(blacklist);
            }
            
            pos = secure_bridges(board, enemy, bridges, count);
            
            if (pos.lin == -1 && pos.col == -1) {
                pos = play(board, color, bridges, &count, last, end_flag);
                last.lin = pos.lin; last.col = pos.col;
            }
            
            if((color == 'b' && pos.lin == 13) || (color == 'p' && pos.col == 13)) {
                end_flag = 1;
                count = 0;
            }
            
            board[pos.lin][pos.col] = color;
            if (pflag) print_board(board);
            printf("%d %d\n", pos.lin, pos.col);
        }
    }

    for (i = 0; i < SIZE; i++) free(board[i]);
    
    free(board);
    free(blacklist);
    free(bridges);
    
    return 0;
}
