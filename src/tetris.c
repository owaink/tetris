
#include <stdlib.h>
#include <ncurses.h>
#include "tetris.h"
#include "game.h"
//int argc, char** argv)
int main() {
    initscr();                  //start cruses mode
    raw();                      //handle userinput directly
    noecho();                   //don't show user input, handle it internally
    keypad(stdscr, TRUE);       //enable arrow keys
    curs_set(0);
    //halfdelay(tenths_of_second);  //wait for input for amount of time
    Game* game = calloc(1, sizeof(Game));
    init_game(game);
    int key = 0;
    while(key != 'q') {
        Tetrimino* t = game->activeTet;
        key = getch();
        switch(key) {
            case KEY_UP:
                move_tetrimino(t, -1, 0);
                break;
            case KEY_LEFT:
                move_tetrimino(t, 0, -1);
                break;
            case KEY_RIGHT:
                move_tetrimino(t, 0, 1);
                break;
            case KEY_DOWN:
                move_tetrimino(t, 1, 0);
                break;
            default:
                set_tetrimino_position(t, 3, 3);
        }
        //display_active_tetrimino(game);
        print_gameboard(game);
    }
    endwin();                   //exit curses mode
    return 0;
}