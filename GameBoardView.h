#ifndef GAMEBOARDVIEW_H_
#define GAMEBOARDVIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include "SoldierButton.h"
#include "Window.h"
#include "CommonStructures.h"
#include "CommonGUIUtil.h"
#include "Commands.h"


/*
 * enum to indicate at which drag and drop state the board is at
 */
enum boardstates_t {
	UNINITIALZIED,
	WAITING_FOR_SELECTION,
	PLAYER_SELECTED

};
typedef enum boardstates_t BoardStates;

/*
 * struct that contains the data of the view
 */
typedef struct gameBoard_t  GameBoardData;
struct gameBoard_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	Window*** soldierButtons;
	Window** menuButtons;
	Window* statusButton;
	Window* selectedSoldier;
	GameSettings* gameSettings;
	GameState* gameState;
	int dragDropIgnored;
};

/*
 * creator function of the view
 */
Window* createBoardWindow(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState);

/*
 * creator function of the soldier buttons on the board
 */
Window*** createBoardSoldierButtons(Window* holdingWindow, SDL_Renderer* renderer);

/*
 * destroyer function of the buttons of view
 */
void destroyGameBoardWindow(Window* src);

/*
 * draw function of the buttons of view
 */
ErrorCode drawGameBoardWindow(Window* src);

/*
 * handler for view GUI events
 */
Command* handleEventGameBoardWindow(Window* src, SDL_Event* event);

/*
 * creator function of the menu buttons of view
 */
Window** createBoardMenuButtons(Window* holdingWindow, SDL_Renderer* renderer);

/*
 * handler for restart button
 */
Command* restartButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for save button
 */
Command* saveButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for undo button
 */
Command* undoButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for exit button
 */
Command* exitBoardButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for main menu button
 */
Command* mainMenuButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for load button
 */
Command* loadGameBoardButtonHandler(Window* src, SDL_Event* event);

/*
 * the function sets re draw state of the view and each of it's inner components
 */
void setGameBoardInnerReDraw(Window* src, SDL_bool reDraw);

/*
 * the function sets a move in the board's GUI.
 * gameBoard - the data of the game board view
 * toSoldier - the soldier button that the user decided to move his soldier to
 */
Command* moveSelectedSoldierTo(GameBoardData* gameBoard, Window* toSoldier);

/*
 * the function sets boardToSet board to gameBoardWindow in GUI
 */
void setBoard(Window* gameBoardWindow, char** boardToSet);

/*
 * The function checked by showing a messagebox if save is wanted by user when the user switches from GameBoard view.
 */
SDL_bool checkIfSaveGameNeeded(GameBoardData* data);

/*
 * The function checked by showing a messagebox if save is wanted by user when the user switches from GameBoard view.
 */
ErrorCode setStatusImage(GameBoardData* data);

/*
 * The function frees memory resources of soldier buttons in the view
 */
void destroySoldierButtonMatrix(Window*** matrix);

/*
 * The function destroys the menu buttons
 */
void destroyMenuButtons(Window** menuButtons);

/*
 * draw selected soldier for live drag and drop.
 */
ErrorCode drawSelectedSoldier(Window* gameWindow,SDL_Event* event);

/*
 * the function updated enabled state of undo button.
 */
ErrorCode updateUndoState(Window* gameWindow, GameState* state);

/*
 * The function shows a message box to indicate to which soldier the computer promoted his pawn to
 */
ErrorCode showComputerPawnPromotion(GameBoardStatuses promotionStatus);

/*
 * the function updates the status image according to the game status
 */
ErrorCode updateGameStatusImage(GameBoardStatuses gameStatus, Window* statusBut);

/*
 * the function sets save button enabled state
 */
void setSaveEnabledState(Window* src, SDL_bool enabled);
#endif
