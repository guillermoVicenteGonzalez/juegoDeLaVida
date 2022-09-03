/*************************************************************
 * Autor: Guillermo Vicente González
 * ***********************************************************/


#include <ncurses.h>
#include <stdlib.h>
#include "funcionesJuegoVida.h"
#include <unistd.h>
#include <string.h>
#define MAX_LEN 128

typedef struct posicion{
    int x;
    int y;
}posicion;
   
void pruebaImprimir(WINDOW *win);
void print_image(FILE *fptr);
void recorrerMatrizNcurses(int x, int y,char **matriz, WINDOW *win);
void juegoNcurses(char **matriz, int filas, int columnas, WINDOW *win);

int main()
{
/***************************************************
 * Variables
 * ************************************************/
    posicion miPosicion;        //estructura de datos para la posicion del cursos
    int height, width, start_x, start_y, max_height, max_width; //dimensiones de la ventana
    int margen = 2;
    int terminal_h, terminal_w;
    WINDOW * win; //puntero a ventana. Es la ventana principal
    WINDOW * fondo;
    WINDOW * menu;

    int caracter; //caracter leido
    char *filename = "banner.txt";
    FILE *fp;
    char msg[] = "introduce las dimensiones del juego";
    int cantidad = 5; //usado para imprimir y tomar la cantidad de filas y columnas de la applicacion

/*************************************************
 * Variables juego de la vida
 * ***********************************************/
    int filas, columnas, max_filas, max_columnas;
    char **matriz;
    int ysize = 300;
    int xsize = 300;
    char c;
    int dimensionx, dimensiony;
    char *cadena;

/***********************************************
 * Programa
 * *********************************************/
    //temporalmente le damos valor a filas y columnas
    //mas tarde seran dinamicas y les dará valor el usuario
    height = 20; //altura de la ventana principal
    width = 40;  //longitud de la ventana principal
    start_x = start_y = margen;
    miPosicion.x=start_x;
    miPosicion.y=start_y;
    filas = width -2;
    columnas = height -2;
    matriz = CrearMatriz(filas,columnas);


    initscr();
    //noecho(); 

    getmaxyx(stdscr,terminal_h, terminal_w); 
    if(has_colors() == FALSE){
        endwin();
        fprintf(stderr, "el terminal no tiene soporte para colores\n");
        exit(0);
    }
    start_color();
    init_pair(1,COLOR_WHITE, COLOR_BLUE);
    init_pair(2,COLOR_RED, COLOR_WHITE);

    //en mi terminal al menos 2 pixeles a lo ancho son 1 a lo alto
    max_height = terminal_h - (2 * margen);
    max_width = terminal_w - (4 * margen);
    //el maximo de filas que puede tener el juego
    //le quitamos 2 porque es lo que ocupa el marco
    max_filas = max_height -2;
    max_columnas = max_width -2;

    //creo el fondo y el menu inicial
    win = newwin(height, width, start_y, start_x);
    keypad(win,TRUE);
    fondo = newwin(terminal_h, terminal_w,0,0);
    menu = newwin(max_height, max_width,margen,2 * margen);
    keypad(menu,TRUE);
    wbkgd(fondo,COLOR_PAIR(1));
    wbkgd(menu,COLOR_PAIR(2));
    wrefresh(fondo);
    box(menu,0,0);


    filas = columnas = 5;
    //creo el texto del menu principal
    mvwprintw(menu,(max_height/3),(max_width-strlen(msg))/2,"%s",msg);
    mvwprintw(menu,(max_height/3)*2 -1,(max_width-strlen(msg))/2,"filas: ");
    mvwprintw(menu,(max_height/3)*2 -1,(max_width-strlen(msg))/2 + strlen("filas: ") + 3,"%d",filas);
    

/**********************************************************
 * Menu de seleccion
 * *******************************************************/

    //si pulsas arriba sube el numero de filas. SI pulsas abajo baja
    //si pulsas enter aceptas el resultado
    //funciona mal porque se quedan los 0 al pasar de 10
    while(10 != (caracter = wgetch(menu))){
        switch (caracter){
            case KEY_UP:
                if(filas < max_filas){
                    filas++;
                }
                break;

            case KEY_DOWN:
                if(filas > 5){
                    filas--;
                }
                break;
        }
        mvwprintw(menu,(max_height/3)*2 -1,(max_width-strlen(msg))/2 + strlen("filas: ") + 3,"%d",filas);
        wrefresh(menu);
    }


    //repito lo mismo para las columnas
    mvwprintw(menu,(max_height/3),(max_width-strlen(msg))/2,"%s",msg);
    mvwprintw(menu,(max_height/3)*2 ,(max_width-strlen(msg))/2,"columnas: ");
    mvwprintw(menu,(max_height/3)*2 ,(max_width-strlen(msg))/2 + strlen("columnas: ") + 3,"%d",columnas);
    wrefresh(menu);
    //si pulsas arriba sube el numero de filas. SI pulsas abajo baja
    //si pulsas enter aceptas el resultado
    //funciona mal porque se quedan los 0 al pasar de 10
    while(10 != (caracter = wgetch(menu))){
        switch (caracter){
            case KEY_UP:
                if(columnas < max_columnas){
                    columnas++;
                }
                break;

            case KEY_DOWN:
                if(columnas > 5){
                    columnas--;
                }
                break;
        }
        mvwprintw(menu,(max_height/3)*2,(max_width-strlen(msg))/2 + strlen("columnas: ") + 3,"%d",columnas);
        wrefresh(menu);
    }

/*********************************************************
 * CREACION DEL TABLERO
 * *******************************************************/



    //opciones ya seleccionadas
    //creo el menu
    //win = newwin(max_height, max_width,margen,2 * margen);
    win = newwin(filas+2, columnas+2,(max_height-(filas+2))/2, (max_width-(columnas+2))/2);
    wbkgd(win,COLOR_PAIR(1));
    wbkgd(fondo,COLOR_PAIR(2));
    box(win,0,0);
    wrefresh(fondo);
    wrefresh(win);
    //empiezo con el juego de la vida
    juegoNcurses(matriz, filas, columnas, win);

    wrefresh(win);
    getchar();
    //box(stdscr,'|','-');


    

    //pruebaImprimir(win);
    //move(0,0);
    wrefresh(win);




    getchar();
    endwin();
    return(0);
}

