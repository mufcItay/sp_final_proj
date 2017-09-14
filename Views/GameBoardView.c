#include "GameBoardView.h"
#include <stdlib.h>
#include "SimpleButton.h"
#include "CommonGUIUtil.h"
#include "Window.h"
#include "MainWindow.h"
#include "CommonStructures.h"
#include "Commands.h"
#include "FileSystemUtil.h"
#include "SaveGameMessageBox.h"

Window*** createBoardSoldierButtons(Window* holdingWindow, SDL_Renderer* renderer)
{
	if (renderer == NULL || holdingWindow == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL ;
	}
	GameBoardData* data = (GameBoardData*) (holdingWindow->data);
	char** boardToSet = data->gameState->board;
	// init memory
	Window*** soldierButtonsMatrix = calloc(BOARD_WINDOW_ROWS_AMOUNT,sizeof(Window*));
	if (soldierButtonsMatrix == NULL ) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	for(int i=0; i<BOARD_WINDOW_ROWS_AMOUNT; ++i)
	{
		soldierButtonsMatrix[i] = calloc(BOARD_WINDOW_COLUMNS_AMOUNT,sizeof(Window*));
		if (soldierButtonsMatrix[i] == NULL ) {
			printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
			return NULL;
		}
	}

	// actually create the soldier buttons
	for (int i = 0; i < BOARD_WINDOW_ROWS_AMOUNT; ++i) {
		for (int j = 0; j < BOARD_WINDOW_COLUMNS_AMOUNT; ++j) {
			soldierButtonsMatrix[i][j] = (Window*) createSoldierButton(holdingWindow, renderer, i, j, boardToSet[i][j]);
			if (soldierButtonsMatrix[i][j] == NULL) {
				destroySoldierButtonMatrix(soldierButtonsMatrix);
				return NULL;
			}
			initWindow(soldierButtonsMatrix[i][j]);
		}
	}
	return soldierButtonsMatrix;
}

void destroySoldierButtonMatrix(Window*** matrix) {
	for (int i = 0; i < BOARD_WINDOW_ROWS_AMOUNT; ++i) {
		for (int j = 0; j < BOARD_WINDOW_COLUMNS_AMOUNT; ++j) {
			destroyWindow(matrix[i][j]);
		}
	}
	free(matrix);
}

void destroyMenuButtons(Window** menuButtons) {
	for (int i = 0; i < BOARD_WINDOW_BUTTONS_AMOUNT; ++i) {
		destroyWindow(menuButtons[i]);
	}
	free(menuButtons);
}

