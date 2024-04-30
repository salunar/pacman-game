#ifndef _PACMAN_H_
#define _PACMAN_H_
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define BOMB 'b'

void move (char direction);
int finished();
int isdirection(char direction);
void ghost();
int findway(int xactual, int yactual, int* xdestiny, int* ydestiny);
int updateposition(int* xorigin, int* yorigin, int xdestiny, int ydestiny);
void pillexplodes1();
void pillexplodes2(int x, int y, int sumx, int sumy, int amount);
#endif