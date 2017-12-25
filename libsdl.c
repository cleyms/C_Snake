#include "libsdl.h"

void startSDL(){
	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void endSDL(Window *w){
	free(w);
	SDL_Quit();
}

Window* createWindow(int width, int height, char *title){
	startSDL();
	Window *w = malloc(sizeof(*w));
	w->width = width;
	w->height = height;
	w->screen = malloc(sizeof(SDL_Surface));
	w->screen = SDL_SetVideoMode(w->width, w->height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(w->screen == NULL){
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	setColor(w, 0xFFF);
	SDL_WM_SetCaption(title, NULL);
	SDL_FillRect(w->screen, NULL, w->color);
	SDL_Flip(w->screen);
	setColor(w, 0x000);
	return w;
}

RGB hexToRGB(const int hex){
	int m = (hex > 0xFFF) ? 0x1 : 0x11;
	RGB col = {
		(hex >> 0x8*(0x2-(m >> 0x4)) & 0xFF/m)*m,
		(hex >> 0x4*(0x2-(m >> 0x4)) & 0xFF/m)*m,
		(hex >> 0x0*(0x2-(m >> 0x4)) & 0xFF/m)*m
	};
	return col;
}

void setColor(Window *w, const int hex){
	RGB col = hexToRGB(hex);
	w->color = SDL_MapRGB(w->screen->format, col.red, col.green, col.blue);
}

void drawRect(Window *w, int x, int y, int width, int height){
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	SDL_Surface *rect = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(rect, NULL, w->color);
	SDL_BlitSurface(rect, NULL, w->screen, &pos);
	SDL_FreeSurface(rect);
}