Window** createBoardMenuButtons(Window* holdingWindow, SDL_Renderer* renderer){
	Window** menuButtons = calloc(BOARD_WINDOW_BUTTONS_AMOUNT,sizeof(Window*));
	if (menuButtons == NULL ) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	// init rectangles for menu buttons
	SDL_Rect restartR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING, .y = BOARD_WINDOW_BUTTON_SPACING, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	SDL_Rect saveR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING , .y = 2*BOARD_WINDOW_BUTTON_SPACING+ BOARD_WINDOW_BUTTON_HEIGHT, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	SDL_Rect loadR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING , .y = 3*BOARD_WINDOW_BUTTON_SPACING+ 2*BOARD_WINDOW_BUTTON_HEIGHT, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	SDL_Rect undoR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING , .y = 4*BOARD_WINDOW_BUTTON_SPACING+ 3*BOARD_WINDOW_BUTTON_HEIGHT, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	SDL_Rect mainmenuR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING , .y = 5*BOARD_WINDOW_BUTTON_SPACING+ 4*BOARD_WINDOW_BUTTON_HEIGHT, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	SDL_Rect exitR = { .x = SOLDIER_BUTTON_IMAGE_WIDTH * BOARD_WINDOW_COLUMNS_AMOUNT + BOARD_WINDOW_BUTTON_SPACING , .y = 6*BOARD_WINDOW_BUTTON_SPACING+ 5*BOARD_WINDOW_BUTTON_HEIGHT, .h = BOARD_WINDOW_BUTTON_HEIGHT, .w = BOARD_WINDOW_BUTTON_WIDTH};
	// create menu buttons
	menuButtons[BOARD_WINDOW_RESTART_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &restartR,BOARD_WINDOW_RESTART_BUTTON_PIC_PATH ,restartButtonHandler);
	menuButtons[BOARD_WINDOW_LOAD_GAME_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &loadR, BOARD_WINDOW_LOAD_GAME_BUTTON_PIC_PATH, loadGameBoardButtonHandler);
	menuButtons[BOARD_WINDOW_SAVE_GAME_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &saveR, BOARD_WINDOW_SAVE_GAME_BUTTON_PIC_PATH,saveButtonHandler);
	menuButtons[BOARD_WINDOW_UNDO_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &undoR, BOARD_WINDOW_UNDO_BUTTON_PIC_PATH,undoButtonHandler);
	menuButtons[BOARD_WINDOW_MAIN_MENU_GAME_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &mainmenuR, BOARD_WINDOW_MAIN_MENU_GAME_BUTTON_PIC_PATH, mainMenuButtonHandler);
	menuButtons[BOARD_WINDOW_EXIT_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &exitR, BOARD_WINDOW_EXIT_BUTTON_PIC_PATH,exitBoardButtonHandler);
	//TODO:if undo history is empty !!
	setEnabledSimpleButton(menuButtons[BOARD_WINDOW_UNDO_BUTTON_INDEX], SDL_FALSE);
	// if an error occurred, free memory
	if (menuButtons[BOARD_WINDOW_RESTART_BUTTON_INDEX] == NULL || menuButtons[BOARD_WINDOW_LOAD_GAME_BUTTON_INDEX] == NULL || menuButtons[BOARD_WINDOW_SAVE_GAME_BUTTON_INDEX] == NULL ||
			menuButtons[BOARD_WINDOW_UNDO_BUTTON_INDEX] == NULL || menuButtons[BOARD_WINDOW_MAIN_MENU_GAME_BUTTON_INDEX] == NULL || menuButtons[BOARD_WINDOW_EXIT_BUTTON_INDEX] == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		destroyMenuButtons(menuButtons);
		return NULL ;
	}

	return menuButtons;
}

Window* createBoardWindow(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState) {
	// allocate memory
	Window* res = malloc(sizeof(Window));
	GameBoardData* data = malloc(sizeof(GameBoardData));
	res->data = (void*) data;
	data->gameState = gameState;
	data->gameSettings = gameSettings;
	MainWindow* main = (MainWindow*)holdingWindow->data;
	// rectangle for board
	SDL_Rect boardR = { .x = 0, .y = 0, .h = BOARD_WINDOW_HEIGHT, .w = BOARD_WINDOW_WIDTH};
	res->location = &boardR;
	SDL_Renderer* renderer = main->windowRenderer;
	// create Windows of the view
	Window*** widgets = createBoardSoldierButtons(res, renderer);
	Window** menuButtons = createBoardMenuButtons(res, renderer);
	SDL_Rect statusR = { .x = BOARD_STATUS_BUTTON_X_POS , .y = BOARD_STATUS_BUTTON_Y_POS, .h = BOARD_STATUS_BUTTON_HEIGHT, .w = BOARD_STATUS_BUTTON_WIDTH};
	Window* statusWindow = createSimpleButton(res,renderer,&statusR,BOARD_WINDOW_STATUS_NEUTRAL_BUTTON_PIC_PATH,NULL);
	// handle windows creation errors
	if (res == NULL || data == NULL || holdingWindow == NULL || renderer == NULL
			|| widgets == NULL || menuButtons == NULL|| statusWindow == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer);
		destroyWindow(statusWindow);
		destroyWindow(holdingWindow);
		destroySoldierButtonMatrix(widgets);
		destroyMenuButtons(menuButtons);
		free(res);
		free(data);
		return NULL ;
	}
	data->soldierButtons = widgets;
	data->windowRenderer = renderer;
	data->soldierButtons = widgets;
	data->menuButtons = menuButtons;
	data->isGameSaved = SDL_FALSE;
	data->selectedSoldier = NULL;
	data->statusButton = statusWindow;
	res->destroyWindow = destroyGameBoardWindow;
	res->drawWindow = drawGameBoardWindow;
	res->handleEventWindow = handleEventGameBoardWindow;
	res->isClosed = SDL_FALSE;
	res->holdingWindow = holdingWindow;
	res->setInnerWidgetsReDraw = setGameBoardInnerReDraw;
	return res;
}

