#include <ncurses.h>
#include <stdlib.h>
#include "funcionesJuegoVida.h"
#include "ncursesAuxFunctions.h"
#include <unistd.h>
#include <string.h>
#define MAX_LEN 128
#define DELAY 1000


int main(){

/***************************************************
 * Variables
 * ************************************************/

	//windows
	WINDOW *win; //main window
	WINDOW *menu; //menu window
	WINDOW *background; //window for creating backgrounds
	WINDOW *shadow; //window for creating shadows

	//window positions
	position win_pos;
	position menu_pos;

	//window dimensions
	dimensions terminal;
	position arrayDimensions;
	int terminal_h, terminal_w ;//terminal initial dimensions
	int height, width, start_x, start_y, max_win_height, max_win_width;
	int win_h, win_w;
	int margin = 2; //box margin around windows
	int padding = 4; //space between background and the window

	//square selection variables
	bool triggerHighlight; //if true triggers higlight accept message
	bool exit; //when true breaks the square selection loop
	position cursPos;
	wchar_t ch; //used in the square selection getchar loop

	//auxiliary variables
	position posAcc; //accept message position

	//game of life variables
	int max_rows, max_cols;
	int rows, cols;
	char **GOLArray;

/***************************************************
 * PROGRAM SETUP
 * ************************************************/


	rows = 10;
	cols = 5;
	initscr();
   clear();
   noecho();

	if(has_colors() == FALSE){
        endwin();
        fprintf(stderr, "terminal does not support color representation\n");
        //exit(0);
        return 0;
    }
    
    start_color();
    init_pair(1,COLOR_WHITE, COLOR_BLUE);
    init_pair(2,COLOR_RED, COLOR_WHITE);
    init_pair(3,COLOR_BLACK, COLOR_BLACK);


   getmaxyx(stdscr,terminal_h, terminal_w);
   max_win_width  = terminal_w - margin - 2 * padding;
   max_win_height = terminal_h - margin - 2 * padding;
    //this is the same as LINES and COLS


/***************************************************
 * WINDOW CREATION
 * ************************************************/
    //background window
    background = newwin(LINES,COLS,0,0);
    wbkgd(background,COLOR_PAIR(1));
    wrefresh(background);

   //menu window + shadow
   menu_pos = centerWindow(COLS, LINES, 40, 14);
   menu = newwin(14,40, menu_pos.y, menu_pos.x);
   keypad(menu,TRUE);

   shadow = newwin(14,40,menu_pos.y+1, menu_pos.x+2);
   wbkgd(menu,COLOR_PAIR(2));
   box(menu,0,0);
   wrefresh(shadow);
   wrefresh(menu);

/***************************************************
 * ARRAY DIMENSIONS SELECTION AND ARRAY CREATION
 * ************************************************/   
   arrayDimensions = selectionMenu(menu,40,14,margin,max_win_height, max_win_width);
   rows = arrayDimensions.y;
   cols = arrayDimensions.x;

   GOLArray = CrearMatriz(rows,cols);
   //GOLArray = CclrearMatriz(cols,rows);
   //we have to update windows and their colors
   //main window
   win_pos = centerWindow(COLS, LINES, cols+margin, rows+margin);
   win = newwin(rows +margin, cols + margin, win_pos.y,win_pos.x);
   wbkgd(win,COLOR_PAIR(1));
   keypad(win,TRUE);
   box(win,0,0);

   //shadow window
   shadow = newwin(rows+margin, cols + margin, win_pos.y+1, win_pos.x+2);

   //background window
   wbkgd(background,COLOR_PAIR(2));
   posAcc=printCenteredTextH(background,COLS,LINES-2,"Accept");


   //we paint them in order
   wrefresh(background);
   wrefresh(shadow);
   wrefresh(win);
   showArrayNcurses(win,GOLArray,rows,cols);

/***************************************************
 * SQUARE SELECTION
 ***************************************************/ 
   cursPos.x = 1;
   cursPos.y = 1;
   wmove(win,cursPos.y,cursPos.x);

   do{
   	ch = wgetch(win);
   	switch(ch){
   		case KEY_UP:
   			if(cursPos.y == rows && triggerHighlight){
   				//cursPos.y--;
   				curs_set(1);
                wattroff(background,A_STANDOUT);
                wattroff(background,A_BLINK);
   				printCenteredTextH(background,COLS,LINES-2,"Accept");
                wrefresh(background);
                triggerHighlight=false;
   			}else if(cursPos.y > 1){
   				cursPos.y--;
   			}
   			break;

   		case KEY_DOWN:
   			if(cursPos.y < rows){
   				cursPos.y++;
   			}else{
                curs_set(0);
                wattron(background,A_STANDOUT);
                wattron(background,A_BLINK);
   				printCenteredTextH(background,COLS,LINES-2,"Accept");
                wrefresh(background);
                triggerHighlight=true;
   			}
   			break;

   		case KEY_LEFT:
   			cursPos.x--;
   			break;

   		case KEY_RIGHT:
   			cursPos.x++;
   			break;

   		case 10:
   			if(triggerHighlight){
				curs_set(1);
	            wattroff(background,A_STANDOUT);
	            wattroff(background,A_BLINK);
   				printCenteredTextH(background,COLS,LINES-2,"Accept");
	            wrefresh(background);
	            wrefresh(win);
	            exit = true;
   			}else{
	   			if(GOLArray[cursPos.y-1][cursPos.x-1] == '-')
	   				GOLArray[cursPos.y-1][cursPos.x-1] = '*';
	   			else if(GOLArray[cursPos.y-1][cursPos.x-1] == '*')
	   				GOLArray[cursPos.y-1][cursPos.x-1] = '-';
	   		}

   	}
   	mvwprintw(background,0,0,"x:%d y:%d %c",cursPos.x,cursPos.y,GOLArray[cursPos.y-1][cursPos.x-1]);
   	wrefresh(background);
   	showArrayNcurses(win,GOLArray,rows,cols);
   	wmove(win,cursPos.y,cursPos.x);
   	wrefresh(win);
   }while(!exit);

   curs_set(0);
   wprintw(background,"Accept");
   wprintw(background,"Cancel");
   wrefresh(background);
   playGameNcurses(GOLArray, rows,cols,win,500);
    getchar();
    endwin();
    freeArrayMemory(GOLArray,rows,cols);
    return 1;
}

