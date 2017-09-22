#include "LoadGameView.h"
#include <math.h>
#include <stdlib.h>
#include "SimpleButton.h"
#include "CommonGUIUtil.h"
#include "Window.h"
#include "MainWindow.h"
#include "FileSystemUtil.h"
#include "Commands.h"
#include "InfoMessageBox.h"


Window** updateSlotButtons(Window* holdingWindow) {
	if (holdingWindow == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL ;
	}

	LoadGameView* data = (LoadGameView*) holdingWindow->data;
	if(data->slotButtons != NULL) {
		// free old slot buttons
		for (int i = 0; i< data->slotsAmount; ++i) {
			destroyWindow(data->slotButtons[i]);
		}
		free(data->slotButtons);
	}

	Window** ret = createSlotButtons(holdingWindow,data->windowRenderer);
	if(ret == NULL){
		return NULL;
	}
	data->selectedSlot = SLOT_UNSELECTED;
	data->slotButtons = ret;
	setEnabledSimpleButton(data->menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX],SDL_FALSE);
	return ret;
}

void destroyLoadSlotButtons(LoadGameView* view, Window** slotButtons) {
	for (int i = 0; i < view->slotsAmount; ++i) {
		destroyWindow(slotButtons[i]); //NULL SAFE
	}
	free(slotButtons);
}

Window** createSlotButtons(Window* holdingWindow, SDL_Renderer* renderer)
{
	if (holdingWindow == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL ;
	}
	LoadGameView* view = (LoadGameView*) (holdingWindow->data);
	// allocate memory
	Window** slotButtons = calloc(LOAD_GAME_WINDOW_SLOTS_AMOUNT,sizeof(Window*));
	if (slotButtons == NULL ) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	// get from file system the number of saved games
	int availableSlots = getNumberOfSavedGames();
	if(availableSlots == SLOTS_LOAD_ERROR) {
		view->slotsAmount = 0;
		showInfoMessageBox(INFO_MBOX_READ_DIR_ERROR_MESSAGE);
		return slotButtons;
	}
	if(availableSlots > LOAD_GAME_WINDOW_SLOTS_AMOUNT) {
		availableSlots = LOAD_GAME_WINDOW_SLOTS_AMOUNT;
	}
	view->slotsAmount = availableSlots;
	if(availableSlots == 0) {
		return slotButtons;
	}

	//crate the buttons of slots
	for (int i = 0; i < availableSlots; ++i) {
		SDL_Rect slotButtonR = {.x = 0, .y = LOAD_GAME_WINDOW_BUTTON_HEIGHT * i + LOAD_GAME_WINDOW_BUTTON_SPACING *i, .h = LOAD_GAME_WINDOW_BUTTON_HEIGHT, .w = LOAD_GAME_WINDOW_BUTTON_WIDTH};
		char* imagePath = getSlotImagePath(i);
		if(imagePath != NULL){
			slotButtons[i] = (Window*) createSimpleButton(holdingWindow,renderer, &slotButtonR,imagePath ,slotButtonHandler);
		}
		// if a creation error occurred clean exit
		if (slotButtons[i] == NULL) {
			destroyLoadSlotButtons(view, slotButtons);
			return NULL;
		}
		initWindow(slotButtons[i]);
	}
	return slotButtons;
}

void destroyLoadMenuButtons(Window** menuButtons) {
	destroyWindow(menuButtons[LOAD_GAME_WINDOW_BACK_BUTTON_INDEX]); //NULL SAFE
	destroyWindow(menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX]); //NULL SAFE
	free(menuButtons);
}

Window** createLoadGameMenuButtons(Window* holdingWindow, SDL_Renderer* renderer){
	Window** menuButtons = calloc(LOAD_GAME_WINDOW_NAVIGATIONS_AMOUNT,sizeof(Window*));
	if (menuButtons == NULL ) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	// create rectangles and buttons of navigation
	SDL_Rect loadR = { .x = 0, .y = LOAD_GAME_NAVIGTION_PANE_Y_POS, .h = LOAD_GAME_WINDOW_BUTTON_HEIGHT, .w = LOAD_GAME_WINDOW_BUTTON_WIDTH};
	SDL_Rect backR = { .x = LOAD_GAME_WINDOW_BUTTON_WIDTH + BOARD_WINDOW_BUTTON_SPACING , .y = LOAD_GAME_NAVIGTION_PANE_Y_POS, .h = LOAD_GAME_WINDOW_BUTTON_HEIGHT, .w = LOAD_GAME_WINDOW_BUTTON_WIDTH};
	menuButtons[LOAD_GAME_WINDOW_BACK_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &backR,LOAD_GAME_WINDOW_BACK_BUTTON_PIC_PATH ,backLoadGameButtonHandler);
	initWindow(menuButtons[LOAD_GAME_WINDOW_BACK_BUTTON_INDEX]);
	menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &loadR, LOAD_GAME_WINDOW_LOAD_BUTTON_PIC_PATH, loadSlotButtonHandler);
	initWindow(menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX]);

	setEnabledSimpleButton(menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX], SDL_FALSE);
	// handle creation error of buttons
	if (menuButtons[LOAD_GAME_WINDOW_BACK_BUTTON_INDEX] == NULL || menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX] == NULL ) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		destroyLoadMenuButtons(menuButtons);
		return NULL ;
	}

	return menuButtons;
}

