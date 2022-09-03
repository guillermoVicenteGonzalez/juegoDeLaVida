programa: pruebaNcurses.c funcionesJuegoVida.o
	gcc pruebaNcurses.c funcionesJuegoVida.o -o programa -lcurses

funcionesJuegoVida.o: funcionesJuegoVida.c funcionesJuegoVida.h
	gcc -c funcionesJuegoVida.c funcionesJuegoVida.h