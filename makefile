programa: pruebaNcurses.c funcionesJuegoVida.o
	gcc pruebaNcurses.c funcionesJuegoVida.o -o programa -lcurses

debug: debug.c funcionesJuegoVida.o
	gcc debug.c funcionesJuegoVida.o -o debug -lcurses

funcionesJuegoVida.o: funcionesJuegoVida.c funcionesJuegoVida.h
	gcc -c funcionesJuegoVida.c funcionesJuegoVida.h