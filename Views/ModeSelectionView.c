#include "ModeSelectionView.h"

#include <stdlib.h>
#include "SimpleButton.h"
#include "CommonGUIUtil.h"
#include "Window.h"
#include "MainWindow.h"
#include "CommonStructures.h"
#include "Commands.h"

Window** createModeButtons(Window* holdingWindow, SDL_Renderer* renderer)
{
	if (holdingWindow == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL ;
	}
	// allocate memory
	Window** modeButtons = calloc(MODE_SELECTION_WINDOW_MODES_AMOUNT,sizeof(Window*));
	if (modeButtons == NULL ) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	for (int i = 0; i < MODE_SELECTION_WINDOW_MODES_AMOUNT; ++i) {
		// create rectangles and actual buttons of mode selection
		SDL_Rect modeButtonR = {.x = 0, .y = MODE_SELECTION_WINDOW_BUTTON_HEIGHT * i + MODE_SELECTION_WINDOW_BUTTON_SPACING *i, .h = MODE_SELECTION_WINDOW_BUTTON_HEIGHT, .w = MODE_SELECTION_WINDOW_BUTTON_WIDTH};
		char* imagePath = getModeImagePath(i, SDL_FALSE);
		if(imagePath != NULL){
			modeButtons[i] = (Window*) createSimpleButton(holdingWindow,renderer, &modeButtonR,imagePath ,modeButtonHandler);
		}
		if (modeButtons[i] == NULL) {
			destroyModeButtons(modeButtons);
			return NULL;
		}
		initWindow(modeButtons[i]);
	}
	return modeButtons;
}

Window** createModeNavigationButtons(Window* holdingWindow, SDL_Renderer* renderer){
	// allocate memory
	Window** navigationButtons = calloc(MODE_SELECTION_WINDOW_NAVIGATIONS_AMOUNT,sizeof(Window*));
	if (navigationButtons == NULL ) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	// create rectangles and actual buttons of navigation
	SDL_Rect nextR = { .x = 0, .y = MODE_SELECTION_NAVIGTION_PANE_Y_POS, .h = MODE_SELECTION_WINDOW_BUTTON_HEIGHT, .w = MODE_SELECTION_WINDOW_BUTTON_WIDTH};
	SDL_Rect backR = { .x = MODE_SELECTION_WINDOW_BUTTON_WIDTH + BOARD_WINDOW_BUTTON_SPACING , .y = MODE_SELECTION_NAVIGTION_PANE_Y_POS, .h = MODE_SELECTION_WINDOW_BUTTON_HEIGHT, .w = MODE_SELECTION_WINDOW_BUTTON_WIDTH};
	navigationButtons[MODE_SELECTION_WINDOW_BACK_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &backR,MODE_SELECTION_WINDOW_BACK_BUTTON_PIC_PATH ,backModeButtonHandler);
	initWindow(navigationButtons[MODE_SELECTION_WINDOW_BACK_BUTTON_INDEX]);
	navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &nextR, MODE_SELECTION_WINDOW_NEXT_BUTTON_PIC_PATH, nextModeButtonHandler);
	initWindow(navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX]);
	// handle navigation buttons creation error
	if (navigationButtons[MODE_SELECTION_WINDOW_BACK_BUTTON_INDEX] == NULL || navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX] == NULL ) {
		destroyModeNavigationButtons(navigationButtons);
		return NULL ;
	}
	return navigationButtons;
}

