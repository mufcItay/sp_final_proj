#include "GameBoardView.h"
#include <stdlib.h>
#include "SimpleButton.h"
#include "CommonGUIUtil.h"
#include "Window.h"
#include "MainWindow.h"
#include "CommonStructures.h"
#include "Commands.h"
#include "FileSystemUtil.h"


void fillSoldierButtonsMatrix(Window* holdingWindow, Window*** soldierButtonsMatrix, SDL_Renderer* renderer, char** initialBoard) {
	for (int i = 0; i < BOARD_WINDOW_ROWS_AMOUNT; ++i) {
		for (int j = 0; j < BOARD_WINDOW_COLUMNS_AMOUNT; ++j) {
			soldierButtonsMatrix[i][j] = (Window*) createSoldierButton(holdingWindow,
					renderer, i, j, initialBoard[i][j]);
			if (soldierButtonsMatrix[i][j] == NULL) {
				for (int i = 0; i < BOARD_WINDOW_ROWS_AMOUNT; ++i) {
					for (int j = 0; j < BOARD_WINDOW_COLUMNS_AMOUNT; ++j) {
						destroyWindow(soldierButtonsMatrix[i][j]); //NULL SAFE
					}
				}
				free(soldierButtonsMatrix);
				return;
			}
			initWindow(soldierButtonsMatrix[i][j]);
		}
	}
}

Window*** createBoardSoldierButtons(Window* holdingWindow, SDL_Renderer* renderer)
{
	if (renderer == NULL || holdingWindow == NULL) {
		return NULL ;
	}
	GameBoardData* data = (GameBoardData*) (holdingWindow->data);

	char** initialBoard = data->gameState->board;
	// init memory
	Window*** soldierButtonsMatrix = calloc(BOARD_WINDOW_ROWS_AMOUNT,sizeof(Window*));
	if (soldierButtonsMatrix == NULL ) {
		return NULL;
	}
	for(int i=0; i<BOARD_WINDOW_ROWS_AMOUNT; ++i)
	{
		soldierButtonsMatrix[i] = calloc(BOARD_WINDOW_COLUMNS_AMOUNT,sizeof(Window*));
		if (soldierButtonsMatrix[i] == NULL ) {
			return NULL;
		}
	}

	fillSoldierButtonsMatrix(holdingWindow, soldierButtonsMatrix, renderer, initialBoard);

	return soldierButtonsMatrix;
}

Window** createBoardMenuButtons(Window* holdingWindow, SDL_Renderer* renderer){
	Window** menuButtons = calloc(BOARD_WINDOW_BUTTONS_AMOUNT,sizeof(Window*));
	if (menuButtons == NULL ) {
		return NULL;
	}
	SDL_Rect restartR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING, .y = BOARD_WINDOW_BUTTON_SPACING, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	SDL_Rect saveR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING , .y = 2*BOARD_WINDOW_BUTTON_SPACING+ BOARD_WINDOW_BUTTON_HEIGHT, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	SDL_Rect loadR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING , .y = 3*BOARD_WINDOW_BUTTON_SPACING+ 2*BOARD_WINDOW_BUTTON_HEIGHT, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	SDL_Rect undoR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING , .y = 4*BOARD_WINDOW_BUTTON_SPACING+ 3*BOARD_WINDOW_BUTTON_HEIGHT, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	SDL_Rect mainmenuR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING , .y = 5*BOARD_WINDOW_BUTTON_SPACING+ 4*BOARD_WINDOW_BUTTON_HEIGHT, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	SDL_Rect exitR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING , .y = 6*BOARD_WINDOW_BUTTON_SPACING+ 5*BOARD_WINDOW_BUTTON_HEIGHT, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	menuButtons[BOARD_WINDOW_RESTART_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &restartR,BOARD_WINDOW_RESTART_BUTTON_PIC_PATH ,restartButtonHandler);
	menuButtons[BOARD_WINDOW_LOAD_GAME_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &loadR, BOARD_WINDOW_LOAD_GAME_BUTTON_PIC_PATH, loadGameBoardButtonHandler);
	menuButtons[BOARD_WINDOW_SAVE_GAME_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &saveR, BOARD_WINDOW_SAVE_GAME_BUTTON_PIC_PATH,saveButtonHandler);
	menuButtons[BOARD_WINDOW_UNDO_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &undoR, BOARD_WINDOW_UNDO_BUTTON_PIC_PATH,undoButtonHandler);
	menuButtons[BOARD_WINDOW_MAIN_MENU_GAME_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &mainmenuR, BOARD_WINDOW_MAIN_MENU_GAME_BUTTON_PIC_PATH, mainMenuButtonHandler);
	menuButtons[BOARD_WINDOW_EXIT_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &exitR, BOARD_WINDOW_EXIT_BUTTON_PIC_PATH,exitBoardButtonHandler);

	setEnabledSimpleButton(menuButtons[BOARD_WINDOW_UNDO_BUTTON_INDEX], SDL_FALSE);

	if (menuButtons[BOARD_WINDOW_RESTART_BUTTON_INDEX] == NULL || menuButtons[BOARD_WINDOW_LOAD_GAME_BUTTON_INDEX] == NULL || menuButtons[BOARD_WINDOW_SAVE_GAME_BUTTON_INDEX] == NULL ||
			menuButtons[BOARD_WINDOW_UNDO_BUTTON_INDEX] == NULL || menuButtons[BOARD_WINDOW_MAIN_MENU_GAME_BUTTON_INDEX] == NULL || menuButtons[BOARD_WINDOW_EXIT_BUTTON_INDEX] == NULL) {
		destroyWindow(menuButtons[BOARD_WINDOW_RESTART_BUTTON_INDEX]); //NULL SAFE
		destroyWindow(menuButtons[BOARD_WINDOW_LOAD_GAME_BUTTON_INDEX]); //NULL SAFE
		destroyWindow(menuButtons[BOARD_WINDOW_SAVE_GAME_BUTTON_INDEX]); //NULL SAFE
		destroyWindow(menuButtons[BOARD_WINDOW_UNDO_BUTTON_INDEX]); //NULL SAFE
		destroyWindow(menuButtons[BOARD_WINDOW_MAIN_MENU_GAME_BUTTON_INDEX]); //NULL SAFE
		destroyWindow(menuButtons[BOARD_WINDOW_EXIT_BUTTON_INDEX]); //NULL SAFE
		free(menuButtons);
		return NULL ;
	}

	return menuButtons;
}

