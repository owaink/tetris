#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tetris.h"

#define DEFAULT_BOARD_ROWS 20
#define DEFAULT_BOARD_COLUMNS 10
#define INITIAL_DROP_RATE 1 // Seconds per line
#define TICK_RATE 60 // Ticks per second
#define OCCUPIED 1
#define EMPTY 0

// enum TETRIMINO {
//     O_block, // Square block, yellow
//     I_block, // Line block, blue
//     T_block, // T block, purple
//     L_block, // L block, facing right, orange
//     J_block, // Reverse L block, facing left, dark blue
//     S_block, // S block, green
//     Z_block, // Reverse S block, red  
//     emptyBlock, // No Block
// };

enum ROTATION {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

int init_playarea(Gameboard* gb) {
    gb->rows = DEFAULT_BOARD_ROWS;
    gb->columns = DEFAULT_BOARD_COLUMNS;
    gb->playarea = calloc(gb->rows * gb->columns, sizeof(int));
    gb->curBlock = calloc(1, sizeof(Block));
    init_block(gb->curBlock, (const int*) T_block, 2, 2);
    return 0;
}
int init_game(Game* game) {
    game->score = 0;
    game->heldBlock = 0;
    game->gb = calloc(1, sizeof(Gameboard));
    init_playarea(game->gb);

    return 0;
}

int get_square(Gameboard* gb, int row, int column) {
    return gb->playarea[row * gb->columns + column];
}

int set_square(Gameboard* gb, int row, int column, int occupied) {
    gb->playarea[row * gb->columns + column] = occupied;
    return 0;
}

int is_row_full(Gameboard* game, int row) {
    int col;

    for(col = 0; col < game->columns; ++col) {
        if(!get_square(game, row, col)) {
            return 0;
        }
    }
    return 1;
}

int clear_row(Gameboard* gb, int row) {
    int col;
    for(col = 0; col < gb->columns; ++col) {
        set_square(gb, row, col, EMPTY);
    }
    return 0;
}

int lower_board(Gameboard* gb, int clearedRow) {
    int row, col;
    for(row = clearedRow; row > 0; --row) {
        for(col = 0; col < gb->columns; ++col) {
            set_square(gb, row, col, get_square(gb, row-1, col));
        }
    }
    clear_row(gb, 0);
    return 0;
}


int print_gameboard(Gameboard* gb) {
    int row, column;
    printf(
        "Rows: %d\n"
        "Columns: %d\n"
        "Gameboard: \n",
        gb->rows,
        gb->columns
    );
    for(row = 0; row < gb->rows; ++row) {
        for(column = 0; column < gb->columns; ++column) {
            if(get_square(gb, row,column)) {
                printf("X");
            } else {
                printf("~");
            }
        }
        printf("\n");
    }
    return 0;
}

int print_game(Game* game) {
    printf(
        "Score: %d\n",
        game->score
    );
    print_gameboard(game->gb);

    return 0;
}

int init_block(Block* b, const int* type, int row, int column) {
    b->col = column;
    b->row = row;
    b->squares = calloc(8, sizeof(int));
    memcpy(b->squares, type, sizeof(int)*8);
    return 0;
}

int move_block(Block* b, int rowsDown, int columnsRight) {
    b->row += rowsDown;
    b->col += columnsRight;
    return 0;
}
void swap(int* x, int* y) {
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}
int rotate_block(Block* b) {
    int* i;
    for(i = b->squares; i < b->squares+8; i += 2) {
        *i = *i * -1;
        swap(i, i+1);
    }
}

int write_block(Gameboard* gb, Block* b) {
    int* i;
    for(i = b->squares; i < (b->squares+8); i += 2) {
        set_square(gb, b->row + *i, b->col + *(i+1), OCCUPIED);
    }
}

int main(void* argc, void* argv) {
    Game* game = calloc(1, sizeof(Game));
    init_game(game);
    write_block(game->gb, game->gb->curBlock);
    print_game(game);
    
    return 0;
}