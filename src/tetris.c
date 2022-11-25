
#include <stdlib.h>
#include "tetris.h"
#include "game.h"
//int argc, char** argv)
int main() {
    Game* game = calloc(1, sizeof(Game));
    init_game(game);
    display_active_tetrimino(game);
    print_game(game);
    
    return 0;
}