Window* createBoardWindow(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState) {
	Window* res = malloc(sizeof(Window));
	GameBoardData* data = malloc(sizeof(GameBoardData));
	res->data = (void*) data;
	data->gameState = gameState;
	data->gameSettings = gameSettings;
	MainWindow* main = (MainWindow*)holdingWindow->data;
	SDL_Rect boardR = { .x = 0, .y = 0, .h = BOARD_WINDOW_HEIGHT, .w = BOARD_WINDOW_WIDTH};
	res->location = &boardR;
	SDL_Renderer* renderer = main->windowRenderer;
	Window*** widgets = createBoardSoldierButtons(res, renderer);
	Window** menuButtons = createBoardMenuButtons(res, renderer);
	if (res == NULL || data == NULL || holdingWindow == NULL || renderer == NULL
			|| widgets == NULL || menuButtons == NULL) {
		free(res);
		free(data);
		free(widgets);
		free(menuButtons);
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer); //NULL safe
		destroyWindow(holdingWindow); //NULL safe
		return NULL ;
	}
	data->soldierButtons = widgets;
	data->windowRenderer = renderer;
	data->soldierButtons = widgets;
	data->menuButtons = menuButtons;
	data->selectedSoldier = NULL;
	res->destroyWindow = destroyGameBoardWindow;
	res->drawWindow = drawGameBoardWindow;
	res->handleEventWindow = handleEventGameBoardWindow;
	res->isClosed = SDL_FALSE;
	res->holdingWindow = holdingWindow;
	res->setInnerWidgetsReDraw = setGameBoardInnerReDraw;
	return res;

}
void destroyGameBoardWindow(Window* src) {
	if (src == NULL ) {
		return;
	}
	GameBoardData* data = (GameBoardData*) src->data;
	for (int i = 0; i< BOARD_WINDOW_ROWS_AMOUNT; ++i) {
			for (int j= 0; j< BOARD_WINDOW_COLUMNS_AMOUNT; ++j) {
				destroyWindow(data->soldierButtons[i][j]); //NULL SAFE
			}
	}
	for (int i = 0; i < BOARD_WINDOW_BUTTONS_AMOUNT; ++i) {
		destroyWindow(data->menuButtons[i]);
	}
	// free menu buttons
	//free(src->location);
	free(data->soldierButtons);
	free(data->menuButtons);
	SDL_DestroyRenderer(data->windowRenderer);
	free(data);
	free(src);
}

void drawGameBoardWindow(Window* src) {
	if (src == NULL ) {
		return;
	}
	GameBoardData* data = (GameBoardData*) src->data;
	//Draw window
	if(src->reDrawNeeded)
	{
		SDL_SetRenderDrawColor(data->windowRenderer, BOARD_WINDOW_BGCOLOR_RED, BOARD_WINDOW_BGCOLOR_GREEN, BOARD_WINDOW_BGCOLOR_BLUE, BOARD_WINDOW_BGCOLOR_ALPHA);
		SDL_RenderClear(data->windowRenderer);
	}
	for (int i = 0; i< BOARD_WINDOW_ROWS_AMOUNT; ++i) {
		for (int j= 0; j< BOARD_WINDOW_COLUMNS_AMOUNT; ++j) {
			src->reDrawNeeded |= data->soldierButtons[i][j]->reDrawNeeded;
			(data->soldierButtons[i][j])->drawWindow(data->soldierButtons[i][j]);
		}
	}
	for (int i = 0; i < BOARD_WINDOW_BUTTONS_AMOUNT; ++i) {
		src->reDrawNeeded |= data->menuButtons[i]->reDrawNeeded;
		data->menuButtons[i]->drawWindow(data->menuButtons[i]);
	}
	if(src->reDrawNeeded){
		SDL_RenderPresent(data->windowRenderer);
	}
	src->reDrawNeeded = SDL_FALSE;
}

