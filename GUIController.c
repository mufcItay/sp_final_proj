#include <stdlib.h>
#include <stdio.h>
#include "SDL2\SDL.h"
#include "SDL2\SDL_video.h"
#include "GUIController.h"
#include "Window.h"
#include "MainWindow.h"
#include "CommonStructures.h"

void setGUIController(UIController* controller) {
	controller->init = GUIInit;
	controller->draw= GUIDraw;
	controller->handleInput = GUIHandleInput;
	controller->destroyController = GUIDestroyController;
}

void* GUIInit(GameSettings* gameSettings ,GameState* gameState) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return CONTROLLER_ERROR;
	}

	if(gameSettings == NULL || gameState == NULL) {
		return CONTROLLER_ERROR;
	}

	// create main window of the GUI
	Window* window = (Window*) createMainWindow(gameSettings ,gameState);
	initWindow(window);
	if (window == NULL ) {
		SDL_Quit();
		return CONTROLLER_ERROR;
	}

	return window;
}

int GUIHandleInput(void* src, GameSettings* settings, GameState* state){
	Window* window = (Window*) src;
	SDL_Event event;
	// wait for a user event
	SDL_WaitEvent(&event);
	// if we need to close gui..
	if((event.type == SDL_WINDOWEVENT) && (event.window.event == SDL_WINDOWEVENT_CLOSE)){
		return CONTROLLER_END;
	}
	// handle the event by calling it's unique handler
	Command* cmd = window->handleEventWindow(window,&event);
	cmd->handleCommand(cmd, settings,state);
	// check if re draw needed. if so then draw
	if(window->isClosed == SDL_TRUE)
	{
		return CONTROLLER_END;
	}

	destroyCommand(cmd);

	return OK;
}

void GUIDraw(void* src){
	Window* window = (Window*) src;
	// always draw the main window
	window->drawWindow(window);
}

void GUIDestroyController(void* src) {
	Window* window = (Window*) src;
	destroyWindow(window);
	SDL_Quit();
}
