#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "ui.h"

char desingwall[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desingghost[4][7] = {
    {" .-.  " },
    {"| 00| " },
    {"|   | " },
    {"'^^^' " }
};

char desinghero[4][7] = {
    {" .--. "},
    {"/ _.-'"},
    {"\\ '-. "},
    {" '--' "}
};

char desingpill[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desingempty[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "},
};

void printpart(char desing[4][7], int part){
    printf("%s", desing[part]);
}
void printmap(MAP* m){
    for (int i = 0; i < m->lines; i++){
        for (int part = 0; part < 4; part++){
            for(int j = 0; j < m->columns; j++){
                switch (m->matrix[i][j]){
                    case GHOST:
                        printpart(desingghost, part);
                        break;
                    case HERO:
                        printpart(desinghero, part);
                        break;
                    case PILL:
                        printpart(desingpill, part);
                        break;
                    case HORIZONTAL_WALL:
                    case VERTICAL_WALL:
                        printpart(desingwall, part);
                        break;
                    case EMPTY:
                        printpart(desingempty, part);
                        break;
                }       
            }
            printf("\n");
        }
    }
}