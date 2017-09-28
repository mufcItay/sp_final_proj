#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_video.h"
#include "UIController.h"
#include "GUIController.h"
#include "CMDController.h"
#include "Window.h"

/*
 * the function sets the relevant controller according to command line arguments
 */
void setController(int argc, char* argv[], UIController* controller) {
	if(argc == EMPTY_ARGS_AMOUNT) {
		setCMDController(controller);
	}
	else if(argv[UITYPE_INDEX][UI_PREFIX_INDEX] == UI_PREFIX) {
		if(argv[UITYPE_INDEX][UI_CHAR_INDEX] == GUI_CONST) {
			setGUIController(controller);
		}
		else if(argv[UITYPE_INDEX][UI_CHAR_INDEX] == CONSOLE_CONST) {
			setCMDController(controller);
		}
	}
}

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

	// set relevant controller according to command line args
	setController(argc, argv, &controller);
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

