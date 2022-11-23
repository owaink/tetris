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
    int heldBlock;
} Game;
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

int init_block(Block* b, int type);
int init_playarea(Gameboard* gb);
int get_square(Gameboard* gb, int row, int column);
int set_square(Gameboard* gb, int row, int column, int occupied);
int is_row_full(Gameboard* game, int row);
int clear_row(Gameboard* gb, int row);
int lower_board(Gameboard* gb, int clearedRow);
int print_gameboard(Gameboard* gb);
int print_game(Game* game);
