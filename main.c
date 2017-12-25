#include <math.h>
#include <time.h>
#include "libsdl.h"
#include "snake.h"

#define FRAME_SIZE 20

int main(int argc, char *argv[]){
	Window *win = createWindow(FRAME_SIZE*50, FRAME_SIZE*30, "Snake!");
	Snake player = createSnake(10, 7, 4, FRAME_SIZE);
	SDL_Event event;
	int close = 0, i;
	while(!close){
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT){
			close = 1;
		}else if(event.type == SDL_KEYDOWN){
			switch(event.key.keysym.sym){
				case SDLK_ESCAPE:
					close = 1;
					break;
				case SDLK_RIGHT:
					player.dir = 0;
					break;
				case SDLK_UP:
					player.dir = 1;
					break;
				case SDLK_LEFT:
					player.dir = 2;
					break;
				case SDLK_DOWN:
					player.dir = 3;
					break;
			}
		}
		updateSnake(&player);
		setColor(win, 0x969696);
		drawRect(win, 0, 0, win->width, win->height);
		setColor(win, 0x640000);
		drawSnake(win, player);
		SDL_Flip(win->screen);
		SDL_Delay(200);
	}
	destroySnake(player);
	endSDL(win);
	return EXIT_SUCCESS;
}