void setBoard(Window* gameBoardWindow, char** boardToSet)
{
	gameBoardWindow->reDrawNeeded = SDL_TRUE;
	GameBoardData* gameBoard = (GameBoardData*) gameBoardWindow->data;
	gameBoard->isGameSaved = SDL_FALSE;
	Window*** soldierButtons = gameBoard->soldierButtons;
	for (int i = 0; i < BOARD_WINDOW_ROWS_AMOUNT; ++i) {
		for (int j = 0; j < BOARD_WINDOW_COLUMNS_AMOUNT; ++j) {
			Window* soldierWindow = (Window*) soldierButtons[i][j];
			SoldierButton* soldierData = (SoldierButton*) soldierWindow->data;
			// set soldier type and re draw state so it will be re drawn
			soldierData->soldierType = boardToSet[i][j];
			soldierWindow->setInnerWidgetsReDraw(soldierWindow,SDL_TRUE);
		}
	}
}

void destroyGameBoardWindow(Window* src) {
	if (src == NULL ) {
		return;
	}
	GameBoardData* data = (GameBoardData*) src->data;
	destroySoldierButtonMatrix(data->soldierButtons);
	destroyMenuButtons(data->menuButtons);
	destroyWindow(data->statusButton);
	SDL_DestroyRenderer(data->windowRenderer);
	free(data);
	free(src);
}

ErrorCode drawGameBoardWindow(Window* src) {
	if (src == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}
	ErrorCode err = OK;
	GameBoardData* data = (GameBoardData*) src->data;
	//Draw window
	if(src->reDrawNeeded)
	{
		setBoard(src, data->gameState->board);
		err |= SDL_SetRenderDrawColor(data->windowRenderer, BOARD_WINDOW_BGCOLOR_RED, BOARD_WINDOW_BGCOLOR_GREEN, BOARD_WINDOW_BGCOLOR_BLUE, BOARD_WINDOW_BGCOLOR_ALPHA);
		err |= SDL_RenderClear(data->windowRenderer);
		if(err != OK) {
			err = SDL_ERROR;
			return err;
		}
	}
	src->reDrawNeeded |= data->statusButton->reDrawNeeded;
	err |= data->statusButton->drawWindow(data->statusButton);
	for (int i = 0; i< BOARD_WINDOW_ROWS_AMOUNT; ++i) {
		for (int j= 0; j< BOARD_WINDOW_COLUMNS_AMOUNT; ++j) {
			// draw soldier buttons
			src->reDrawNeeded |= data->soldierButtons[i][j]->reDrawNeeded;
			err |= (data->soldierButtons[i][j])->drawWindow(data->soldierButtons[i][j]);
			if(err != OK) {
				err = SDL_ERROR;
				return err;
			}
		}
	}
	for (int i = 0; i < BOARD_WINDOW_BUTTONS_AMOUNT; ++i) {
		// draw menu buttons
		src->reDrawNeeded |= data->menuButtons[i]->reDrawNeeded;
		err |= data->menuButtons[i]->drawWindow(data->menuButtons[i]);
		if(err != OK) {
			err = SDL_ERROR;
			return err;
		}
	}

	if(src->reDrawNeeded){
		SDL_RenderPresent(data->windowRenderer);
	}
	src->reDrawNeeded = SDL_FALSE;
	return err;
}

