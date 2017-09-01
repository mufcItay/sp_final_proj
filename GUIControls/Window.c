#include "Window.h"

#include <stdlib.h>

void destroyWindow(Window* src){
	if(!src){
		return;
	}
	src->destroyWindow(src);
}

void initWindow(Window* src){
	if(!src){
		return;
	}
	src->reDrawNeeded = SDL_TRUE;
	src->isClosed = SDL_FALSE;
}


SDL_bool isEventWindowRelated(Window* src, SDL_Event* event)
{
	SDL_Point point;
	point.x = event->button.x;
	point.y = event->button.y;

	return SDL_PointInRect(&point, src->location);
}
