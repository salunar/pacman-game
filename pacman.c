#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacman.h"
#include "map.h"

MAP m;
POSITION hero;

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
        if(isvalid(&m, options[position1][0], options[position1][1]) && 
        isempty(&m, options[position1][0], options[position1][1])){
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
    return 0;
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
    if(!isvalid(&m, nextx, nexty))
        return;
    
    if(!isempty(&m, nextx, nexty))
        return;
    
    walkmap(&m, hero.x, hero.y, nextx, nexty);
    
    hero.x = nextx;
    hero.y = nexty;

}
int main(){
    readmap(&m);
    findmap(&m, &hero, HERO);    
    
    do {
        printmap(&m);
        char command;
        scanf(" %c", &command);
        move(command);
        ghost();
    }while(!finished());
    
    clearmap(&m);
}