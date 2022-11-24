typedef struct {
    __uint8_t row;
    __uint8_t col;
    __uint8_t* squares;
} Block;

typedef struct {
    __uint8_t rows;
    __uint8_t columns;
    __uint8_t* playarea;
    Block* curBlock;
} Gameboard;

typedef struct {
    int score;
    Gameboard* gb;
    Block* heldBlock;
} Game;
static const __uint8_t* O_block[4][2] = {
    { 0, 0},    { 0, 1},
    { 1, 0},    { 1, 1}
    };

static const __uint8_t* I_block[4][2] = {
    {0,-1},{0,0},{0,1},{0,2}
};

static const __uint8_t* T_block[4][2] = {
                {-1, 0},
    { 0,-1},    { 0, 0},    { 0, 1}
};

static const __uint8_t* L_block[4][2] = {
                            {-1, 1},
    { 0,-1},    { 0, 0},    { 0, 1}
};

static const __uint8_t* J_block[4][2] = {
    {-1,-1},
    { 0,-1},    { 0, 0},    { 0, 1}
};


static const __uint8_t* S_block[4][2] = {
                {-1, 0},    {-1, 1},
    { 0,-1},    { 0, 0}
};

static const __uint8_t* Z_block[4][2] = {
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
