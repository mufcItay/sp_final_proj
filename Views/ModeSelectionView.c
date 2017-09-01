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
		return NULL ;
	}
	Window** modeButtons = calloc(MODE_SELECTION_WINDOW_MODES_AMOUNT,sizeof(Window*));
	if (modeButtons == NULL ) {
		return NULL;
	}
	for (int i = 0; i < MODE_SELECTION_WINDOW_MODES_AMOUNT; ++i) {
		SDL_Rect modeButtonR = {.x = 0, .y = MODE_SELECTION_WINDOW_BUTTON_HEIGHT * i + MODE_SELECTION_WINDOW_BUTTON_SPACING *i, .h = MODE_SELECTION_WINDOW_BUTTON_HEIGHT, .w = MODE_SELECTION_WINDOW_BUTTON_WIDTH};
		char* imagePath = GetModeImagePath(i, SDL_FALSE);
		if(imagePath != NULL){
			modeButtons[i] = (Window*) createSimpleButton(holdingWindow,renderer, &modeButtonR,imagePath ,ModeButtonHandler);
		}
		if (modeButtons[i] == NULL) {
			for (int i = 0; i < MODE_SELECTION_WINDOW_MODES_AMOUNT; ++i) {
					destroyWindow(modeButtons[i]); //NULL SAFE
			}
			free(modeButtons);
		}
		initWindow(modeButtons[i]);
	}
	return modeButtons;
}

Window** createModeNavigationButtons(Window* holdingWindow, SDL_Renderer* renderer){
	Window** navigationButtons = calloc(MODE_SELECTION_WINDOW_NAVIGATIONS_AMOUNT,sizeof(Window*));
	if (navigationButtons == NULL ) {
		return NULL;
	}
	SDL_Rect nextR = { .x = 0, .y = MODE_SELECTION_NAVIGTION_PANE_Y_POS, .h = MODE_SELECTION_WINDOW_BUTTON_HEIGHT, .w = MODE_SELECTION_WINDOW_BUTTON_WIDTH};
	SDL_Rect backR = { .x = MODE_SELECTION_WINDOW_BUTTON_WIDTH + BOARD_WINDOW_BUTTON_SPACING , .y = MODE_SELECTION_NAVIGTION_PANE_Y_POS, .h = MODE_SELECTION_WINDOW_BUTTON_HEIGHT, .w = MODE_SELECTION_WINDOW_BUTTON_WIDTH};
	navigationButtons[MODE_SELECTION_WINDOW_BACK_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &backR,MODE_SELECTION_WINDOW_BACK_BUTTON_PIC_PATH ,BackModeButtonHandler);
	initWindow(navigationButtons[MODE_SELECTION_WINDOW_BACK_BUTTON_INDEX]);
	navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &nextR, MODE_SELECTION_WINDOW_NEXT_BUTTON_PIC_PATH, NextModeButtonHandler);
	initWindow(navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX]);

	setEnabledSimpleButton(navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX], SDL_FALSE);

	if (navigationButtons[MODE_SELECTION_WINDOW_BACK_BUTTON_INDEX] == NULL || navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX] == NULL ) {
		destroyWindow(navigationButtons[MODE_SELECTION_WINDOW_BACK_BUTTON_INDEX]); //NULL SAFE
		destroyWindow(navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX]); //NULL SAFE
		free(navigationButtons);
		return NULL ;
	}

	return navigationButtons;
}

Window* createModeSelectionView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState) {
	Window* res = malloc(sizeof(Window));
	ModeSelectionView* data = malloc(sizeof(ModeSelectionView));
	data->gameState = gameState;
	data->gameSettings = gameSettings;
	MainWindow* main = (MainWindow*)holdingWindow->data;
	SDL_Rect difficultiesR = { .x = 0, .y = 0, .h = MODE_SELECTION_WINDOW_HEIGHT, .w = MODE_SELECTION_WINDOW_WIDTH};
	res->location = &difficultiesR;
	SDL_Renderer* renderer = main->windowRenderer;
	Window** modeWidgets = createModeButtons(res, renderer);
	Window** navigationButtons = createModeNavigationButtons(res, renderer);
	if (res == NULL || data == NULL || holdingWindow == NULL || renderer == NULL
			|| modeWidgets == NULL || navigationButtons == NULL) {
		free(res);
		free(data);
		free(modeWidgets);
		free(navigationButtons);
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer); //NULL safe
		destroyWindow(holdingWindow); //NULL safe
		return NULL ;
	}
	data->modeButtons = modeWidgets;
	data->windowRenderer = renderer;
	data->navigationButtons = navigationButtons;
	data->selectedMode = MODE_UNSELECTED;
	res->data = (void*) data;
	res->destroyWindow = destroyModeSelectionView;
	res->drawWindow = drawModeSelectionView;
	res->handleEventWindow = handleEventModeSelectionView;
	res->holdingWindow = holdingWindow;
	res->setInnerWidgetsReDraw = setModeSelectionInnerReDraw;
	initWindow(res);
	return res;

}
void destroyModeSelectionView(Window* src) {
	if (src == NULL ) {
		return;
	}
	ModeSelectionView* data = (ModeSelectionView*) src->data;
	for (int i = 0; i< MODE_SELECTION_WINDOW_MODES_AMOUNT; ++i) {
		destroyWindow(data->modeButtons[i]);
	}
	for (int i = 0; i < MODE_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		destroyWindow(data->navigationButtons[i]);
	}
	free(data->modeButtons);
	free(data->navigationButtons);
	SDL_DestroyRenderer(data->windowRenderer);
	free(data);
	free(src);
}

