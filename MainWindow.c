#include "MainWindow.h"

#include <stdlib.h>

#include "CommonGUIUtil.h"
#include "Window.h"
#include "LoadGameView.h"
#include "ModeSelectionView.h"
#include "ColorSelectionView.h"
#include "GameBoardView.h"
#include "SimpleButton.h"
#include "DifficultySelectionView.h"

Window** createMainWindowWidgets(Window* window,SDL_Renderer* renderer) {
	if (renderer == NULL ) {
		return NULL;
	}
	// allocate memory
	Window** widgets = malloc(sizeof(Window*) * MAIN_NUMBER_OF_BUTTONS);
	if (widgets == NULL ) {
		return NULL;
	}
	// create buttons rectangles and actual buttons
	SDL_Rect startR = { .x = MAIN_BUTTON_X_POS , .y = MAIN_BUTTON_SPACING, .h = MAIN_BUTTON_HEIGHT, .w = MAIN_BUTTON_WIDTH};
	SDL_Rect boardR = { .x = MAIN_BUTTON_X_POS , .y = 2 * MAIN_BUTTON_SPACING + MAIN_BUTTON_HEIGHT, .h = MAIN_BUTTON_HEIGHT, .w = MAIN_BUTTON_WIDTH };
	SDL_Rect exitR = { .x = MAIN_BUTTON_X_POS , .y = 3*MAIN_BUTTON_SPACING + 2*MAIN_BUTTON_HEIGHT, .h = MAIN_BUTTON_HEIGHT, .w = MAIN_BUTTON_WIDTH};
	widgets[NEW_GAME_BUTTON_INDEX] = createSimpleButton(window,renderer, &startR, NEW_GAME_PIC_PATH,newGameButtonHandler);
	widgets[LOAD_GAME_BUTTON_INDEX] = createSimpleButton(window,renderer, &boardR, LOAD_GAME_PIC_PATH, loadGameButtonHandler);
	widgets[EXIT_BUTTON_INDEX] = createSimpleButton(window,renderer, &exitR, EXIT_PIC_PATH,exitButtonHandler);
	//handle errors
	if (widgets[NEW_GAME_BUTTON_INDEX] == NULL || widgets[LOAD_GAME_BUTTON_INDEX] == NULL || widgets[EXIT_BUTTON_INDEX] == NULL ) {
		destroyWindow(widgets[NEW_GAME_BUTTON_INDEX]); //NULL SAFE
		destroyWindow(widgets[LOAD_GAME_BUTTON_INDEX]); //NULL SAFE
		destroyWindow(widgets[EXIT_BUTTON_INDEX]); //NULL SAFE
		free(widgets);
		return NULL;
	}
	initWindow(widgets[NEW_GAME_BUTTON_INDEX]);
	initWindow(widgets[LOAD_GAME_BUTTON_INDEX]);
	initWindow(widgets[EXIT_BUTTON_INDEX]);
	return widgets;
}
Window* createMainWindow(GameSettings* gameSettings, GameState* gameState) {
	// allocate memory
	Window* res = malloc(sizeof(Window));
	if(res == NULL) {
		return NULL;
	}
	MainWindow* data = malloc(sizeof(MainWindow));
	if(data == NULL) {
		free(res);
		return NULL;
	}
	res->isClosed = SDL_FALSE;
	data->gameState = gameState;
	data->gameSettings = gameSettings;
	res->location = createInvlidRect();
	// create the main wondow of GUI
	SDL_Window* window = SDL_CreateWindow(MAIN_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);
	// create buttons of the view
	Window** widgets = createMainWindowWidgets(res,renderer);
	// handle creation errors
	if (window == NULL || renderer == NULL || widgets == NULL ) {
		free(res);
		free(data);
		free(widgets);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		return NULL;
	}
	// set data members
	data->numOfWidgets = MAIN_NUMBER_OF_BUTTONS;
	data->window = window;
	data->windowRenderer = renderer;
	data->mainMenuWidgets = widgets;
	data->view = MAIN_VIEW;
	data->viewWindow = res;
	initWindow(res);
	res->data = (void*) data;
	// init and set views
	data->boardViewWindow = (Window*) createBoardWindow(res, data->gameSettings, data->gameState);
	initWindow(data->boardViewWindow);
	data->difficultySelectionViewWindow = (Window*) createDifficultySelectionView(res, data->gameSettings, data->gameState);
	initWindow(data->difficultySelectionViewWindow);
	data->colorSelectionViewWindow = (Window*) createColorSelectionView(res, data->gameSettings, data->gameState);
	initWindow(data->colorSelectionViewWindow);
	data->modeSelectionViewWindow = (Window*) createModeSelectionView(res, data->gameSettings, data->gameState);
	initWindow(data->modeSelectionViewWindow);
	data->loadGameViewWindow = (Window*) createLoadGameView(res, data->gameSettings, data->gameState);
	initWindow(data->loadGameViewWindow);
	// handle errors
	if (data->boardViewWindow == NULL || data->difficultySelectionViewWindow== NULL || data->modeSelectionViewWindow== NULL ||
			data->colorSelectionViewWindow == NULL || data->loadGameViewWindow== NULL) {
		SDL_Quit();
		return NULL;
	}
	res->destroyWindow = destroyMainWindow;
	res->drawWindow = drawMainWindow;
	res->handleEventWindow = handleEventMainWindow;
	res->holdingWindow = NULL;
	res->handleError = handleMainWindowError;
	res->setInnerWidgetsReDraw = setMainWindowInnerReDraw;
	return res;
}

