typedef struct {
    int row;
    int col;
    int* squares;
} Tetrimino;

static const int O_TETRIMINO[4][2] = {
    { 0, 0},    { 0, 1},
    { 1, 0},    { 1, 1}
    };

static const int I_TETRIMINO[4][2] = {
    {0,-1},{0,0},{0,1},{0,2}
};

static const int T_TETRIMINO[4][2] = {
                {-1, 0},
    { 0,-1},    { 0, 0},    { 0, 1}
};

static const int L_TETRIMINO[4][2] = {
                            {-1, 1},
    { 0,-1},    { 0, 0},    { 0, 1}
};

static const int J_TETRIMINO[4][2] = {
    {-1,-1},
    { 0,-1},    { 0, 0},    { 0, 1}
};

static const int S_TETRIMINO[4][2] = {
                {-1, 0},    {-1, 1},
    { 0,-1},    { 0, 0}
};

static const int Z_TETRIMINO[4][2] = {
    {-1,-1},    {-1, 0},
                { 0, 0},    { 0, 1}
};

enum DIRECTION {
    CLOCKWISE,
    COUNTERCLOCKWISE
};

int init_tetrimino(Tetrimino* t);
int destroy_tetrimino(Tetrimino* t);

int rotate_tetrimino(Tetrimino* t, int direction);
int move_tetrimino(Tetrimino* t, int row, int column);