void drawModeSelectionView(Window* src) {
	if (src == NULL ) {
		return;
	}
	ModeSelectionView* data = (ModeSelectionView*) src->data;
	if(src->reDrawNeeded)
	{
		SDL_SetRenderDrawColor(data->windowRenderer, MODE_SELECTION_WINDOW_BGCOLOR_RED, MODE_SELECTION_WINDOW_BGCOLOR_GREEN, MODE_SELECTION_WINDOW_BGCOLOR_BLUE, MODE_SELECTION_WINDOW_BGCOLOR_ALPHA);
		SDL_RenderClear(data->windowRenderer);
	}
	for (int i = 0; i< MODE_SELECTION_WINDOW_MODES_AMOUNT; ++i) {
		src->reDrawNeeded |= data->modeButtons[i]->reDrawNeeded;
		data->modeButtons[i]->drawWindow(data->modeButtons[i]);
	}
	for (int i = 0; i < MODE_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		src->reDrawNeeded |= data->navigationButtons[i]->reDrawNeeded;
		data->navigationButtons[i]->drawWindow(data->navigationButtons[i]);
	}
	if(src->reDrawNeeded)
	{
		SDL_RenderPresent(data->windowRenderer);
	}
	src->reDrawNeeded = SDL_FALSE;
}

Command* handleEventModeSelectionView(Window* src, SDL_Event* event){
	if(src == NULL || event==NULL){
		return NULL;
	}
	Command* cmd;
	ModeSelectionView* data = (ModeSelectionView*) src->data;
	for (int i = 0; i< MODE_SELECTION_WINDOW_MODES_AMOUNT; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->modeButtons[i], event) == SDL_TRUE){
			data->modeButtons[i]->handleEventWindow(data->modeButtons[i],event);
			if(UpdateSelectedMode(data->selectedMode,i,data) == SDL_FALSE) {
				// exit the program properly TODO: CHECK!!!
				src->holdingWindow->holdingWindow->isClosed = SDL_TRUE;
				return NULL;
			}
			else {
				GameMode selectedMode = GetMode(data->selectedMode);
				cmd = CreateGameModeCommand(selectedMode);
				return cmd;
			}
		}
	}
	for (int i = 0; i < MODE_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->navigationButtons[i], event) == SDL_TRUE){
			cmd = data->navigationButtons[i]->handleEventWindow(data->navigationButtons[i],event);
			if(cmd->data != NOP_COMMAND_DATA) {
				return cmd;
			}
		}
	}
	cmd = CreateNOPCommand();
	return cmd;
}
Command* NextModeButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}

	Command* cmd = CreateNOPCommand();
	SimpleButton* data = (SimpleButton*) src->data;
	ModeSelectionView* modeSelectionView = (ModeSelectionView*) (src->holdingWindow->data);
	if(data->isEnabled == SDL_FALSE){
		return cmd;
	}
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		if(modeSelectionView->selectedMode == MODE_UNSELECTED) {
			return NULL;
		}

		enum WindowView nextView = DIFFICULTY_SELECTION_VIEW;
		if(modeSelectionView->selectedMode == MODE_SELECTION_WINDOW_TWO_PLAYERS_INDEX) {
			nextView = BOARD_VIEW;
		}

		setCurrentView(src->holdingWindow->holdingWindow, nextView);

		cmd = CreateGameModeCommand(modeSelectionView->selectedMode);
		return cmd;
	}
	return cmd;
}

Command* BackModeButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	Command* cmd = CreateNOPCommand();
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow, MAIN_VIEW);
	}
	return cmd;
}

Command* ModeButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	Command* cmd = CreateNOPCommand();
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
	}
	return cmd;
}


SDL_bool UpdateSelectedMode(int lastSelectedMode, int currentlySelectedMode, ModeSelectionView* view) {

	Window* selectedMode = (Window*) view->modeButtons[currentlySelectedMode];
	char* imagePath = GetModeImagePath(currentlySelectedMode, SDL_TRUE);
	// get image for selected Mode
	updateImage(selectedMode, imagePath);
	setEnabledSimpleButton(view->navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX], SDL_TRUE);
	if(lastSelectedMode != MODE_UNSELECTED)
	{
		imagePath = GetModeImagePath(lastSelectedMode, SDL_FALSE);
		Window* lastSelected = (Window*) view->modeButtons[lastSelectedMode];
		updateImage(lastSelected, imagePath);
		if(lastSelectedMode == currentlySelectedMode)
		{
			view->selectedMode = MODE_UNSELECTED;
			setEnabledSimpleButton(view->navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX], SDL_FALSE);
			return SDL_TRUE;
		}
	}
	view->selectedMode = currentlySelectedMode;

	return SDL_TRUE;
}

char* GetModeImagePath(int mode, SDL_bool isSelected) {
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