void destroyMainWindow(Window* src) {
	if (src == NULL ) {
		return;
	}
	MainWindow* data = (MainWindow*) src->data;
	int i = 0;
	for (; i < data->numOfWidgets; i++) {
		destroyWindow(data->mainMenuWidgets[i]);
	}
	destroyWindow(data->boardViewWindow);
	destroyWindow(data->difficultySelectionViewWindow);
	destroyWindow(data->modeSelectionViewWindow);
	destroyWindow(data->colorSelectionViewWindow);
	destroyWindow(data->loadGameViewWindow);
	free(src->location);
	free(data->mainMenuWidgets);
	SDL_DestroyRenderer(data->windowRenderer);
	SDL_DestroyWindow(data->window);
	free(data);
	free(src);
}
void drawMainWindow(Window* src) {
	if (src == NULL ) {
		return;
	}
	MainWindow* data = (MainWindow*) src->data;
	// draw according to current view
	switch(data->view)
	{
		case MAIN_VIEW:
			if(src->reDrawNeeded)
			{
				SDL_SetRenderDrawColor(data->windowRenderer, MAIN_WINDOW_BGCOLOR_RED, MAIN_WINDOW_BGCOLOR_GREEN, MAIN_WINDOW_BGCOLOR_BLUE, MAIN_WINDOW_BGCOLOR_ALPHA);
				SDL_RenderClear(data->windowRenderer);
			}
			for (int i = 0; i < data->numOfWidgets; i++) {
				src->reDrawNeeded |= (data->mainMenuWidgets[i])->reDrawNeeded;
				(data->mainMenuWidgets[i])->drawWindow(data->mainMenuWidgets[i]);
			}
			if(src->reDrawNeeded)
			{
				SDL_RenderPresent(data->windowRenderer);
			}
			src->reDrawNeeded = SDL_FALSE;
			break;
		case BOARD_VIEW:
			src->reDrawNeeded |= data->boardViewWindow->reDrawNeeded;
			data->boardViewWindow->drawWindow(data->boardViewWindow);
			break;
		case DIFFICULTY_SELECTION_VIEW:
			src->reDrawNeeded |= data->difficultySelectionViewWindow->reDrawNeeded;
			data->difficultySelectionViewWindow->drawWindow(data->difficultySelectionViewWindow);
			break;
		case COLOR_SELECTION_VIEW:
			src->reDrawNeeded |= data->colorSelectionViewWindow->reDrawNeeded;
			data->colorSelectionViewWindow->drawWindow(data->colorSelectionViewWindow);
			break;
		case MODE_SELECTION_VIEW:
			src->reDrawNeeded |= data->modeSelectionViewWindow->reDrawNeeded;
			data->modeSelectionViewWindow->drawWindow(data->modeSelectionViewWindow);
			break;
		case LOAD_GAME_VIEW:
			src->reDrawNeeded |= data->loadGameViewWindow->reDrawNeeded;
			data->loadGameViewWindow->drawWindow(data->loadGameViewWindow);
			break;
		case UNINITIALIZED_VIEW:
			return;
	}
}

