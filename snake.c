#include "snake.h"

Snake createSnake(const int x, const int y, const int length, const int size){
	int i = 0;
	Snake s = {x, y, size};
	s.tail = malloc(1000*sizeof(Tail));
	for(; i < length; i++){
		newTail(&s);
	}
	return s;
}

void destroySnake(Snake s){
	free(s.tail);
}

void newTail(Snake *s){
	int x = (s->length == 0) ? s->x : s->tail[s->length-1].x;
	int y = (s->length == 0) ? s->y : s->tail[s->length-1].y;
	Tail t = {x, y};
	s->tail[s->length++] = t;
}

void updateSnake(Snake *s){
	int i = s->length-1;
	for(; i > 0; i--){
		s->tail[i].x = s->tail[i-1].x;
		s->tail[i].y = s->tail[i-1].y;
	}
	switch(s->dir){
		case 0:
			s->tail[0].x++;
			break;
		case 1:
			s->tail[0].y--;
			break;
		case 2:
			s->tail[0].x--;
			break;
		case 3:
			s->tail[0].y++;
			break;
	}
}

void drawSnake(Window *w, const Snake s){
	int i = 0;
	for(; i < s.length; i++)
		drawRect(w, s.tail[i].x*s.size, s.tail[i].y*s.size, s.size, s.size);
}