Window* createModeSelectionView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState) {
	// allocate memory
	Window* res = calloc(1,sizeof(Window));
	if(res == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	ModeSelectionView* data = calloc(1,sizeof(ModeSelectionView));
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	data->gameState = gameState;
	data->gameSettings = gameSettings;
	MainWindow* main = (MainWindow*)holdingWindow->data;
	// create rectangle for the view
	SDL_Rect difficultiesR = { .x = 0, .y = 0, .h = MODE_SELECTION_WINDOW_HEIGHT, .w = MODE_SELECTION_WINDOW_WIDTH};
	res->location = &difficultiesR;
	SDL_Renderer* renderer = main->windowRenderer;
	Window** modeWidgets = createModeButtons(res, renderer);
	Window** navigationButtons = createModeNavigationButtons(res, renderer);
	res->data = (void*) data;
	// set members
	if (res == NULL || data == NULL || holdingWindow == NULL || renderer == NULL
			|| modeWidgets == NULL || navigationButtons == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		destroyModeSelectionView(res);
		return NULL ;
	}
	data->modeButtons = modeWidgets;
	data->windowRenderer = renderer;
	data->navigationButtons = navigationButtons;
	// selected mode is zero based
	data->selectedMode = gameSettings->mode -1;
	// handle buttons creation errors
	res->destroyWindow = destroyModeSelectionView;
	res->drawWindow = drawModeSelectionView;
	res->handleEventWindow = handleEventModeSelectionView;
	res->holdingWindow = holdingWindow;
	res->setInnerWidgetsReDraw = setModeSelectionInnerReDraw;
	initWindow(res);
	// set default mode selection
	ErrorCode err = updateSelectedMode(MODE_UNSELECTED, data->selectedMode,data);
	if(err != OK) {
		return NULL;
	}
	return res;

}

void destroyModeButtons(Window** modeButtons) {
	for (int i = 0; i < MODE_SELECTION_WINDOW_MODES_AMOUNT; ++i) {
		destroyWindow(modeButtons[i]);
	}
	free(modeButtons);
}

void destroyModeNavigationButtons(Window** navigationButtons) {
	for (int i = 0; i < MODE_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		destroyWindow(navigationButtons[i]);
	}
	free(navigationButtons);
}

void destroyModeSelectionView(Window* src) {
	if (src == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return;
	}
	ModeSelectionView* data = (ModeSelectionView*) src->data;
	if(data->modeButtons  != NULL) {
		destroyModeButtons(data->modeButtons);
	}
	if(data->navigationButtons != NULL) {
		destroyModeNavigationButtons(data->navigationButtons);
	}
	SDL_DestroyRenderer(data->windowRenderer);
	free(data);
	free(src);
}

ErrorCode drawModeSelectionView(Window* src) {
	if (src == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}
	ErrorCode err = OK;
	ModeSelectionView* data = (ModeSelectionView*) src->data;
	if(src->reDrawNeeded)
	{
		err |= SDL_SetRenderDrawColor(data->windowRenderer, MODE_SELECTION_WINDOW_BGCOLOR_RED, MODE_SELECTION_WINDOW_BGCOLOR_GREEN, MODE_SELECTION_WINDOW_BGCOLOR_BLUE, MODE_SELECTION_WINDOW_BGCOLOR_ALPHA);
		err |= SDL_RenderClear(data->windowRenderer);
		if(err != OK) {
			err = SDL_ERROR;
			return err;
		}
	}
	for (int i = 0; i< MODE_SELECTION_WINDOW_MODES_AMOUNT; ++i) {
		// draw mode selection buttons
		src->reDrawNeeded |= data->modeButtons[i]->reDrawNeeded;
		err |= data->modeButtons[i]->drawWindow(data->modeButtons[i]);
		if(err != OK) {
			err = SDL_ERROR;
			return err;
		}
	}
	for (int i = 0; i < MODE_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		// draw navigation buttons
		src->reDrawNeeded |= data->navigationButtons[i]->reDrawNeeded;
		err |= data->navigationButtons[i]->drawWindow(data->navigationButtons[i]);
		if(err != OK) {
			err = SDL_ERROR;
			return err;
		}
	}
	if(src->reDrawNeeded) {
		SDL_RenderPresent(data->windowRenderer);
	}
	src->reDrawNeeded = SDL_FALSE;
	return err;
}

Command* handleEventModeSelectionView(Window* src, SDL_Event* event){
	if(src == NULL || event==NULL){
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd;
	ModeSelectionView* data = (ModeSelectionView*) src->data;
	for (int i = 0; i< MODE_SELECTION_WINDOW_MODES_AMOUNT; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->modeButtons[i], event) == SDL_TRUE){
			// handle event for selection buttons
			cmd = data->modeButtons[i]->handleEventWindow(data->modeButtons[i],event);
			if(cmd == NULL) {
				return NULL;
			}
			if(updateSelectedMode(data->selectedMode,i,data) != OK) {
				return NULL;
			}
			else {
				GameMode selectedMode = getMode(data->selectedMode);
				cmd = createGameModeCommand(selectedMode);
				return cmd;
			}
		}
	}
	for (int i = 0; i < MODE_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->navigationButtons[i], event) == SDL_TRUE){
			// handle event for navigation buttons
			cmd = data->navigationButtons[i]->handleEventWindow(data->navigationButtons[i],event);
			if(cmd->data != NOP_COMMAND_DATA) {
				return cmd;
			}
		}
	}
	cmd = createNOPCommand();
	return cmd;
}
Command* nextModeButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}

	Command* cmd = createNOPCommand();
	SimpleButton* data = (SimpleButton*) src->data;
	ModeSelectionView* modeSelectionView = (ModeSelectionView*) (src->holdingWindow->data);
	if(data->isEnabled == SDL_FALSE){
		return cmd;
	}
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		if(modeSelectionView->selectedMode == MODE_UNSELECTED) {
			printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
			return NULL;
		}
		enum WindowView nextView = DIFFICULTY_SELECTION_VIEW;
		if(modeSelectionView->selectedMode == MODE_SELECTION_WINDOW_TWO_PLAYERS_INDEX) {
			nextView = BOARD_VIEW;
		}
		setCurrentView(src->holdingWindow->holdingWindow, nextView);
		cmd = createGameModeCommand(modeSelectionView->selectedMode);
		return cmd;
	}
	return cmd;
}

