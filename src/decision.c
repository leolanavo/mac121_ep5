#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int line;
    int col;
    char color;
} piece

typedef struct snode {
    coord* piece;
    struct snode* right;
    struct snode* left;
} node;

node* create_node (coord piece) {
    node* new;
    new = malloc(sizeof(node));
    new->piece = malloc(sizeof(piece));
    new->piece.line = piece.line;
    new->piece.col = piece.col;
    new->piece.color = piece.color;
    new->right = NULL;
    new->left = NULL;
}



