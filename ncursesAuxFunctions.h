#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcionesJuegoVida.h"

typedef struct position{
    int x;
    int y;
}position;

typedef struct dimensions{
    int rows;
    int cols;
}dimensions;


void showArrayNcurses(WINDOW *win, char **array, int rows, int cols);
void squareSelection(WINDOW *win, char **array, int rows, int cols, WINDOW *background, position backgroundDimensions);
position printCenteredTextH(WINDOW *win,int win_width, int height,char *msg);
position centerWindow(int max_x, int max_y, int win_x, int win_y);
position selectionMenu(WINDOW *win, int win_width, int win_height, int margin, int max_rows, int max_cols);
void playGameNcurses(char **array, int rows, int cols, WINDOW *win, int delay);
