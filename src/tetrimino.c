#include <string.h>
#include <stdlib.h>
#include "tetrimino.h"
#include "utils.h"

int init_tetrimino(Tetrimino* t) {
    t->col = 0;
    t->row = 0;
    t->squares = calloc(8, sizeof(int));
    memcpy(t->squares, T_TETRIMINO, sizeof(int)*8);
    return 0;
}

int destroy_tetrimino(Tetrimino* t) {
    free(t->squares);
    t->squares = NULL;
    free(t);
    t = NULL;
    return 0;
}

int rotate_tetrimino(Tetrimino* t, int direction) {
    int* i;
    for(i = t->squares; i < t->squares+8; i += 2) {
        swap(i, i+1);
        *i = *(i+direction) * -1;
    }

    return 0;
}

int move_tetrimino(Tetrimino* t, int row, int column) {
    t->col += column;
    t->row += row;
    return 0;
}