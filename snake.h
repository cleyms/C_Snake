#ifndef SNAKE
#define SNAKE

#include "libsdl.h"

typedef struct Tail{
	int x;
	int y;
} Tail;

typedef struct Snake{
	int x;
	int y;
	int size;
	int dir;
	int length;
	Tail *tail;
} Snake;

Snake createSnake(const int, const int, const int, const int);

void destroySnake(Snake);

void newTail(Snake*);

void updateSnake(Snake*);

void drawSnake(Window*, const Snake);

#endif //SNAKE