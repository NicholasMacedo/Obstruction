#ifndef INCLUDE_A1_H_
#define INCLUDE_A1_H_
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <curses.h> //Used for inch();
#include <stdbool.h> //Used for bool function and variable

int playerAction(char,int);
int placeMove(int,int,int);
bool boardFull ();
void hintPlayer();
void secondaryBoard();
void helpInfo();

#endif  // INCLUDE_A1_H_
