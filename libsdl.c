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
	Window *w = malloc(sizeof(*w));
	w->width = width;
	w->height = height;
	w->screen = malloc(sizeof(SDL_Surface));
	w->screen = SDL_SetVideoMode(w->width, w->height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(w->screen == NULL){
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	setColor(w, 255, 255, 255);
	SDL_WM_SetCaption(title, NULL);
	SDL_FillRect(w->screen, NULL, w->color);
	SDL_Flip(w->screen);
	setColor(w, 0, 0, 0);
	return w;
}

void setColor(Window *w, int r, int g, int b){
	w->color = SDL_MapRGB(w->screen->format, r, g, b);
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

void waitclose(Window *w){
	int close = 0;
	SDL_Event event;
	while(!close){
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT){
			close = 1;
		}
		//loop();
		SDL_Flip(w->screen);
	}
}