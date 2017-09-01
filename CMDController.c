#include <stdlib.h>
#include <stdio.h>
#include "CMDController.h"

void SetCMDController(UIController* controller) {
	controller->Init = CMDInit;
	controller->Draw= CMDDraw;
	controller->HandleInput = CMDHandleInput;
	controller->DestroyController = CMDDestroyController;
}

void* CMDInit(GameSettings* gameSettings ,GameState* gameState) {
	// init
	return NULL;
}

int CMDHandleInput(void* src){
	//
	return OK;
}

void CMDDraw(void* src){
	//
}

void CMDDestroyController(void* src) {
	// destroy all
}
