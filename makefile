game: gameOfLife.c funcionesJuegoVida.o ncursesAuxFunctions.o
	gcc gameOfLife.c funcionesJuegoVida.o ncursesAuxFunctions.o -o game -lcurses

programa: pruebaNcurses.c funcionesJuegoVida.o
	gcc pruebaNcurses.c funcionesJuegoVida.o -o programa -lcurses

ncursesAuxFunctions.o: ncursesAuxFunctions.c ncursesAuxFunctions.h 
	gcc -c ncursesAuxFunctions.c ncursesAuxFunctions.h 

debug: debug.c funcionesJuegoVida.o
	gcc debug.c funcionesJuegoVida.o -o debug -lcurses

funcionesJuegoVida.o: funcionesJuegoVida.c funcionesJuegoVida.h
	gcc -c funcionesJuegoVida.c funcionesJuegoVida.h
