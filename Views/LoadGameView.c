#include "LoadGameView.h"
#include <math.h>
#include <stdlib.h>
#include "SimpleButton.h"
#include "CommonGUIUtil.h"
#include "Window.h"
#include "MainWindow.h"
#include "FileSystemUtil.h"
#include "Commands.h"

Window** createSlotButtons(Window* holdingWindow, SDL_Renderer* renderer)
{
	if (holdingWindow == NULL) {
		return NULL ;
	}

	Window** slotButtons = calloc(LOAD_GAME_WINDOW_SLOTS_AMOUNT,sizeof(Window*));
	if (slotButtons == NULL ) {
		return NULL;
	}
	int availableSlots = getNumberOfSavedGames();
	LoadGameView* view = (LoadGameView*) (holdingWindow->data);
	if(availableSlots > LOAD_GAME_WINDOW_SLOTS_AMOUNT) {
		availableSlots = LOAD_GAME_WINDOW_SLOTS_AMOUNT;
	}
	if(availableSlots == 0) {
		return slotButtons;
	}
	view->slotsAmount = availableSlots;

	//for (int i = 0; i < LOAD_GAME_WINDOW_SLOTS_AMOUNT; ++i) {
	for (int i = 0; i < availableSlots; ++i) {
		SDL_Rect slotButtonR = {.x = 0, .y = LOAD_GAME_WINDOW_BUTTON_HEIGHT * i + LOAD_GAME_WINDOW_BUTTON_SPACING *i, .h = LOAD_GAME_WINDOW_BUTTON_HEIGHT, .w = LOAD_GAME_WINDOW_BUTTON_WIDTH};
		char* imagePath = GetSlotImagePath(i);
		if(imagePath != NULL){
			slotButtons[i] = (Window*) createSimpleButton(holdingWindow,renderer, &slotButtonR,imagePath ,SlotButtonHandler);
		}
		if (slotButtons[i] == NULL) {
			for (int i = 0; i < view->slotsAmount; ++i) {
					destroyWindow(slotButtons[i]); //NULL SAFE
			}
			free(slotButtons);
		}
		initWindow(slotButtons[i]);
	}
	return slotButtons;
}

Window** createLoadGameMenuButtons(Window* holdingWindow, SDL_Renderer* renderer){
	Window** menuButtons = calloc(LOAD_GAME_WINDOW_NAVIGATIONS_AMOUNT,sizeof(Window*));
	if (menuButtons == NULL ) {
		return NULL;
	}
	SDL_Rect loadR = { .x = 0, .y = LOAD_GAME_NAVIGTION_PANE_Y_POS, .h = LOAD_GAME_WINDOW_BUTTON_HEIGHT, .w = LOAD_GAME_WINDOW_BUTTON_WIDTH};
	SDL_Rect backR = { .x = LOAD_GAME_WINDOW_BUTTON_WIDTH + BOARD_WINDOW_BUTTON_SPACING , .y = LOAD_GAME_NAVIGTION_PANE_Y_POS, .h = LOAD_GAME_WINDOW_BUTTON_HEIGHT, .w = LOAD_GAME_WINDOW_BUTTON_WIDTH};
	menuButtons[LOAD_GAME_WINDOW_BACK_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &backR,LOAD_GAME_WINDOW_BACK_BUTTON_PIC_PATH ,BackLoadGameButtonHandler);
	initWindow(menuButtons[LOAD_GAME_WINDOW_BACK_BUTTON_INDEX]);
	menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &loadR, LOAD_GAME_WINDOW_LOAD_BUTTON_PIC_PATH, LoadSlotButtonHandler);
	initWindow(menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX]);

	setEnabledSimpleButton(menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX], SDL_FALSE);

	if (menuButtons[LOAD_GAME_WINDOW_BACK_BUTTON_INDEX] == NULL || menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX] == NULL ) {
		destroyWindow(menuButtons[LOAD_GAME_WINDOW_BACK_BUTTON_INDEX]); //NULL SAFE
		destroyWindow(menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX]); //NULL SAFE
		free(menuButtons);
		return NULL ;
	}

	return menuButtons;
}

