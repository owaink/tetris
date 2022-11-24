#include "tetrimino.h"
#include <stddef.h>
#include <stdlib.h>

Tetrimino* create_tetriminio(void) {
    Tetrimino* t = calloc(1, sizeof(Tetrimino));
    if(t == NULL) {
        return NULL;
    }
    init_tetrimino(t);
    return t;
}

int init_tetrimino(Tetrimino* t) {
    t->col = 0;
    t->row = 0;
    t->rotation = NORTH;
    t->type = O_TETRIMINO;
    return 0;
}

int destroy_tetriminio(Tetrimino* t) {
    t->col = NULL;
    t->row = NULL;
    t->type = NULL;
    t->rotation = NULL;
    free(t);
}

int rotate_tetrimino(Tetrimino* t, int direction) {
    if(direction == CLOCKWISE) {
        
    }
}