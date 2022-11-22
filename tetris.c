#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_BOARD_ROWS 20
#define DEFAULT_BOARD_COLUMNS 10
#define INITIAL_DROP_RATE 1 // Seconds per line
#define OCCUPIED 1
#define EMPTY 0

enum Tetrimino {
    O_block, // Square block, yellow
    I_block, // Line block, blue
    T_block, // T block, purple
    L_block, // L block, facing right, orange
    J_block, // Reverse L block, facing left, dark blue
    S_block, // S block, green
    Z_block, // Reverse S block, red  
    emptyBlock, // No Block
};

enum Rotation {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

typedef struct {
    int type;
    int rotation;
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
    int heldBlock;
} Game;

int init_playarea(Gameboard* gb) {
    gb->rows = DEFAULT_BOARD_ROWS;
    gb->columns = DEFAULT_BOARD_COLUMNS;
    gb->playarea = (int*) 
                    calloc(gb->rows * gb->columns, sizeof(int));
    return 0;
}
int init_game(Game* game) {
    game->score = 0;
    game->heldBlock = emptyBlock;
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


int print_gb(Gameboard* gb) {
    int row, column;
    printf(
        "Rows: %d\n"
        "Columns: %d\n"
        "Gameboard: \n",
        gb->rows,
        gb->columns
    );
    for(row = 0; row < gb->rows; ++row) {
        //printf("%d: ", row);
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
    print_gb(game->gb);
}

int main(void* argc, void* argv) {
    Game* game = (Game*) calloc(1, sizeof(Game));
    init_game(game);
    set_square(game->gb, game->gb->rows-1,game->gb->columns-1, OCCUPIED);
    set_square(game->gb, 0,0, OCCUPIED);
    print_game(game);
    
    lower_board(game->gb, 10);
    print_game(game);
    return 0;
}