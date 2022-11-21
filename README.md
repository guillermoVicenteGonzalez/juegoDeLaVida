# juegoDeLaVida

## Introduction
This is an implementation of conway's game of life written in c. It makes use of ncurses to visually represent the cell's state.
It is a passion project i started a long time ago and i only progressed from time to time, so its structure could definitely be better.

## Structure
The project is composed of the following items
  - gameOfLife.c: the main file. Contains the program loop
  - ipcFunctions.c: functions regarding semaphores and message queues are defined here for better modularity
  - nCursesAuxFunctions.c: contains function definitions for reusable blocks of ncurses code specific to this project, suck as menu creations or grid drawings
  - funcionesJuegoVida.c: game of life logic. It was written when on my first year of university so it is the part of the project that needs more work (although it is funcitonal)
  
## Goals
  - [x] Basic functionality
    - [x] game of life logic
    - [x] grid creation menu
    - [x] grid assignation menu
    - [x] controlled exit
    - [x] user exit with buttons
  - [ ] Advanced functionality
    - [ ] pattern loading
    - [ ] program loop
    - [ ] complex menus
    - [ ] grid pause and modification
  - [ ] Extras
    - [ ] Vanity banner loading
    
