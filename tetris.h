typedef struct {
    int row;
    int col;
    int* squares;
} Block;

typedef struct {
    int rows;
    int columns;
    int* playarea;
    Block* curBlock;
} Gameboard;

typedef struct {
    int score;
    Gameboard* gb;
    Block* heldBlock;
} Game;
static const int O_block[4][2] = {
    { 0, 0},    { 0, 1},
    { 1, 0},    { 1, 1}
    };

static const int I_block[4][2] = {
    {0,-1},{0,0},{0,1},{0,2}
};

static const int T_block[4][2] = {
                {-1, 0},
    { 0,-1},    { 0, 0},    { 0, 1}
};

static const int L_block[4][2] = {
                            {-1, 1},
    { 0,-1},    { 0, 0},    { 0, 1}
};

static const int J_block[4][2] = {
    {-1,-1},
    { 0,-1},    { 0, 0},    { 0, 1}
};


static const int S_block[4][2] = {
                {-1, 0},    {-1, 1},
    { 0,-1},    { 0, 0}
};

static const int Z_block[4][2] = {
    {-1,-1},    {-1, 0},
                { 0, 0},    { 0, 1}
};

int init_block(Block* b, const int* type, int row, int column);
int init_playarea(Gameboard* gb);
int get_square(Gameboard* gb, int row, int column);
int set_square(Gameboard* gb, int row, int column, int occupied);
int is_row_full(Gameboard* game, int row);
int clear_row(Gameboard* gb, int row);
int lower_board(Gameboard* gb, int clearedRow);
int print_gameboard(Gameboard* gb);
int print_game(Game* game);