Window* createLoadGameView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState) {
	Window* res = malloc(sizeof(Window));
	LoadGameView* data = malloc(sizeof(LoadGameView));
	data->gameState = gameState;
	data->gameSettings = gameSettings;
	res->data = (void*) data;
	MainWindow* main = (MainWindow*)holdingWindow->data;
	SDL_Rect slotsR = { .x = 0, .y = 0, .h = LOAD_GAME_WINDOW_HEIGHT, .w = LOAD_GAME_WINDOW_WIDTH};
	res->location = &slotsR;
	SDL_Renderer* renderer = main->windowRenderer;
	Window** slotsWidgets = createSlotButtons(res, renderer);
	Window** menuButtons = createLoadGameMenuButtons(res, renderer);
	if (res == NULL || data == NULL || holdingWindow == NULL || renderer == NULL
			|| slotsWidgets == NULL || menuButtons == NULL) {
		free(res);
		free(data);
		free(slotsWidgets);
		free(menuButtons);
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer); //NULL safe
		destroyWindow(holdingWindow); //NULL safe
		return NULL ;
	}
	data->slotButtons = slotsWidgets;
	data->windowRenderer = renderer;
	data->menuButtons = menuButtons;
	data->selectedSlot = SLOT_UNSELECTED;
	data->lastView = UNINITIALIZED_VIEW;
	res->destroyWindow = destroyLoadGameView;
	res->drawWindow = drawLoadGameView;
	res->handleEventWindow = handleEventLoadGameView;
	res->holdingWindow = holdingWindow;
	res->setInnerWidgetsReDraw = setLoadGameInnerReDraw;
	initWindow(res);
	return res;

}
void destroyLoadGameView(Window* src) {
	if (src == NULL ) {
		return;
	}
	LoadGameView* data = (LoadGameView*) src->data;
	for (int i = 0; i< data->slotsAmount; ++i) {
		destroyWindow(data->slotButtons[i]);
	}
	for (int i = 0; i < LOAD_GAME_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		destroyWindow(data->menuButtons[i]);
	}
	free(data->slotButtons);
	free(data->menuButtons);
	SDL_DestroyRenderer(data->windowRenderer);
	free(data);
	free(src);
}

void drawLoadGameView(Window* src) {
	if (src == NULL ) {
		return;
	}
	LoadGameView* data = (LoadGameView*) src->data;
	if(src->reDrawNeeded)
	{
		SDL_SetRenderDrawColor(data->windowRenderer, LOAD_GAME_WINDOW_BGCOLOR_RED, LOAD_GAME_WINDOW_BGCOLOR_GREEN, LOAD_GAME_WINDOW_BGCOLOR_BLUE, LOAD_GAME_WINDOW_BGCOLOR_ALPHA);
		SDL_RenderClear(data->windowRenderer);
	}
	for (int i = 0; i< data->slotsAmount; ++i) {
		src->reDrawNeeded |= data->slotButtons[i]->reDrawNeeded;
		data->slotButtons[i]->drawWindow(data->slotButtons[i]);
	}
	for (int i = 0; i < LOAD_GAME_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		src->reDrawNeeded |= data->menuButtons[i]->reDrawNeeded;
		data->menuButtons[i]->drawWindow(data->menuButtons[i]);
	}
	if(src->reDrawNeeded)
	{
		SDL_RenderPresent(data->windowRenderer);
	}
	src->reDrawNeeded = SDL_FALSE;
}

