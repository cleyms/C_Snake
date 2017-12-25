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

typedef struct RGB{
	int red;
	int green;
	int blue;
} RGB;

void startSDL();

void endSDL(Window*);

Window* createWindow(int, int, char*);

RGB hexToRGB(const int hex);

void setColor(Window*, const int);

void drawRect(Window*, int, int, int, int);

#endif //LIBSDL