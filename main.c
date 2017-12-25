#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "libsdl.h"

#define FRAME_SIZE 20

int close = 0;
typedef struct entity{
		int queue[1000][2];
		int dir;
} entity;

void event_manager(entity*);
void draw_grid(Window*);
void draw_player(Window*, entity*);
void physic_player(entity*);

int main(int argc, char *argv[]){
	//Init SDL
	startSDL();
	Window *win = createWindow(FRAME_SIZE*50, FRAME_SIZE*30, "Snake!");
	//Init player
	entity player;
	player.queue[0][0] = 10;
	player.queue[0][1] = 10;
	player.queue[1][0] = -50;//Setting -50
	player.queue[1][1] = -50;//to set the end
	player.dir = 0;
	//Game Loop
	int index = 0;
	while(!close){
		//Calc
		event_manager(&player);
		physic_player(&player);
		//clear
		setColor(win, 150, 150, 150);
		drawRect(win, 0, 0, win->width, win->height);
		//Environment
		draw_grid(win);
		draw_player(win, &player);
		//SDL update
		SDL_Flip(win->screen);
		index += 1;
		SDL_Delay(200);
	}
	endSDL(win);

	return EXIT_SUCCESS;
}

void event_manager(entity *player){
	SDL_Event event;
	SDL_PollEvent(&event);
	if(event.type == SDL_QUIT){
		close = 1;
	}else if(event.type == SDL_KEYDOWN){
		//#### DIR #####//
		//		1		//
		//	2		0	//
		//		3		//
		//##############//
		fprintf(stderr, "%d", event.key.keysym.sym);
		if(event.key.keysym.sym == 119){//up
			player->dir = 1;
		}else if(event.key.keysym.sym == 115){//down
			player->dir = 3;
		}else if(event.key.keysym.sym == 97){//left
			player->dir = 2;
		}else if(event.key.keysym.sym == 100){//right
			player->dir = 0;
		}
	}
}

void draw_grid(Window *window){
	int x = 0, y = 0;
	setColor(window, 50, 50, 50);
	for(; x < window->width; x += FRAME_SIZE){
		drawRect(window, x, 0, 1, window->height);
	}
	for(; y < window->height; y += FRAME_SIZE){
		drawRect(window, 0, y, window->width, 1);
	}
}

void draw_player(Window *window, entity *player){
	int i = 0;
	setColor(window, 100, 0, 0);
	while(player->queue[i][0] != -50){
		drawRect(window, player->queue[i][0]*FRAME_SIZE, player->queue[i][1]*FRAME_SIZE, FRAME_SIZE, FRAME_SIZE);
		i++;
	}
}

void physic_player(entity *player){
	//Queue
	int i=0;
	while(player->queue[i][0] != -50){
		i++;
	}
	for(; i>1; i--){
		player->queue[i][0] = player->queue[i-1][0];
		player->queue[i][1] = player->queue[i-1][1];
	}
	//Head
	switch(player->dir){
		case 0:
			player->queue[0][0] += 1;
		case 1:
			player->queue[0][1] -= 1;
		case 2:
			player->queue[0][0] -= 1;
		case 3:
			player->queue[0][1] += 1;
 	}
}