#ifndef WINDOW_H_
#define WINDOW_H_
#include "SDL2\SDL.h"
#include "SDL2\SDL_video.h"
#include "Commands.h"

typedef struct window_t Window;
struct window_t {
	void* data;
	SDL_Rect* location;
	SDL_bool isClosed;
	SDL_bool reDrawNeeded;
	Window* holdingWindow;
	void (*initWindow)(Window* );
	void (*drawWindow)(Window* );
	Command* (*handleEventWindow)(Window* , SDL_Event* );
	void (*destroyWindow)(Window* );
	void (*setInnerWidgetsReDraw)(Window* , SDL_bool);
};

/*
 * The function frees all resources held by the window
 */
void destroyWindow(Window* src);


/*
 * The function initialized window's members
 */
void initWindow(Window* src);


/*
 * The function decides if an event relates to the window
 */
SDL_bool isEventWindowRelated(Window* src, SDL_Event* event);

#endif