Command* handleEventGameBoardWindow(Window* src, SDL_Event* event){
	if(src == NULL || event==NULL){
		return NULL;
	}
	Command* cmd;
	GameBoardData* data = (GameBoardData*)src->data;
	for (int i = 0; i < BOARD_WINDOW_BUTTONS_AMOUNT; ++i) {
		if(isEventWindowRelated(data->menuButtons[i], event) == SDL_TRUE){
			cmd = data->menuButtons[i]->handleEventWindow(data->menuButtons[i],event);
			if (cmd->data != NOP_COMMAND_DATA) {
				return cmd;
			}
		}
	}

	for (int i = 0; i< BOARD_WINDOW_ROWS_AMOUNT; ++i) {
		for (int j= 0; j< BOARD_WINDOW_COLUMNS_AMOUNT; ++j) {
			if(isEventWindowRelated(data->soldierButtons[i][j], event) == SDL_TRUE){
				cmd = data->soldierButtons[i][j]->handleEventWindow(data->soldierButtons[i][j],event);
				if (cmd->data != NOP_COMMAND_DATA) {
					return cmd;
				}
			}
		}
	}

	cmd = createNOPCommand();
	return cmd;
}

Command* saveButtonHandler(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
			return NULL;
	}
	Command* cmd = createNOPCommand();

	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		cmd = createSaveCommand(SAVED_GAMES_DIRECTORY_PATH);
	}
	return cmd;
}
Command* restartButtonHandler(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	Command* cmd = createNOPCommand();

	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		cmd = createResetCommand();
	}

	return cmd;
}
Command* undoButtonHandler(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	Command* cmd = createNOPCommand();

	SimpleButton* data = (SimpleButton*) src->data;
	if(data->isEnabled == SDL_FALSE)
	{
		return cmd;
	}
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		cmd = createUndoCommand();
	}

	return cmd;
}

Command* exitBoardButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	Command* cmd = createNOPCommand();
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		src->holdingWindow->isClosed = SDL_TRUE;
		cmd = createQuitCommand();
	}
	return cmd;
}

Command* mainMenuButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	Command* cmd = createNOPCommand();
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow, MAIN_VIEW);
	}
	return cmd;
}

Command* loadGameBoardButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	Command* cmd = createNOPCommand();

	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow, LOAD_GAME_VIEW);
	}
	return cmd;
}

void setGameBoardInnerReDraw(Window* src, SDL_bool reDraw){
	if (src == NULL ) {
		return;
	}
	GameBoardData* data = (GameBoardData*) src->data;
	src->reDrawNeeded = reDraw;
	for (int i = 0; i< BOARD_WINDOW_ROWS_AMOUNT; ++i) {
		for (int j= 0; j< BOARD_WINDOW_COLUMNS_AMOUNT; ++j) {
			(data->soldierButtons[i][j])->reDrawNeeded = reDraw;
		}
	}
	for (int i = 0; i < BOARD_WINDOW_BUTTONS_AMOUNT; ++i) {
		data->menuButtons[i]->reDrawNeeded = reDraw;
	}
}

Command* moveSelectedSoldierTo(GameBoardData* gameBoard, Window* toSoldier) {
	if(gameBoard->selectedSoldier == NULL){
		return NULL;
	}
	Command* cmd;
	SoldierButton* soldierToMove = (SoldierButton*)(gameBoard->selectedSoldier->data);
	SoldierButton* destinationSoldier= (SoldierButton*)(toSoldier->data);

	if(soldierToMove == NULL || destinationSoldier == NULL) {
		return NULL;
	}
//		if(invalid move) continue
//		else - removes selection (gameBoard->selectedSoldier = NULL) and re draw
//	return CreateNOPCommand();
	// set new position
	updateSoldierData(toSoldier,soldierToMove->soldierType);
	// set old position
	updateSoldierData(gameBoard->selectedSoldier,SOLDIER_TYPE_EMPTY);

	gameBoard->selectedSoldier->reDrawNeeded = SDL_TRUE;
	toSoldier->reDrawNeeded = SDL_TRUE;

	//if(check or check mate, react GUI'li)

	SDL_Point origin = {.x = soldierToMove->rowIndex, .y = soldierToMove->columnIndex};
	SDL_Point destination = {.x = destinationSoldier->rowIndex, .y = destinationSoldier->columnIndex};
	cmd = createMoveCommand(origin,destination);
	return cmd;
}