void movimientoCursor(posicion miPosicion, WINDOW * win){
    int c;

    /*
    registramos un caracter por "ciclo"
    el bucle no sale hasta que se pulse p
    el bucle refresca la pantalla y mueve el cursor en cada ciclo
    La posicion solo se actualiza si se pulsa alguna de las teclas del switch.
    */

    do{
        c = wgetch(win);
        switch(c){
            case KEY_UP:
                miPosicion.y--;
                break;
            case KEY_DOWN:
                miPosicion.y++;
                break;
            case KEY_RIGHT:
                miPosicion.x ++;
                break;
            case KEY_LEFT:
                miPosicion.x--;
                break;
        }

        move(miPosicion.y,miPosicion.x);
        refresh();
    }while(c != 'q');
}

void pruebaImprimir(WINDOW *win){
    for(int i=1; i<39;i++){
        for(int j=1;j<19;j++){
            mvwaddch(win,j,i,'*');
            wrefresh(win);
        }
        wrefresh(win);
    }
}

void print_image(FILE *fptr)
{
    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}

void recorrerMatrizNcurses(int x, int y,char **matriz, WINDOW *win){
    for(int i=1;i<x;i++){
        for(int j=1;j<y;j++){
            //printf("%c",matriz[i][j]);
            mvwaddch(win,j,i,matriz[i][j]);
            wrefresh(win);
        }
        printf("\n");
    }
}

void juegoNcurses(char **matriz, int filas, int columnas, WINDOW *win){
   int caracter;

    while(1){
        sleep(1);
        recorrerMatrizNcurses(filas,columnas,matriz,win);
        wrefresh(win);
        juego(matriz,filas,columnas);
    }
    //'q' != (caracter = getchar())
}