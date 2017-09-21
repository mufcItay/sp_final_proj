#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_video.h"
#include "UIController.h"
#include "GUIController.h"
#include "CMDController.h"
#include "Window.h"

int main(int argc, char* argv[]) {
	UIController controller;
	GameSettings* gameSettings = createGameSettings();
	if (gameSettings == NULL) {
		return MEMORY_ERROR;
	}
	GameState* gameState = createGameState();
	if (gameState == NULL) {
		return MEMORY_ERROR;
	}
	// set GUI or CMD controller according to command line args
	setGUIController(&controller);
	void* ui = controller.init(gameSettings, gameState);
	while (ui != NULL) {
		// handle user input
		int ret = controller.handleInput(ui,gameSettings, gameState);
		if (ret != OK) {
			break;
		}
		// draw UI
		ErrorCode err = controller.draw(ui);
		if(err != OK) {
			printErrorMessage("drawing GUI has encountered a problem");
			break;
		}
	}
	// free all resources
	controller.destroyController(ui);
	destroyGameSettings(gameSettings);
	destroyGameState(gameState);
	return OK;
}
