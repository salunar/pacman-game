#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'

void move (char direction);
int finished();
int isdirection(char direction);
void ghost();
int findway(int xactual, int yactual, int* xdestiny, int* ydestiny);
