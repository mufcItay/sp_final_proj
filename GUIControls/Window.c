#include "Window.h"

#include <stdlib.h>

void destroyWindow(Window* src){
	if(src == NULL){
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return;
	}
	src->destroyWindow(src);
}


void initWindow(Window* src){
	if(src == NULL){
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
	// if the event happened inside the rectangle of the window, then it is window related
	return SDL_PointInRect(&point, src->location);
}