Window* createLoadGameView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState) {
	// allocate memory
	Window* res = calloc(1, sizeof(Window));
	LoadGameView* data = calloc(1, sizeof(LoadGameView));
	data->gameState = gameState;
	data->gameSettings = gameSettings;
	res->data = (void*) data;
	MainWindow* main = (MainWindow*)holdingWindow->data;
	// create rectangle for board
	SDL_Rect slotsR = { .x = 0, .y = 0, .h = LOAD_GAME_WINDOW_HEIGHT, .w = LOAD_GAME_WINDOW_WIDTH};
	res->location = &slotsR;
	SDL_Renderer* renderer = main->windowRenderer;
	Window** slotsWidgets = createSlotButtons(res, renderer);
	Window** menuButtons = createLoadGameMenuButtons(res, renderer);
	if (res == NULL || data == NULL || holdingWindow == NULL || renderer == NULL
			|| slotsWidgets == NULL || menuButtons == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		destroyLoadGameView(res);
		return NULL ;
	}
	res->destroyWindow = destroyLoadGameView;
	// set data members
	data->slotButtons = slotsWidgets;
	data->windowRenderer = renderer;
	data->menuButtons = menuButtons;
	data->selectedSlot = SLOT_UNSELECTED;
	data->lastView = UNINITIALIZED_VIEW;
	// hand error in button allocation
	res->drawWindow = drawLoadGameView;
	res->handleEventWindow = handleEventLoadGameView;
	res->holdingWindow = holdingWindow;
	res->setInnerWidgetsReDraw = setLoadGameInnerReDraw;
	initWindow(res);
	return res;
}

void destroyLoadGameView(Window* src) {
	if (src == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return;
	}
	LoadGameView* data = (LoadGameView*) src->data;
	if(data->menuButtons != NULL) {
		destroyLoadMenuButtons(data->menuButtons);
	}
	if(data->slotButtons != NULL) {
		destroyLoadSlotButtons(data,data->slotButtons);
	}
	SDL_DestroyRenderer(data->windowRenderer);
	free(data);
	free(src);
}

ErrorCode drawLoadGameView(Window* src) {
	if (src == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}
	ErrorCode err = OK;
	LoadGameView* data = (LoadGameView*) src->data;
	if(src->reDrawNeeded)
	{
		err |= SDL_SetRenderDrawColor(data->windowRenderer, LOAD_GAME_WINDOW_BGCOLOR_RED, LOAD_GAME_WINDOW_BGCOLOR_GREEN, LOAD_GAME_WINDOW_BGCOLOR_BLUE, LOAD_GAME_WINDOW_BGCOLOR_ALPHA);
		err |= SDL_RenderClear(data->windowRenderer);
		if(err != OK) {
			err = SDL_ERROR;
			return err;
		}
	}
	for (int i = 0; i< data->slotsAmount; ++i) {
		// draw slots
		src->reDrawNeeded |= data->slotButtons[i]->reDrawNeeded;
		err |= data->slotButtons[i]->drawWindow(data->slotButtons[i]);
		if(err != OK) {
			err = SDL_ERROR;
			return err;
		}
	}
	for (int i = 0; i < LOAD_GAME_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		// draw menu buttons
		src->reDrawNeeded |= data->menuButtons[i]->reDrawNeeded;
		err |= data->menuButtons[i]->drawWindow(data->menuButtons[i]);
		if(err != OK) {
			err = SDL_ERROR;
			return err;
		}
	}
	if(src->reDrawNeeded)
	{
		SDL_RenderPresent(data->windowRenderer);
	}
	src->reDrawNeeded = SDL_FALSE;
	return err;
}

