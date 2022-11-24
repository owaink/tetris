#include "tetrimino.h"
typedef struct {
    int score;
    int rows;
    int columns;
    int* playarea;
    Tetrimino* activeTet;
    Tetrimino* heldTet;
} Game;

Game* create_game();
int init_game(Game* game);
int destory_game(Game* game);

int print_game(Game* game);

int is_row_full(Game* game, int row);
int clear_row(Game* game, int row);
int lower_board(Game* game, int clearedRow);

int get_square(Game* game, int row, int column);
int set_square(Game* game, int row, int column, int occupied);