#ifndef GAMEBOARDVIEW_H_
#define GAMEBOARDVIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include "SoldierButton.h"
#include "Window.h"
#include "CommonStructures.h"
#include "Commands.h"

enum boardstates_t {
	UNINITIALZIED,
	WAITING_FOR_SELECTION,
	PLAYER_SELECTED

};
typedef enum boardstates_t BoardStates;

typedef struct gameBoard_t  GameBoardData;
struct gameBoard_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	Window*** soldierButtons;
	Window** menuButtons;
	Window* selectedSoldier;
	GameSettings* gameSettings;
	GameState* gameState;
};

Window* createBoardWindow(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState);
Window*** createBoardSoldierButtons(Window* holdingWindow, SDL_Renderer* renderer);
void destroyGameBoardWindow(Window* src);
void drawGameBoardWindow(Window* src);
Command* handleEventGameBoardWindow(Window* src, SDL_Event* event);
void fillSoldierButtonsMatrix(Window* holdingWindow, Window*** soldierButtonsMatrix, SDL_Renderer* renderer, char** initialBoard);
Window** createBoardMenuButtons(Window* holdingWindow, SDL_Renderer* renderer);
Command* restartButtonHandler(Window* src, SDL_Event* event);
Command* saveButtonHandler(Window* src, SDL_Event* event);
Command* undoButtonHandler(Window* src, SDL_Event* event);
Command* exitBoardButtonHandler(Window* src, SDL_Event* event);
Command* mainMenuButtonHandler(Window* src, SDL_Event* event);
Command* loadGameBoardButtonHandler(Window* src, SDL_Event* event);
void setGameBoardInnerReDraw(Window* src, SDL_bool reDraw);
Command* moveSelectedSoldierTo(GameBoardData* gameBoard, Window* toSoldier);
#endif
