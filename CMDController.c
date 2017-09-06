#include <stdlib.h>
#include <stdio.h>
#include "CMDController.h"

void setCMDController(UIController* controller) {
	controller->init = CMDInit;
	controller->draw= CMDDraw;
	controller->handleInput = CMDHandleInput;
	controller->destroyController = CMDDestroyController;
}

void* CMDInit(GameSettings* gameSettings ,GameState* gameState) {
	// init
	return NULL;
}

int CMDHandleInput(void* src, GameSettings* settings, GameState* state){
	//
	return OK;
}

void CMDDraw(void* src){
	//
}

void CMDDestroyController(void* src) {
	// destroy all
}