Command* backModeButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd = createNOPCommand();
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow, MAIN_VIEW);
	}
	return cmd;
}

Command* modeButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd = createNOPCommand();
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
	}
	return cmd;
}


ErrorCode updateSelectedMode(int lastSelectedMode, int currentlySelectedMode, ModeSelectionView* view) {
	// get window of selected mode
	Window* selectedMode = (Window*) view->modeButtons[currentlySelectedMode];
	// update image of selected mode
	char* imagePath = getModeImagePath(currentlySelectedMode, SDL_TRUE);
	ErrorCode err = updateImage(selectedMode, imagePath);
	if(err != OK) {
		return err;
	}
	setEnabledSimpleButton(view->navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX], SDL_TRUE);
	if(lastSelectedMode != MODE_UNSELECTED)
	{
		// update image of last selected mode
		imagePath = getModeImagePath(lastSelectedMode, SDL_FALSE);
		Window* lastSelected = (Window*) view->modeButtons[lastSelectedMode];
		ErrorCode err = updateImage(lastSelected, imagePath);
		if(err != OK) {
			return err;
		}
		if(lastSelectedMode == currentlySelectedMode)
		{
			view->selectedMode = MODE_UNSELECTED;
			setEnabledSimpleButton(view->navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX], SDL_FALSE);
			return OK;
		}
	}
	view->selectedMode = currentlySelectedMode;

	return OK;
}

char* getModeImagePath(int mode, SDL_bool isSelected) {
	if(mode == MODE_SELECTION_WINDOW_SINGLE_PALYER_BUTTON_INDEX) {
		if(isSelected == SDL_TRUE){
			return MODE_SELECTION_WINDOW_SINGLE_PLAYER_BUTTON_SELECTED_PIC_PATH;
		}
		return MODE_SELECTION_WINDOW_SINGLE_PLAYER_BUTTON_NOT_SELECTED_PIC_PATH;
	}
	if(isSelected == SDL_TRUE){
		return MODE_SELECTION_WINDOW_TWO_PLAYERS_BUTTON_SELECTED_PIC_PATH;
	}
	return MODE_SELECTION_WINDOW_TWO_PLAYERS_BUTTON_NOT_SELECTED_PIC_PATH;
}


void setModeSelectionInnerReDraw(Window* src, SDL_bool reDraw) {
	if(src == NULL){
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return;
	}
	ModeSelectionView* data = (ModeSelectionView*) src->data;
	for (int i = 0; i< MODE_SELECTION_WINDOW_MODES_AMOUNT; ++i) {
		data->modeButtons[i]->reDrawNeeded = reDraw;
	}
	for (int i = 0; i < MODE_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		data->navigationButtons[i]->reDrawNeeded = reDraw;
	}
}