Command* handleEventGameBoardWindow(Window* src, SDL_Event* event){
	if(src == NULL || event==NULL){
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd;
	GameBoardData* data = (GameBoardData*)src->data;
	for (int i = 0; i < BOARD_WINDOW_BUTTONS_AMOUNT; ++i) {
		if(isEventWindowRelated(data->menuButtons[i], event) == SDL_TRUE){
			// handle menu buttons
			cmd = data->menuButtons[i]->handleEventWindow(data->menuButtons[i],event);
			if (cmd->data != NOP_COMMAND_DATA) {
				return cmd;
			}
		}
	}

	for (int i = 0; i< BOARD_WINDOW_ROWS_AMOUNT; ++i) {
		for (int j= 0; j< BOARD_WINDOW_COLUMNS_AMOUNT; ++j) {
			if(isEventWindowRelated(data->soldierButtons[i][j], event) == SDL_TRUE){
				// handle soldier buttons
				cmd = data->soldierButtons[i][j]->handleEventWindow(data->soldierButtons[i][j],event);
				if (cmd != NULL && cmd->data != NOP_COMMAND_DATA) {
					return cmd;
				}
			}
		}
	}

	ErrorCode err = drawSelectedSoldier(src,event);
	if(err != OK) {
		return NULL;
	}

	cmd = createNOPCommand();
	return cmd;
}

Command* saveButtonHandler(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd = createNOPCommand();

	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		reArrageSavedGames();
		int pathLen = strlen(SAVED_GAMES_DIRECTORY_PATH) + sizeof(char) + strlen(XML_FILE_TYPE) + 1;
		char* path = (char*) malloc(pathLen * sizeof(char));
		sprintf(path,SLOT_PATH_FORMAT,SAVED_GAMES_DIRECTORY_PATH,FIRST_SLOT_NAME,XML_FILE_TYPE);
		cmd = createSaveCommand(path);
		GameBoardData* data = (GameBoardData*) src->holdingWindow->data;
		data->isGameSaved = SDL_TRUE;
	}
	return cmd;
}
Command* restartButtonHandler(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL; //Better to return an error value
	}
	Command* cmd = createNOPCommand();

	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		cmd = createResetCommand();
		src->holdingWindow->reDrawNeeded = SDL_TRUE;
		src->holdingWindow->setInnerWidgetsReDraw(src->holdingWindow,SDL_TRUE);
	}
	return cmd;
}
Command* undoButtonHandler(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
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
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	GameBoardData* data = (GameBoardData*) src->holdingWindow->data;
	Command* cmd = createNOPCommand();
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		SDL_bool isCancel = checkIfSaveGameNeeded(data);
		if(isCancel == SDL_TRUE) {
			return cmd;
		}
		src->holdingWindow->isClosed = SDL_TRUE;
		cmd = createQuitCommand();
	}
	return cmd;
}

SDL_bool checkIfSaveGameNeeded(GameBoardData* data) {
	if(data->isGameSaved == SDL_TRUE) {
		return SDL_FALSE;
	}
	MBoxSaveGameButton selectedButton = getUserSaveGameDescision();
	switch(selectedButton) {
		case BUTTON_YES:
			reArrageSavedGames();
			int pathLen = strlen(SAVED_GAMES_DIRECTORY_PATH) + sizeof(char) + strlen(XML_FILE_TYPE) + 1;
			char* path = (char*) malloc(pathLen * sizeof(char));
			sprintf(path,SLOT_PATH_FORMAT,SAVED_GAMES_DIRECTORY_PATH,FIRST_SLOT_NAME,XML_FILE_TYPE);
			Command* saveCmd = createSaveCommand(path);
			ErrorCode err =handleSaveCommand(saveCmd,data->gameSettings,data->gameState);
			if(err != OK) {
				printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
			}
			break;
		case BUTTON_CANCEL:
			return SDL_TRUE;
		case BUTTON_NO:
		case SAVE_NO_SELECTION:
			break;
	}
	return SDL_FALSE;
}

