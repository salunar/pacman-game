#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacman.h"
#include "map.h"
#include "ui.h"

MAP m;
POSITION hero;

int havepill = 0;

int updateposition(int* xorigin, int* yorigin, int xdestiny, int ydestiny){
    *xorigin = xdestiny;
    *yorigin = ydestiny;
    return 1;
}

int findway(int xactual, int yactual, int* xdestiny, int* ydestiny) {
    int options [4][2] = {
        {xactual -1, yactual},
        {xactual +1, yactual},
        {xactual, yactual -1},
        {xactual, yactual +1}
    };
    srand(time(0));
    for(int i = 0; i < 10; i++){
        int position1 = rand () % 4;
        if(canwalk(&m, GHOST, options[position1][0], options[position1][1])){
            *xdestiny = options[position1][0];
            *ydestiny = options[position1][1];
            return 1;
        }
    }
    return 0;
}

void ghost(){
    MAP copy;
    copymap(&copy, &m);

    for(int i = 0; i < m.lines; i++){
        for(int j = 0; j < m.columns; j++){
            if(copy.matrix[i][j] == GHOST){
                int xdestiny;
                int ydestiny;
                int found = findway(i, j, &xdestiny, &ydestiny);

                if(found){
                    walkmap(&m, i, j, xdestiny, ydestiny);
                }
            }
        }
    }
    clearmap(&copy);    
}

int finished() {
    POSITION pos;
    int pacmaminmap = findmap(&m, &pos, HERO);
    return !pacmaminmap;
}

int isdirection(char direction){
    return direction == 'w' || 
        direction == 'a' || 
        direction == 's' || 
        direction == 'd';
}

void move(char direction) {

    if(!isdirection(direction))
        return;

    int nextx = hero.x;
    int nexty = hero.y;
    
    switch(direction){ 
        case up:
            nextx--;
            break;
        case left:
            nexty--;
            break;
        case down:
            nextx++;
            break;
        case right:
            nexty++;
            break;
    }
    if(!canwalk(&m, HERO, nextx, nexty))
        return;
    if(ischaracter(&m, PILL, nextx, nexty)){
        havepill = 1;
    }
    walkmap(&m, hero.x, hero.y, nextx, nexty);
    updateposition(&hero.x, &hero.y, nextx, nexty);
}
void pillexplodes1(){
    if(!havepill) return;
    pillexplodes2(hero.x, hero.y, -1, 0, 3);
    pillexplodes2(hero.x, hero.y, +1, 0, 3);
    pillexplodes2(hero.x, hero.y, 0, -1, 3);
    pillexplodes2(hero.x, hero.y, 0, +1, 3);
    havepill = 0;
}
void pillexplodes2(int x, int y, int sumx, int sumy, int amount){
    if(amount == 0) return;
    int newx = x + sumx;
    int newy = y + sumy;
    
    if(!isvalid(&m, newx, newy)) return;
    if(iswall(&m, newx, newy)) return;
    m.matrix[newx][newy] = empty;
    pillexplodes2(newx, newy, sumx, sumy, amount - 1);
}
    
int main(){
    readmap(&m);
    findmap(&m, &hero, HERO);    
    
    do {
        printf("Tem pilula? %s\n", (havepill ? "YES" : "NO"));
        printmap(&m);
        char command;
        scanf(" %c", &command);
        move(command);
        if(command == BOMB) pillexplodes1();
        ghost();
    }while(!finished());
    
    clearmap(&m);
}