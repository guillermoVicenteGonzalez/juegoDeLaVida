#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "funcionesJuegoVida.h"
#include "ncursesAuxFunctions.h"
#include <ncurses.h>

void showArrayNcurses(WINDOW *win, char **array, int rows, int cols){
	/*
	for(int j=0;j<cols;j++){
		for(int i=0;i<rows;i++){
			//remember: i=rows == Y axis, not x axis
			mvwaddch(win,i+1,j+1,array[i][j]);
		}
	}
	*/
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			//remember: i=rows == Y axis, not x axis
			if(array[i][j] == '*'){
				mvwaddch(win,i+1,j+1,ACS_DIAMOND);
			}else{
				mvwaddch(win,i+1,j+1,array[i][j]);
			}
		}
	}


	
	wrefresh(win);
}

//prints text centered horizontally at the selected height
position printCenteredTextH(WINDOW *win,int win_width, int height,char *msg){
	int middle_x;
	int msgLength;
	position posAcc;

	msgLength = sizeof(msg);
	middle_x = 1 + win_width/2 - (msgLength/2);
	mvwprintw(win,height,middle_x,msg);

	posAcc.x = middle_x;
	posAcc.y = height;

	return posAcc;
}


position centerWindow(int max_x, int max_y, int win_x, int win_y){
	position middlePos; //point on the middle of the screen
	position startPos; //start position of the window

	//I get the middle point of the screen based on its max width and height
	middlePos.x = max_x/2;
	middlePos.y = max_y/2;

	//we want the middle of the window to be in the middle of the screen
	//that means the start position is the middlepos - half the window width/height
	startPos.x = middlePos.x - (win_x/2);
	startPos.y = middlePos.y -(win_y/2);


	//TODO: add a margin parameter
	return startPos;
}


position selectionMenu(WINDOW *win, int win_width, int win_height, int margin, int max_rows, int max_cols){
	position cursorPos;
	position messagePos;
	position dimensions; //stores rows and columns. x = columns and y = rows
	wchar_t ch; //remember, a larger type of datatype is needed. char is not enough
	int filas = 5;
	dimensions.x = dimensions.y = 5;

	messagePos.x = margin +1;
	messagePos.y = (win_height/3);
	mvwprintw(win, messagePos.y,messagePos.x,"enter the number of rows:  %d",dimensions.x);
	getyx(win,cursorPos.y, cursorPos.x);
	wrefresh(win);
	keypad(win,TRUE);

	//we get the rows
	while(10 != (ch = wgetch(win))){
		switch(ch){
			case KEY_UP:
				if(dimensions.y < max_rows){
					dimensions.y++;
				}
				break;

			case KEY_DOWN:
				if(dimensions.y > 5){
					dimensions.y --;
				}
				break;
		}
		mvwprintw(win,cursorPos.y,cursorPos.x-1,"%d",dimensions.y);
		wrefresh(win);
	}

	mvwprintw(win, messagePos.y+2,messagePos.x,"enter the number of columns:  %d",dimensions.x);
	wrefresh(win);
	getyx(win,cursorPos.y, cursorPos.x);

	while(10 != (ch = wgetch(win))){
		switch(ch){
			case KEY_UP:
				if(dimensions.x < max_cols){
					dimensions.x++;
				}
				break;

			case KEY_DOWN:
				if(dimensions.x > 5){
					dimensions.x --;
				}
				break;
			}
			mvwprintw(win,cursorPos.y,cursorPos.x-1,"%d",dimensions.x);
			wrefresh(win);
		}

	return dimensions;
}

void playGameNcurses(char **array, int rows, int cols, WINDOW *win, int delay){
   int caracter;

    while(1){
        fflush(stdout);
        napms(delay);
        //recorrerMatrizNcurses(filas,columnas,matriz,win);
         showArrayNcurses(win,array,rows,cols);
        wrefresh(win);
        juego(array,rows,cols);
    }
}

//void createMenu(WINDOW *menu, int max_w, int max_h,)

int checkAlive(char **aray, int rows, int cols){

}

