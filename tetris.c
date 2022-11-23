#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"

#define DEFAULT_BOARD_ROWS 20
#define DEFAULT_BOARD_COLUMNS 10
#define INITIAL_DROP_RATE 1 // Seconds per line
#define TICK_RATE 60 // Ticks per second
#define OCCUPIED 1
#define EMPTY 0

static const int O_block[4] = {
                                1,1,
                                1,1, 
                            };

static const int I_block[16] = {
                                0,0,0,0,
                                1,1,1,1, 
                                0,0,0,0, 
                                0,0,0,0
                            };

static const int T_block[9] = {
                                0,1,0,
                                1,1,1, 
                                0,0,0
                            };

static const int L_block[9] = {
                                0,0,1,
                                1,1,1, 
                                0,0,0
                            };

static const int J_block[9] = {
                                1,0,0,
                                1,1,1, 
                                0,0,0
                            };

static const int S_block[9] = {
                                0,1,1,
                                1,1,0, 
                                0,0,0
                            };

static const int Z_block[9] = {
                                1,1,0,
                                0,1,1, 
                                0,0,0
                            };


typedef struct {
    int type;
    int* area;

} Block;

typedef struct {
    int rows;
    int columns;
    int* playarea;
} Gameboard;

typedef struct {
    int score;
    Gameboard* gb;
    Block* currentBlock;
    Block* heldBlock;
} Game;


int init_playarea(Gameboard* gb) {
    gb->rows = DEFAULT_BOARD_ROWS;
    gb->columns = DEFAULT_BOARD_COLUMNS;
    gb->playarea = calloc(gb->rows * gb->columns, sizeof(int));

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
                printf("O");
            }
        }
        printf("\n");
    }
}

int print_game(Game* game) {
    printf(
        "Score: %d\n",
        game->score
    );
    print_gameboard(game->gb);
}

int main(void* argc, void* argv) {
    Game* game = calloc(1, sizeof(Game));
    init_game(game);
    print_game(game);
    return 0;
}