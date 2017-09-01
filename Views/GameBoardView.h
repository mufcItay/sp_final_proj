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
void FillSoldierButtonsMatrix(Window* holdingWindow, Window*** soldierButtonsMatrix, SDL_Renderer* renderer, char** initialBoard);
Window** createBoardMenuButtons(Window* holdingWindow, SDL_Renderer* renderer);
Command* RestartButtonHandler(Window* src, SDL_Event* event);
Command* SaveButtonHandler(Window* src, SDL_Event* event);
Command* UndoButtonHandler(Window* src, SDL_Event* event);
Command* ExitBoardButtonHandler(Window* src, SDL_Event* event);
Command* MainMenuButtonHandler(Window* src, SDL_Event* event);
Command* LoadGameBoardButtonHandler(Window* src, SDL_Event* event);
void setGameBoardInnerReDraw(Window* src, SDL_bool reDraw);
Command* MoveSelectedSoldierTo(GameBoardData* gameBoard, Window* toSoldier);
#endif