Command* handleEventMainWindow(Window* src, SDL_Event* event){
	if(src == NULL || event==NULL){
		return NULL;
	}
	Command* cmd = createNOPCommand();
	MainWindow* data = (MainWindow*)src->data;
	// handle events according to current view
	switch(data->view)
	{
		case MAIN_VIEW:
			// check each of the view buttons
			for(int i =0;i<data->numOfWidgets;i++){
				if(isEventWindowRelated(data->mainMenuWidgets[i], event) == SDL_TRUE) {
					src->reDrawNeeded |= data->mainMenuWidgets[i]->reDrawNeeded;
					cmd = data->mainMenuWidgets[i]->handleEventWindow(data->mainMenuWidgets[i],event);
				}
			}
			break;
		case BOARD_VIEW:
			cmd = data->boardViewWindow->handleEventWindow(data->boardViewWindow,event);
			if(data->boardViewWindow->isClosed == SDL_TRUE) {
				src->isClosed = SDL_TRUE;
			}
			break;
		case DIFFICULTY_SELECTION_VIEW:
			cmd = data->difficultySelectionViewWindow->handleEventWindow(data->difficultySelectionViewWindow,event);
			break;
		case COLOR_SELECTION_VIEW:
			cmd = data->colorSelectionViewWindow->handleEventWindow(data->colorSelectionViewWindow,event);
			break;
		case MODE_SELECTION_VIEW:
			cmd = data->modeSelectionViewWindow->handleEventWindow(data->modeSelectionViewWindow,event);
			break;
		case LOAD_GAME_VIEW:
			cmd = data->loadGameViewWindow->handleEventWindow(data->loadGameViewWindow,event);
			break;
		case UNINITIALIZED_VIEW:
			return NULL;
			break;
	}
	return cmd;
}

Command* newGameButtonHandler(Window* src, SDL_Event* event)
{
	if (src == NULL || event == NULL ) {
		return NULL;
	}
	Command* cmd = createNOPCommand();
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		cmd = createStartCommand();
		setCurrentView(src->holdingWindow, MODE_SELECTION_VIEW);
		return cmd;
	}
	return cmd;
}

Command* loadGameButtonHandler(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return NULL;
	}
	Command* cmd = createNOPCommand();
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow, LOAD_GAME_VIEW);
	}
	return cmd;
}
Command* exitButtonHandler(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return NULL;
	}
	Command* cmd = createNOPCommand();
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		src->holdingWindow->isClosed = SDL_TRUE;
		cmd = createQuitCommand();
	}
	return cmd;
}


void setCurrentView(Window* src, enum WindowView view) {
	MainWindow* mainWin = (MainWindow*) src->data;
	LoadGameView* loadWin = (LoadGameView*) (mainWin->loadGameViewWindow->data);
	src->reDrawNeeded = SDL_TRUE;
	switch(view)
	{
		case MAIN_VIEW:
			mainWin->viewWindow = src;
			src->reDrawNeeded = SDL_TRUE;
			break;
		case BOARD_VIEW:
			mainWin->viewWindow = mainWin->boardViewWindow;
			mainWin->boardViewWindow->reDrawNeeded = SDL_TRUE;
			break;
		case DIFFICULTY_SELECTION_VIEW:
			mainWin->viewWindow = mainWin->difficultySelectionViewWindow;
			mainWin->difficultySelectionViewWindow->reDrawNeeded = SDL_TRUE;
			break;
		case COLOR_SELECTION_VIEW:
			mainWin->viewWindow = mainWin->colorSelectionViewWindow;
			mainWin->colorSelectionViewWindow->reDrawNeeded = SDL_TRUE;
			break;
		case MODE_SELECTION_VIEW:
			mainWin->viewWindow = mainWin->modeSelectionViewWindow;
			mainWin->modeSelectionViewWindow->reDrawNeeded = SDL_TRUE;
			break;
		case LOAD_GAME_VIEW:
			updateSlotButtons(mainWin->loadGameViewWindow);
			loadWin->lastView = mainWin->view;
			mainWin->viewWindow = mainWin->loadGameViewWindow;
			mainWin->loadGameViewWindow->reDrawNeeded = SDL_TRUE;
			break;
		case UNINITIALIZED_VIEW:
			return;
	}
	mainWin->view = view;
	// we want to redraw the view cause we are switching to it
	mainWin->viewWindow->setInnerWidgetsReDraw(mainWin->viewWindow,SDL_TRUE);
}

void setMainWindowInnerReDraw(Window* src, SDL_bool reDraw) {
	MainWindow* data = (MainWindow*)src->data;
	src->reDrawNeeded = reDraw;
	for (int i = 0; i < data->numOfWidgets; i++) {
		(data->mainMenuWidgets[i])->reDrawNeeded = reDraw;
	}
}

ErrorCode handleMainWindowError(Window* src, ErrorCode err) {
	// if solvable, solve
	switch (err) {
		case LOAD_ERROR:
			setCurrentView(src, LOAD_GAME_VIEW);
			err = OK;
			break;
		case SAVE_ERROR:
			setCurrentView(src, BOARD_VIEW);
			err = OK;
			break;
		case SLOTS_LOAD_ERROR:
		case IMAGE_ERROR:
		case NULL_POINTER_ERROR:
		case MEMORY_ERROR:
		case GENERAL_ERROR:
		case CONTROLLER_END:
		case OK:
			break;
		default:
			break;
	}
	return err;
}
