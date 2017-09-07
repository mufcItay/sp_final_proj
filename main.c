#include <stdlib.h>
#include <stdio.h>
#include "SDL2\SDL.h"
#include "SDL2\SDL_video.h"
#include "UIController.h"
#include "GUIController.h"
#include "CMDController.h"
#include "Window.h"

int main(int argc, char* argv[]) {
	UIController controller;
	GameSettings* gameSettings = createGameSettings();
	if (gameSettings == NULL) {
		return 1;
	}
	GameState* gameState = createGameState();
	if (gameState == NULL) {
		return 1;
	}

	setGUIController(&controller);
	void* ui = controller.init(gameSettings, gameState);
	while (1) {
		int ret = controller.handleInput(ui,gameSettings, gameState);
		if (ret == ERROR || ret == CONTROLLER_END) {
			break;
		}
		controller.draw(ui);
	}
	controller.destroyController(ui);
	destroyGameSettings(gameSettings);
	destroyGameState(gameState);
	return 0;
}
