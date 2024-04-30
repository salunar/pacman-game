#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "ui.h"

void copymap(MAP* destiny, MAP* origin) {
    destiny->lines = origin->lines;
    destiny->columns = origin->columns;

    allocatemap(destiny);
    for(int i = 0; i < origin->lines; i++) {
        strcpy(destiny->matrix[i], origin->matrix[i]);
    }
    
}

int isvalid(MAP* m, int x, int y) {
    if(x >= m->lines)
        return 0;
    if(y >= m->columns)
        return 0;
    return 1;
}

int isempty(MAP* m, int x, int y){
    return m->matrix[x][y] == empty;
}

int iswall(MAP* m, int x, int y){
    return
        m->matrix[x][y] == vertical_wall ||
        m->matrix[x][y] == horizontal_wall;
}

int ischaracter(MAP* m, char character, int x, int y){
    return
        m->matrix[x][y] == character;
}

int canwalk(MAP* m, char character, int x, int y){
    return 
        isvalid(m, x, y) &&
        !iswall(m, x, y) &&
        !ischaracter(m, character, x, y);
}

void walkmap(MAP* m, int xorigin, int yorigin, int xdestiny, int ydestiny) {
    char caracter = m->matrix[xorigin][yorigin];
    m->matrix[xdestiny][ydestiny] = caracter;
    m->matrix[xorigin][yorigin] = empty;
}

int findmap(MAP* m, POSITION* p, char c) {
     //Find the position of pacman
    for(int i = 0; i < m->lines; i++){
        for(int j = 0; j < m->columns; j++){
            if(m->matrix[i][j] == c){
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    printmap(m);
    return 0;
}

void clearmap(MAP* m){
    for (int i = 0; i < m->lines; i++){
        free(m->matrix[i]);
    }
    free(m->matrix);
}

void allocatemap(MAP* m){
     m->matrix = malloc(sizeof(char*) * m->lines);
    for (int i = 0; i < m->lines; i++){
        m->matrix[i] = malloc(sizeof(char) * (m->columns + 1));
    }
}

void readmap(MAP* m){
     FILE* f;
    f = fopen("map2.txt", "r");
    if(f == 0){
        printf("Error reading the map!\n");
        exit(1);
    }
    
    fscanf(f, " %d %d", &m->lines, &m->columns);
    printf("Lines %d e Columns %d\n", m->lines, m->columns);

   allocatemap(m);

    for (int i = 0; i < 24; i++){
        fscanf(f, "%s", m->matrix[i]);
    }
    fclose(f);
}


