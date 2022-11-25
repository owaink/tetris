#include <stdlib.h>
#include <stdio.h>
#include "game.h"

#define DEFAULT_BOARD_ROWS 20 // vertical space for the play area
#define DEFAULT_BOARD_COLUMNS 10 // horizontal space for the play area
#define SAFETY_ROWS 2 // rows above the board

int init_game(Game* game) {
    game->score = 0;
    game->rows = DEFAULT_BOARD_ROWS;
    game->columns = DEFAULT_BOARD_COLUMNS;

    // Allocate memory for the visible play space,
    // plus 2 hidden rows above the top row for safety
    game->playarea = calloc((game->rows+SAFETY_ROWS) * game->columns, sizeof(int));
    if(game->playarea == NULL) {
        return -1;
    }
    game->playarea += (game->columns)*SAFETY_ROWS;

    game->activeTet = calloc(1, sizeof(Tetrimino));
    if(game->activeTet == NULL) {
        return -2;
    }
    init_tetrimino(game->activeTet, (int*)O_TETRIMINO);

    game->heldTet = calloc(1, sizeof(Tetrimino));
    if(game->heldTet == NULL) {
        return -3;
    }
    init_tetrimino(game->heldTet,(int*)NULL_TETRIMINO);

    return 0;
}

int destroy_game(Game* game) {
    game->playarea -= (game->columns)*SAFETY_ROWS;
    free(game->playarea);
    game->playarea = NULL;
    free(game->activeTet);
    game->activeTet = NULL;
    free(game->heldTet);
    game->heldTet = NULL;
    free(game);
    game = NULL;
    return 0;
}

int print_game(Game* game) {
    int row, column;
    printf(
        "Score: %d\n"
        "Rows: %d\n"
        "Columns: %d\n"
        "Gameboard: \n",
        game->score,
        game->rows,
        game->columns
    );
    for(row = 0; row < game->rows; ++row) {
        for(column = 0; column < game->columns; ++column) {
            if(get_square(game, row,column)) {
                printf("X");
            } else {
                printf("~");
            }
        }
        printf("\n");
    }

    return 0;
}

int is_row_full(Game* game, int row) {
    int col;

    for(col = 0; col < game->columns; ++col) {
        if(get_square(game, row, col) == 1) {
            return 0;
        }
    }
    return 1;
}

int clear_row(Game* game, int row) {
    int col;
    for(col = 0; col < game->columns; ++col) {
        set_square(game, row, col, EMPTY);
    }
    return 0;
}

int lower_board(Game* game, int clearedRow) {
    int row, col;
    for(row = clearedRow; row > 0; --row) {
        for(col = 0; col < game->columns; ++col) {
            set_square(game, row, col, get_square(game, row-1, col));
        }
    }
    clear_row(game, 0);
    return 0;
}

int get_square(Game* game, int row, int column) {
    return game->playarea[row * game->columns + column];
}

int set_square(Game* game, int row, int column, int occupied) {
    game->playarea[row * game->columns + column] = occupied;
    return 0;
}

int display_active_tetrimino(Game* game) {
    int* i;
    for(i = game->activeTet->squares; i < game->activeTet->squares+8; i+=2) {
        set_square(game, *i+game->activeTet->row, *(i+1)+game->activeTet->col, ACTIVE);
    }
    return 0;
}

int commit_tetrimino(Game* game, Tetrimino* t) {
    int* i;
    for(i = t->squares; i < t->squares+8; i+=2) {
        set_square(game, *i+game->activeTet->row, *(i+1)+game->activeTet->col, OCCUPIED);
    }
    destroy_tetrimino(t);
    return 0;
}