Command* mainMenuButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd = createNOPCommand();
	GameBoardData* data = (GameBoardData*) src->holdingWindow->data;
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		SDL_bool isCancel = checkIfSaveGameNeeded(data);
		if(isCancel == SDL_TRUE) {
			return cmd;
		}
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

ErrorCode drawSelectedSoldier(Window* gameWindow,SDL_Event* event) {
	if(gameWindow== NULL || event == NULL) {
		return NULL_POINTER_ERROR;
	}
	ErrorCode err = OK;
	GameBoardData* game = (GameBoardData*) gameWindow->data;
	if(game->selectedSoldier == NULL) {
		return err;
	}

	SoldierButton* selectedSoldier = (SoldierButton*) game->selectedSoldier->data;
	if(event->type == SDL_MOUSEMOTION) {
		setGameBoardInnerReDraw(gameWindow, SDL_TRUE);
		SDL_MouseMotionEvent* mmE = (SDL_MouseMotionEvent*) event;
		err = drawGameBoardWindow(gameWindow);
		SDL_Rect selectedSolR = {.x= (mmE->x - SOLDIER_BUTTON_IMAGE_WIDTH/2), .y = (mmE->y - SOLDIER_BUTTON_IMAGE_HEIGHT/2), .h = SOLDIER_BUTTON_IMAGE_HEIGHT, .w = SOLDIER_BUTTON_IMAGE_WIDTH};
		err |= SDL_RenderCopy(game->windowRenderer, selectedSoldier->buttonTexture, NULL,
			&selectedSolR);
		SDL_RenderPresent(game->windowRenderer);
	}
	return err;
}

Command* moveSelectedSoldierTo(GameBoardData* gameBoard, Window* toSoldier) {
	if(gameBoard->selectedSoldier == NULL){
		return NULL;
	}
	Command* cmd;
	SoldierButton* soldierToMove = (SoldierButton*)(gameBoard->selectedSoldier->data);
	SoldierButton* destinationSoldier= (SoldierButton*)(toSoldier->data);

	if(soldierToMove == NULL || destinationSoldier == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
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
	gameBoard->isGameSaved = SDL_FALSE;

	//gui update
	setGameBoardInnerReDraw(toSoldier->holdingWindow, SDL_TRUE);
	return cmd;
}

SDL_bool setStatusImage(GameBoardData* data, GameBoardStatuses status) {
	Window* statusBut = (Window*) data->statusButton;
	SDL_bool err;
	switch(status) {
		case NEUTRAL:
			err = updateImage(statusBut,BOARD_WINDOW_STATUS_NEUTRAL_BUTTON_PIC_PATH);
			break;
		case TIE:
			err = updateImage(statusBut,BOARD_WINDOW_STATUS_TIE_BUTTON_PIC_PATH);
			break;
		case CHECK:
			err = updateImage(statusBut,BOARD_WINDOW_STATUS_CHECK_BUTTON_PIC_PATH);
			break;
		case CHECKMATE:
			err = updateImage(statusBut,BOARD_WINDOW_STATUS_CHECKMATE_BUTTON_PIC_PATH);
			break;
		case PAWN_PROMOTION:
			err = updateImage(statusBut,BOARD_WINDOW_STATUS_PAWN_PROMOTION_BUTTON_PIC_PATH);
			break;
		case BISHOP_PROMOTION:
			err = updateImage(statusBut,BOARD_WINDOW_STATUS_BISHOP_PROMOTION_BUTTON_PIC_PATH);
			break;
		case ROCK_PROMOTION:
			err = updateImage(statusBut,BOARD_WINDOW_STATUS_ROCK_PROMOTION_BUTTON_PIC_PATH);
			break;
		case QUEEN_PROMOTION:
			err = updateImage(statusBut,BOARD_WINDOW_STATUS_QUEEN_PROMOTION_BUTTON_PIC_PATH);
			break;
		case KNIGHT_PROMOTION:
			err = updateImage(statusBut,BOARD_WINDOW_STATUS_KNIGHT_PROMOTION_BUTTON_PIC_PATH);
			break;
	}
	return err;
}
