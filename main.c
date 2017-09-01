#include <stdlib.h>
#include <stdio.h>
#include "SDL2\SDL.h"
#include "SDL2\SDL_video.h"
#include "UIController.h"
#include "GUIController.h"
#include "MainWindow.h"
#include "Window.h"

int main(int argc, char* argv[]) {
	UIController controller;
	GameSettings* gameSettings = CreateGameSettings();
	if (gameSettings == NULL) {
		return 1;
	}
	GameState* gameState = CreateGameState();
	if (gameState == NULL) {
		return 1;
	}

	SetGUIController(&controller);
	void* ui = controller.Init(gameSettings, gameState);
	while (1) {
		int ret = controller.HandleInput(ui);
		if (ret == ERROR || ret == CONTROLLER_END) {
			break;
		}
		controller.Draw(ui);
	}
	controller.DestroyController(ui);
	DestroyGameSettings(gameSettings);
	DestroyGameState(gameState);
	return 0;
}
