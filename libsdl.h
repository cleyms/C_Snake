#ifndef LIBSDL
#define LIBSDL

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

typedef struct Window{
	SDL_Surface *screen;
	Uint32 color;
	int width;
	int height;
} Window;

void startSDL();
void endSDL(Window*);
Window* createWindow(int, int, char*);
void setColor(Window*, int, int, int);
void waitclose(Window*);
void drawRect(Window*, int, int, int, int);

#endif //LIBSDL