Command* handleEventLoadGameView(Window* src, SDL_Event* event){
	if(src == NULL || event==NULL){
		return NULL;
	}
	Command* cmd;
	LoadGameView* data = (LoadGameView*) src->data;
	for (int i = 0; i< data->slotsAmount; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->slotButtons[i], event) == SDL_TRUE){
			data->slotButtons[i]->handleEventWindow(data->slotButtons[i],event);
			if(GetUpdatedImagePathForSlot(data->selectedSlot,i,data) == SDL_FALSE) {
				// exit the program properly TODO: CHECK!!!
				src->holdingWindow->holdingWindow->isClosed = SDL_TRUE;
				return NULL;
			}
		}
	}
	for (int i = 0; i < LOAD_GAME_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->menuButtons[i], event) == SDL_TRUE){
			cmd = data->menuButtons[i]->handleEventWindow(data->menuButtons[i],event);
			if(cmd->data != NOP_COMMAND_DATA) {
				return cmd;
			}
		}
	}

	cmd = CreateNOPCommand();
	return cmd;
}
Command* LoadSlotButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}

	Command* cmd = CreateNOPCommand();
	SimpleButton* data = (SimpleButton*) src->data;
	if(data->isEnabled == SDL_FALSE)
	{
		return cmd;
	}
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		//load a game and set current view to board?
		cmd = CreateLoadCommand(SAVED_GAMES_DIRECTORY_PATH);
	}

	return cmd;
}

Command* BackLoadGameButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	LoadGameView* view = (LoadGameView*) (src->holdingWindow->data);
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow, view->lastView);//MODE_SELECTION_VIEW);
	}
	Command* cmd = CreateNOPCommand();
	return cmd;
}

Command* SlotButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
	}

	Command* cmd = CreateNOPCommand();
	return cmd;
}


SDL_bool GetUpdatedImagePathForSlot(int lastSelectedSlot, int currentlySelectedSlot, LoadGameView* view) {
	Window* selectedSlot = (Window*) view->slotButtons[currentlySelectedSlot];
	char* imageName = malloc(LOAD_GAME_WINDOW_SLOT__PIC_PATH_LENGTH);
	if(imageName == NULL)
	{
		return SDL_FALSE;
	}
	sprintf(imageName, LOAD_GAME_WINDOW_SLOT_BUTTON_PIC_PATH, currentlySelectedSlot,LOAD_GAME_WINDOW_PIC_PATH_SLOT_SELECTED);
	updateImage(selectedSlot, imageName);
	free(imageName);

	setEnabledSimpleButton(view->menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX], SDL_TRUE);

	if(lastSelectedSlot != SLOT_UNSELECTED)
	{
		imageName = malloc(DIFFICULTY_SELECTION_WINDOW_DIFF__PIC_PATH_LENGTH);
		if(imageName == NULL)
		{
			return SDL_FALSE;
		}
		Window* lastSelected = (Window*) view->slotButtons[lastSelectedSlot];
		sprintf(imageName, LOAD_GAME_WINDOW_SLOT_BUTTON_PIC_PATH, lastSelectedSlot,LOAD_GAME_WINDOW_PIC_PATH_SLOT_NOT_SELECTED);
		updateImage(lastSelected, imageName);
		free(imageName);
		if(lastSelectedSlot == currentlySelectedSlot)
		{
			view->selectedSlot = SLOT_UNSELECTED;
			setEnabledSimpleButton(view->menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX], SDL_FALSE);
			return SDL_TRUE;
		}
	}
	view->selectedSlot = currentlySelectedSlot;

	return SDL_TRUE;
}

char* GetSlotImagePath(int slot) {
	char* imageName = malloc(LOAD_GAME_WINDOW_SLOT__PIC_PATH_LENGTH);
	if(imageName == NULL)
	{
		return NULL;
	}
	sprintf(imageName, LOAD_GAME_WINDOW_SLOT_BUTTON_PIC_PATH, slot,LOAD_GAME_WINDOW_PIC_PATH_SLOT_NOT_SELECTED);
	return imageName;
}


void setLoadGameInnerReDraw(Window* src, SDL_bool reDraw) {
	if(src == NULL){
		return;
	}
	LoadGameView* data = (LoadGameView*) src->data;
	for (int i = 0; i< data->slotsAmount; ++i) {
		data->slotButtons[i]->reDrawNeeded = reDraw;
	}
	for (int i = 0; i < LOAD_GAME_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		data->menuButtons[i]->reDrawNeeded = reDraw;
	}
}
