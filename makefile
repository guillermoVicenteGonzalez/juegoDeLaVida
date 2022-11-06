game: gameOfLife.c funcionesJuegoVida.o ncursesAuxFunctions.o ipcFunctions.o
	gcc gameOfLife.c funcionesJuegoVida.o ncursesAuxFunctions.o ipcFunctions.o -o game -lcurses

process: process.c
	gcc process.c -o process

ipcFunctions.o: ipcFunctions.c ipcFunctions.h
	gcc -c ipcFunctions.c ipcFunctions.h

programa: pruebaNcurses.c funcionesJuegoVida.o
	gcc pruebaNcurses.c funcionesJuegoVida.o -o programa -lcurses

ncursesAuxFunctions.o: ncursesAuxFunctions.c ncursesAuxFunctions.h 
	gcc -c ncursesAuxFunctions.c ncursesAuxFunctions.h 

debug: debug.c funcionesJuegoVida.o
	gcc debug.c funcionesJuegoVida.o -o debug -lcurses

funcionesJuegoVida.o: funcionesJuegoVida.c funcionesJuegoVida.h
	gcc -c funcionesJuegoVida.c funcionesJuegoVida.h