Command* handleEventLoadGameView(Window* src, SDL_Event* event){
	if(src == NULL || event==NULL){
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd;
	LoadGameView* data = (LoadGameView*) src->data;
	for (int i = 0; i< data->slotsAmount; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->slotButtons[i], event) == SDL_TRUE){
			// hnadle slot button events
			cmd = data->slotButtons[i]->handleEventWindow(data->slotButtons[i],event);
			if(cmd == NULL) {
				return NULL;
			}
			if(getUpdatedImagePathForSlot(data->selectedSlot,i,data) != OK) {
				return NULL;
			}
		}
	}
	for (int i = 0; i < LOAD_GAME_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->menuButtons[i], event) == SDL_TRUE){
			// handle menu button events
			cmd = data->menuButtons[i]->handleEventWindow(data->menuButtons[i],event);
			if(cmd->data != NOP_COMMAND_DATA) {
				return cmd;
			}
		}
	}
	cmd = createNOPCommand();
	return cmd;
}
Command* loadSlotButtonHandler(Window* src, SDL_Event* event){
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
		LoadGameView* loadGameViewData = (LoadGameView*) src->holdingWindow->data;
		int pathLen = strlen(SAVED_GAMES_DIRECTORY_PATH) + sizeof(char) + strlen(XML_FILE_TYPE) + 1;
		char* path = (char*) malloc(pathLen * sizeof(char));
		if(path == NULL) {
			printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
			return NULL;
		}
		if(sprintf(path,SLOT_PATH_FORMAT,SAVED_GAMES_DIRECTORY_PATH, loadGameViewData->selectedSlot + 1,XML_FILE_TYPE) <= 0) {
			printErrorMessage(STRING_ERROR_MESSAGE);
			return NULL;
		}
		cmd = createLoadCommand(path);
		setCurrentView(src->holdingWindow->holdingWindow, BOARD_VIEW);
	}
	return cmd;
}

Command* backLoadGameButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	LoadGameView* view = (LoadGameView*) (src->holdingWindow->data);
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow, view->lastView);//MODE_SELECTION_VIEW);
	}
	Command* cmd = createNOPCommand();
	return cmd;
}

Command* slotButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
	}
	Command* cmd = createNOPCommand();
	return cmd;
}


ErrorCode getUpdatedImagePathForSlot(int lastSelectedSlot, int currentlySelectedSlot, LoadGameView* view) {
	// get selected slot window
	Window* selectedSlot = (Window*) view->slotButtons[currentlySelectedSlot];
	char* imageName = malloc(LOAD_GAME_WINDOW_SLOT__PIC_PATH_LENGTH);
	if(imageName == NULL)
	{
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return SDL_FALSE;
	}
	// update image
	if(sprintf(imageName, LOAD_GAME_WINDOW_SLOT_BUTTON_PIC_PATH, currentlySelectedSlot,LOAD_GAME_WINDOW_PIC_PATH_SLOT_SELECTED) <= 0) {
		printErrorMessage(STRING_ERROR_MESSAGE);
		return SDL_FALSE;
	}
	ErrorCode err = updateImage(selectedSlot, imageName);
	if(err != OK) {
		return err;
	}
	free(imageName);

	setEnabledSimpleButton(view->menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX], SDL_TRUE);
	if(lastSelectedSlot != SLOT_UNSELECTED)
	{
		// handle last selected slot updates
		imageName = malloc(DIFFICULTY_SELECTION_WINDOW_DIFF__PIC_PATH_LENGTH);
		if(imageName == NULL)
		{
			printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
			return SDL_FALSE;
		}
		Window* lastSelected = (Window*) view->slotButtons[lastSelectedSlot];
		// udpate image of last selected slot
		if(sprintf(imageName, LOAD_GAME_WINDOW_SLOT_BUTTON_PIC_PATH, lastSelectedSlot,LOAD_GAME_WINDOW_PIC_PATH_SLOT_NOT_SELECTED) <= 0) {
			printErrorMessage(STRING_ERROR_MESSAGE);
			return SDL_FALSE;
		}
		ErrorCode err = updateImage(lastSelected, imageName);
		if(err != OK) {
			return err;
		}
		free(imageName);
		if(lastSelectedSlot == currentlySelectedSlot)
		{
			view->selectedSlot = SLOT_UNSELECTED;
			setEnabledSimpleButton(view->menuButtons[LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX], SDL_FALSE);
			return OK;
		}
	}
	view->selectedSlot = currentlySelectedSlot;

	return OK;
}

char* getSlotImagePath(int slot) {
	char* imageName = malloc(LOAD_GAME_WINDOW_SLOT__PIC_PATH_LENGTH);
	if(imageName == NULL)
	{
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	if (sprintf(imageName, LOAD_GAME_WINDOW_SLOT_BUTTON_PIC_PATH, slot,LOAD_GAME_WINDOW_PIC_PATH_SLOT_NOT_SELECTED) <= 0 ) {
		printErrorMessage(STRING_ERROR_MESSAGE);
		return NULL;
	}
	return imageName;
}


void setLoadGameInnerReDraw(Window* src, SDL_bool reDraw) {
	if(src == NULL){
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
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
