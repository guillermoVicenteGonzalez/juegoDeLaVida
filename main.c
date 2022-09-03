#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
//#include "gfx.h"

#include "funciones.h"

int main(int argc, char const *argv[])
{
	/***************************************************
	 * variables
	 * *************************************************/
	int filas, columnas;
	char **matriz;
	int ysize = 300;
	int xsize = 300;
	char c;
	int dimensionx, dimensiony;


	/***************************************************
	 * programa
	 * ***********************************************/
	filas=atoi(argv[1]);
	columnas=atoi(argv[2]);
	if(argc <= 2){
		printf("no has pasado suficientes argumentos\n");
		return -1;
	}else{
		printf("el numero de argumentos %d\n",argc);
		printf("los argumentos son %d y %d",filas,columnas);
	}
	printf("\n\n");
	matriz = CrearMatriz(filas,columnas);

	/*for(int i=0;i<filas;i++){
		for(int j=0;j<2;j++){
			matriz[i][j]='*';
		}
	}*/
	matriz[0][0] = '*';
	matriz[0][1] = '*';
	matriz[1][0] = '*';
	dimensionx = (xsize/columnas)-2;
	dimensiony = (ysize/filas)-2;



	recorrerMatriz(filas,columnas,matriz);
	printf("\n%d",comprobarVivas(0,1,matriz,filas,columnas));
	printf("\n\nComienza el juego\n\n");
	recorrerMatriz(filas,columnas,matriz);
	printf("\n");
	juego(matriz,filas,columnas);
	recorrerMatriz(filas,columnas,matriz);


/*
		// Open a new window for drawing.
	gfx_open(xsize,ysize,"Example Graphics Program");

	// Set the current drawing color to green.
	gfx_color(0,200,100);

	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			if(matriz[i][j] == '-'){
				gfx_color(200,0,0);
			}else{
				gfx_color(0,200,100);
			}
			gfx_point(i*dimensionx+20,j*dimensiony+20);
		}
	}
	while(1) {
		// Wait for the user to press a character.
		c = gfx_wait();
		gfx_clear();
		juego(matriz,filas,columnas);
		for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			if(matriz[i][j] == '-'){
				gfx_color(200,0,0);
			}else{
				gfx_color(0,200,100);
			}
			gfx_point(i*dimensionx+20,j*dimensiony+20);
		}
	}


		// Quit if it is the letter q.
		if(c=='q') break;
	}
	*/
	return 0;
}