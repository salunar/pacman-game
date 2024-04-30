#ifndef _MAP_H_
#define _MAP_H_
#define HERO '@'
#define GHOST 'A'
#define empty '.'
#define vertical_wall '|'
#define horizontal_wall '-'
#define PILL 'o'

struct map {
    char** matrix;
    int lines;
    int columns;
};
typedef struct map MAP;

struct position {
    int x;
    int y;
};
typedef struct position POSITION;

void clearmap(MAP* m);
void readmap(MAP* m);
void allocatemap(MAP* m);
int findmap(MAP* m, POSITION* p, char c);
int isvalid(MAP* m, int x, int y);
int isempty(MAP* m, int x, int y);
void walkmap(MAP* m, int xorigin, int yorigin, int xdestiny, int ydestiny);
void copymap(MAP* destiny, MAP* origin);
int iswall(MAP* m, int x, int y);
int ischaracter(MAP* m, char character, int x, int y);
int canwalk(MAP* m, char character, int x, int y);
#endif