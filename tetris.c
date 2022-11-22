#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_BOARD_ROWS 20
#define DEFAULT_BOARD_COLUMNS 10
#define INITIAL_DROP_RATE 1 // Seconds per line

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
    int score;
    int rows;
    int columns;
    int* gameboard;
    struct Block* currentBlock;
    int heldBlock;
} Game;

int init_game(Game* game) {
    game->score = 0;
    game->rows = DEFAULT_BOARD_ROWS;
    game->columns = DEFAULT_BOARD_COLUMNS;
    game->gameboard = (int*) calloc(game->rows * game->columns, sizeof(int));
    game->heldBlock = emptyBlock;
    

    return 0;
}

int is_square_occupied(Game* game, int row, int column) {
    return game->gameboard[row * game->columns + column];
}

int is_row_full(Game* game, int row) {
    int col;

    for(col = 0; col < game->columns; ++col) {
        if(!is_square_occupied(game, row, col)) {
            return 0;
        }
    }
    return 1;
}



int print_game(Game* game) {
    printf(
        "Score: %d\n"
        "Rows: %d\n"
        "Columns: %d\n"
        "Gameboard: \n",
        game->score,
        game->rows,
        game->columns
    );
    int row, column;
    
    for(row = 0; row < game->rows; ++row) {
        //printf("%d: ", row);
        for(column = 0; column < game->columns; ++column) {
            if(is_square_occupied(game, row,column)) {
                printf("X");
            } else {
                printf("O");
            }
        }
        printf("\n");
    }
}

int main(void* argc, void* argv) {
    Game* game;
    game = (Game*) malloc(sizeof(Game));

    init_game(game);
    print_game(game);
    
    return 0;
}