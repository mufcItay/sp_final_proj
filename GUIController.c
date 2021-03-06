#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_video.h"
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
		printErrorMessage(SDL_ERROR_MESSAGE);
		return NULL;
	}

	if(gameSettings == NULL || gameState == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}

	// create main window of the GUI
	Window* window = (Window*) createMainWindow(gameSettings ,gameState);
	initWindow(window);
	if (window == NULL ) {
		SDL_Quit();
		return NULL;
	}

	return window;
}

ErrorCode GUIHandleInput(void* src, GameSettings* settings, GameState* state){
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
	if(cmd == NULL){
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}
	ErrorCode ret = cmd->handleCommand(cmd, settings,state);
	if(ret != OK) {
		ErrorCode handledError = window->handleError(window, ret);
		return handledError;
	}
	// check if re draw needed. if so then draw
	if(window->isClosed == SDL_TRUE)
	{
		return CONTROLLER_END;
	}

	destroyCommand(cmd);

	return OK;
}

ErrorCode GUIDraw(void* src){
	Window* window = (Window*) src;
	// always draw the main window
	ErrorCode ret = window->drawWindow(window);
	if(ret != OK) {
		printErrorMessage(GUI_ERROR_MESSAGE);
	}
	return ret;
}

void GUIDestroyController(void* src) {
	Window* window = (Window*) src;
	destroyWindow(window);
	SDL_Quit();
}
