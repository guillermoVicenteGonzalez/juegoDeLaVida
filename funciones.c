
#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

void presentacion(){
	printf("hola");
}

char **CrearMatriz(int x, int y){
	char **matriz;
	matriz = malloc(sizeof(char *) * x);
	for(int i=0;i<x;i++){
		matriz[i]=malloc(sizeof(char) * y);
	}

	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			matriz[i][j]='-';
		}
	}
	return matriz;
}


void recorrerMatriz(int x, int y,char **matriz){
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			printf("%c",matriz[i][j]);
		}
		printf("\n");
	}
}

int comprobarVivas(int posx, int posy, char ** matriz, int x, int y){
	int contador = 0;
	int limiteSupX, limiteInfX;
	int limiteSupY, limiteInfY;
	int limX, limY;

	limX = x-1;
	limY = y-1;
	limiteSupX = posx+2;
	limiteInfX = posx-1;
	limiteSupY = posy+2;
	limiteInfY = posy-1;

	if(posx == limX){
		limiteSupX = posx+1;
	}
	if(posx == 0){
		limiteInfX = 0;
	}
	if(posy == limY){
		limiteSupY = posx+1;
	}
	if(posy == 0){
		limiteInfY = 0;
	}


	for(int i=limiteInfX;i<limiteSupX;i++){
		for(int j=limiteInfY;j<limiteSupY;j++){
			
			if(!(i == posx && j==posy)){
				

				if(matriz[i][j] == '*'){
					//printf("%d,%d\n",i,j);
					contador++;
				}
			}
		}
	}
	return contador;
}

/*
char **juego(char **matriz, int filas, int columnas){
	char **matrizAux = CrearMatriz(filas,columnas);
	int cont;

	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			cont = comprobarVivas(i,j,matriz,filas,columnas);
			if(cont >1 && cont < 4){
				matrizAux[i][j]='*';
			}else{
				matrizAux[i][j]='-';
			}
		}
	}
	return matrizAux;
}

void juego(char **matriz, int filas, int columnas){
	char **matrizAux = CrearMatriz(filas,columnas);
	int cont;

	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			cont = comprobarVivas(i,j,matriz,filas,columnas);
			if(cont >1 && cont < 4){
				matrizAux[i][j]='*';
			}else{
				matrizAux[i][j]='-';
			}
		}
	}

	//libero memoria
	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			free(matriz[i][j]);
		}
	}
	free(matriz);
	matriz = matrizAux;

}*/

void juego(char **matriz, int filas, int columnas){
	char matrizAux[filas][columnas];
	int cont = 0;


	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			cont = comprobarVivas(i,j,matriz,filas,columnas);

			if(matriz[i][j] == '*'){
				if(cont >1 && cont <4){
					//tiene entre 2 y 3 vecinas vivas
					matrizAux[i][j] = '*';
				}else{
					matrizAux[i][j] = '-';
				}
			}else{
				if(cont == 3){
					matrizAux[i][j] = '*';
				}else{
					matrizAux[i][j] = '-';
				}
			}
		}
	}


	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			matriz[i][j] = matrizAux[i][j];
		}
	}
}
