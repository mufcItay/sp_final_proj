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
#include "PawnPromotionMessageBox.h"
#include "InfoMessageBox.h"

/////TODO:TEST
#include "co/moves.h"
#include "co/utilities.h"

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
	Window* res = calloc(1,sizeof(Window));
	if(res == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	GameBoardData* data = calloc(1,sizeof(GameBoardData));
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(res);
		return NULL;
	}
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
	if (holdingWindow == NULL || renderer == NULL || widgets == NULL || menuButtons == NULL|| statusWindow == NULL) {
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
	data->selectedSoldier = NULL;
	data->statusButton = statusWindow;
	data->dragDropIgnored = 0;
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
	if(data->soldierButtons != NULL) {
		destroySoldierButtonMatrix(data->soldierButtons);
	}
	if(data->menuButtons != NULL) {
		destroyMenuButtons(data->menuButtons);
	}
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
		err |= setStatusImage(data);
		err |= updateUndoState(src,data->gameState);
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
	Command* cmd = createNOPCommand();
	GameBoardData* data = (GameBoardData*)src->data;
	for (int i = 0; i < BOARD_WINDOW_BUTTONS_AMOUNT; ++i) {
		if(isEventWindowRelated(data->menuButtons[i], event) == SDL_TRUE){
			// handle menu buttons
			if(data->selectedSoldier != NULL) {
				return cmd;
			}
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
;
	return cmd;
}

void setSaveEnabledState(Window* src, SDL_bool enabled) {
	GameBoardData* data = (GameBoardData*) src->data;
	setEnabledSimpleButton(data->menuButtons[BOARD_WINDOW_SAVE_GAME_BUTTON_INDEX],enabled);
}

Command* saveButtonHandler(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd = createNOPCommand();
	SimpleButton* sb = (SimpleButton*) src->data;
	if(sb->isEnabled == SDL_FALSE) {
		return cmd;
	}

	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		reArrageSavedGames();
		int pathLen = strlen(SAVED_GAMES_DIRECTORY_PATH) + sizeof(char) + strlen(XML_FILE_TYPE) + 1;
		char* path = (char*) malloc(pathLen * sizeof(char));
		sprintf(path,SLOT_PATH_FORMAT,SAVED_GAMES_DIRECTORY_PATH,FIRST_SLOT_NAME,XML_FILE_TYPE);
		cmd = createSaveCommand(path);
		setEnabledSimpleButton(src,SDL_FALSE);
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
		src->holdingWindow->reDrawNeeded = SDL_TRUE;
		src->reDrawNeeded = SDL_TRUE;
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
	SimpleButton* sb = data->menuButtons[BOARD_WINDOW_SAVE_GAME_BUTTON_INDEX];
	if(sb->isEnabled == SDL_FALSE) {
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
		// avoid drawing drag and drop live motion for better performance
		if(game->dragDropIgnored < MAX_DRAG_DROPIGNORED) {
			++game->dragDropIgnored;
			return err;
		}
		game->dragDropIgnored = 0;
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
	Command* cmd = createNOPCommand();
	SoldierButton* soldierToMove = (SoldierButton*)(gameBoard->selectedSoldier->data);
	SoldierButton* destinationSoldier= (SoldierButton*)(toSoldier->data);

	if(soldierToMove == NULL || destinationSoldier == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	// anyway, redraw next time to delete selected soldier blueprint
	setGameBoardInnerReDraw(toSoldier->holdingWindow, SDL_TRUE);

	/////TODO:TEST
	getMovesPosition(gameBoard->gameState->board, gameBoard->gameState->turn, soldierToMove->rowIndex, soldierToMove->columnIndex);
	int result = isLegalMove_no_ptr(soldierToMove->rowIndex, soldierToMove->columnIndex, destinationSoldier->rowIndex, destinationSoldier->columnIndex);
	if (result == true) {
		//                move(command,color);

		freeMoves_all();
//		int check_status = isKingThreatened(gameBoard->gameState->board, invertColor(gameBoard->gameState->turn)) ;
//
//		int allowed_moves_opponent = calc_all_allowed_moves (gameBoard->gameState->board, invertColor(gameBoard->gameState->turn));
//
//		if ( ( allowed_moves_opponent == 1 ) &&  ( check_status == 1) ) {  // no moves allowed
//			updateGameStatusImage(CHECKMATE, gameBoard->statusButton);
//		}
//		if ( ( allowed_moves_opponent == 0 ) && (check_status == 1)) {
//			updateGameStatusImage(CHECK, gameBoard->statusButton);
//		}
//		if ( ( allowed_moves_opponent == 1 ) && (check_status == 0)) {
//			updateGameStatusImage(TIE, gameBoard->statusButton);
//				}


	}
		else {
		gameBoard->selectedSoldier = NULL;
		return cmd;
	}


	//	//TODO:TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	ChessGame* cg = chessGameCreate(2,2,0);
//	cg->currentPlayer = gameBoard->gameState->turn;
//	cg->gameBoard = gameBoard->gameState->board;
//	if(isValidMove(cg,soldierToMove->rowIndex,soldierToMove->columnIndex,destinationSoldier->rowIndex,destinationSoldier->columnIndex) == SDL_FALSE) {
//		return cmd;
//	}
//
//	CHESS_GAME_MESSAGE stat = checkStatus(cg);
//	switch (stat) {
//	case     CHESS_GAME_INVALID_MOVE :
//	case     CHESS_GAME_INVALID_ARGUMENT:
//	case     CHESS_GAME_NO_HISTORY:
//	case     CHESS_UN_SPECIAL_STATUS:
//		return NULL;
//	case     CHESS_GAME_SUCCESS:
//		updateGameStatusImage(NEUTRAL, gameBoard->statusButton);
//		break;
//	case     CHESS_GAME_CHECK:
//		updateGameStatusImage(CHECK, gameBoard->statusButton);
//				break;
//	case     CHESS_GAME_MATE:
//		updateGameStatusImage(CHECKMATE, gameBoard->statusButton);
//				break;
//	case     CHESS_GAME_TIE:
//		updateGameStatusImage(TIE, gameBoard->statusButton);
//				break;
//	}
//		if(invalid move) continue
//		else - removes selection (gameBoard->selectedSoldier = NULL) and re draw
//	return CreateNOPCommand();


	//if(check or check mate, react GUI'li)

	SDL_Point origin = {.x = soldierToMove->rowIndex, .y = soldierToMove->columnIndex};
	SDL_Point destination = {.x = destinationSoldier->rowIndex, .y = destinationSoldier->columnIndex};
	cmd = createMoveCommand(origin,destination);
	setEnabledSimpleButton(gameBoard->menuButtons[BOARD_WINDOW_SAVE_GAME_BUTTON_INDEX],SDL_TRUE);
	return cmd;
}

ErrorCode updateGameStatusImage(GameBoardStatuses gameStatus, Window* statusBut) {
	ErrorCode err = OK;
	switch (gameStatus) {
	case NEUTRAL:
		err |= updateImage(statusBut,
				BOARD_WINDOW_STATUS_NEUTRAL_BUTTON_PIC_PATH);
		break;
	case TIE:
		err |= updateImage(statusBut, BOARD_WINDOW_STATUS_TIE_BUTTON_PIC_PATH);
		break;
	case CHECK:
		err |= updateImage(statusBut,
				BOARD_WINDOW_STATUS_CHECK_BUTTON_PIC_PATH);
		break;
	case CHECKMATE:
		err |= updateImage(statusBut,
				BOARD_WINDOW_STATUS_CHECKMATE_BUTTON_PIC_PATH);
		break;
	case PAWN_PROMOTION:
	case BISHOP_PROMOTION:
	case ROCK_PROMOTION:
	case QUEEN_PROMOTION:
	case KNIGHT_PROMOTION:
		break;
	}
	return err;
}

ErrorCode showComputerPawnPromotion(GameBoardStatuses promotionStatus) {
	ErrorCode err = OK;
	switch (promotionStatus) {
	case PAWN_PROMOTION:
		err = showInfoMessageBox(PAWN_PROMOTION_MESSAGE);
		break;
	case BISHOP_PROMOTION:
		err = showInfoMessageBox(BISHOP_PROMOTION_MESSAGE);
		break;
	case ROCK_PROMOTION:
		err = showInfoMessageBox(ROCK_PROMOTION_MESSAGE);
		break;
	case QUEEN_PROMOTION:
		err = showInfoMessageBox(QUEEN_PROMOTION_MESSAGE);
		break;
	case KNIGHT_PROMOTION:
		err = showInfoMessageBox(KNIGHT_PROMOTION_MESSAGE);
		break;
	case NEUTRAL:
	case TIE:
	case CHECK:
	case CHECKMATE:
		err = GENERAL_ERROR;
		break;
	}
	return err;
}

ErrorCode setStatusImage(GameBoardData* data) {
	//TODO: GameBoardStatuses status = gtStatusOfGameFromNoam;
	GameBoardStatuses status = NEUTRAL;
	Window* statusBut = (Window*) data->statusButton;
	// game status is 8 bit for game status and the rest is pawn promotion bits
	GameBoardStatuses gameStatus = status & GAME_RESULT_STATUS_BITMASK;
	GameBoardStatuses promotionStatus = status & PROMOTION_STATUS_BITMASK;

	ErrorCode err = OK;
	err = updateGameStatusImage(gameStatus, statusBut);
	if(promotionStatus == 0 || err != OK) {
		return err;
	}
	err = showComputerPawnPromotion(promotionStatus);
	return err;
}


ErrorCode updateUndoState(Window* gameWindow, GameState* state) {
	if(gameWindow == NULL || state == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}
	GameBoardData* gameBoardData =  (GameBoardData*) gameWindow->data;
	//TODO:if undo history is empty !!
	gameBoardData->menuButtons[BOARD_WINDOW_UNDO_BUTTON_INDEX]->reDrawNeeded = SDL_TRUE;
	if(state->moveHistory == NULL) {
		setEnabledSimpleButton(gameBoardData->menuButtons[BOARD_WINDOW_UNDO_BUTTON_INDEX], SDL_FALSE);
	}
	else {
		setEnabledSimpleButton(gameBoardData->menuButtons[BOARD_WINDOW_UNDO_BUTTON_INDEX], SDL_TRUE);
	}
	return OK;
}
