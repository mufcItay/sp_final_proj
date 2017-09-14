#include "DifficultySelectionView.h"

#include <stdlib.h>
#include "SimpleButton.h"
#include "CommonGUIUtil.h"
#include "Window.h"
#include "MainWindow.h"
#include "CommonStructures.h"
#include "Commands.h"

Window** createDifficultyButtons(Window* holdingWindow, SDL_Renderer* renderer)
{
	if (holdingWindow == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL ;
	}
	// allocate memory
	Window** difficultyButtons = calloc(DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT,sizeof(Window*));
	if (difficultyButtons == NULL ) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	// create the difficulty selection buttons
	for (int i = 0; i < DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT; ++i) {
		SDL_Rect difficultyButtonR = {.x = 0, .y = DIFFICULTY_SELECTION_WINDOW_BUTTON_HEIGHT * i + DIFFICULTY_SELECTION_WINDOW_BUTTON_SPACING *i, .h = DIFFICULTY_SELECTION_WINDOW_BUTTON_HEIGHT, .w = DIFFICULTY_SELECTION_WINDOW_BUTTON_WIDTH};
		char* imagePath = getDifficultyImagePath(i);
		if(imagePath == NULL){
			return NULL;
		}
		difficultyButtons[i] = (Window*) createSimpleButton(holdingWindow,renderer, &difficultyButtonR,imagePath ,difficultyButtonHandler);
		// handle creation error
		if (difficultyButtons[i] == NULL) {
			destroyDifficultyButtons(holdingWindow->data);
			return NULL;
		}
		initWindow(difficultyButtons[i]);
	}
	return difficultyButtons;
}

Window** createDifficultyNavigationButtons(Window* holdingWindow, SDL_Renderer* renderer){
	// allocate memory
	Window** navigationButtons = calloc(DIFFICULTY_SELECTION_WINDOW_NAVIGATIONS_AMOUNT,sizeof(Window*));
	if (navigationButtons == NULL ) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	// create rectangles and buttons for difficulty selection
	SDL_Rect nextR = { .x = 0, .y = DIFFICULTY_SELECTION_NAVIGTION_PANE_Y_POS, .h = DIFFICULTY_SELECTION_WINDOW_BUTTON_HEIGHT, .w = DIFFICULTY_SELECTION_WINDOW_BUTTON_WIDTH};
	SDL_Rect backR = { .x = DIFFICULTY_SELECTION_WINDOW_BUTTON_WIDTH + BOARD_WINDOW_BUTTON_SPACING , .y = DIFFICULTY_SELECTION_NAVIGTION_PANE_Y_POS, .h = DIFFICULTY_SELECTION_WINDOW_BUTTON_HEIGHT, .w = DIFFICULTY_SELECTION_WINDOW_BUTTON_WIDTH};
	navigationButtons[DIFFICULTY_SELECTION_WINDOW_BACK_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &backR,DIFFICULTY_SELECTION_WINDOW_BACK_BUTTON_PIC_PATH ,backDifficultiesButtonHandler);
	initWindow(navigationButtons[DIFFICULTY_SELECTION_WINDOW_BACK_BUTTON_INDEX]);
	navigationButtons[DIFFICULTY_SELECTION_WINDOW_NEXT_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &nextR, DIFFICULTY_SELECTION_WINDOW_NEXT_BUTTON_PIC_PATH, nextDifficultiesButtonHandler);
	initWindow(navigationButtons[DIFFICULTY_SELECTION_WINDOW_NEXT_BUTTON_INDEX]);
	// handle buttons creation error
	if (navigationButtons[DIFFICULTY_SELECTION_WINDOW_BACK_BUTTON_INDEX] == NULL || navigationButtons[DIFFICULTY_SELECTION_WINDOW_NEXT_BUTTON_INDEX] == NULL ) {
		destroyNavigationDifficultyButtons(holdingWindow->data);
		return NULL ;
	}

	return navigationButtons;
}

Window* createDifficultySelectionView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState) {
	// allocate memory
	Window* res = malloc(sizeof(Window));
	DifficultySelectionView* data = malloc(sizeof(DifficultySelectionView));
	data->gameState = gameState;
	data->gameSettings = gameSettings;
	MainWindow* main = (MainWindow*)holdingWindow->data;
	// create view rectangle for drawing it
	SDL_Rect difficultiesR = { .x = 0, .y = 0, .h = DIFFICULTY_SELECTION_WINDOW_HEIGHT, .w = DIFFICULTY_SELECTION_WINDOW_WIDTH};
	res->location = &difficultiesR;
	SDL_Renderer* renderer = main->windowRenderer;
	// create view's buttons
	Window** difficultyWidgets = createDifficultyButtons(res, renderer);
	Window** navigationButtons = createDifficultyNavigationButtons(res, renderer);
	// handle creation error
	// set members
	data->difficultyButtons = difficultyWidgets;
	data->windowRenderer = renderer;
	data->navigationButtons = navigationButtons;
	// selected difficulty is zero based
	data->selectedDifficulty = gameSettings->difficulty - 1;
	res->data = (void*) data;
	if (res == NULL || data == NULL || holdingWindow == NULL || renderer == NULL
			|| difficultyWidgets == NULL || navigationButtons == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		destroyDifficultySelectionView(res);
		return NULL ;
	}
	res->destroyWindow = destroyDifficultySelectionView;
	res->drawWindow = drawDifficultySelectionView;
	res->handleEventWindow = handleEventDifficultySelectionView;
	res->holdingWindow = holdingWindow;
	res->setInnerWidgetsReDraw = setDifficultySelectionInnerReDraw;
	initWindow(res);
	// update to default difficulty selection
	if(updateSelectedDifficulty(DIFFICULTY_UNSELECTED, data->selectedDifficulty,data) != OK) {
		return NULL;
	}
	return res;

}

void destroyDifficultyButtons(DifficultySelectionView* data) {
	for (int i = 0; i < DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT; ++i) {
		destroyWindow(data->difficultyButtons[i]);
	}
	free(data->difficultyButtons);
}

void destroyNavigationDifficultyButtons(DifficultySelectionView* data) {
	for (int i = 0; i < DIFFICULTY_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		destroyWindow(data->navigationButtons[i]);
	}
	free(data->navigationButtons);
}

void destroyDifficultySelectionView(Window* src) {
	if (src == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return;
	}
	DifficultySelectionView* data = (DifficultySelectionView*) src->data;
	destroyDifficultyButtons(data);
	destroyNavigationDifficultyButtons(data);
	SDL_DestroyRenderer(data->windowRenderer);
	free(data);
	free(src);
}

ErrorCode drawDifficultySelectionView(Window* src) {
	if (src == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}
	ErrorCode err = OK;
	DifficultySelectionView* data = (DifficultySelectionView*) src->data;
	if(src->reDrawNeeded)
	{
		err |= SDL_SetRenderDrawColor(data->windowRenderer, DIFFICULTY_SELECTION_WINDOW_BGCOLOR_RED, DIFFICULTY_SELECTION_WINDOW_BGCOLOR_GREEN, DIFFICULTY_SELECTION_WINDOW_BGCOLOR_BLUE, DIFFICULTY_SELECTION_WINDOW_BGCOLOR_ALPHA);
		err |= SDL_RenderClear(data->windowRenderer);
		if(err != OK) {
			err = SDL_ERROR;
			return err;
		}
	}
	for (int i = 0; i< DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT; ++i) {
		// draw difficulties
		src->reDrawNeeded |= data->difficultyButtons[i]->reDrawNeeded;
		err |= data->difficultyButtons[i]->drawWindow(data->difficultyButtons[i]);
		if(err != OK) {
			err = SDL_ERROR;
			return err;
		}
	}
	for (int i = 0; i < DIFFICULTY_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		// draw navigation buttons
		src->reDrawNeeded |= data->navigationButtons[i]->reDrawNeeded;
		err |= data->navigationButtons[i]->drawWindow(data->navigationButtons[i]);
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

Command* handleEventDifficultySelectionView(Window* src, SDL_Event* event){
	if(src == NULL || event==NULL){
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd = createNOPCommand();
	DifficultySelectionView* data = (DifficultySelectionView*) src->data;
	for (int i = 0; i< DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->difficultyButtons[i], event) == SDL_TRUE){
			// handle difficulty selection change
			data->difficultyButtons[i]->handleEventWindow(data->difficultyButtons[i],event);
			if(updateSelectedDifficulty(data->selectedDifficulty,i,data) != OK) {
				// exit the program properly TODO: CHECK!!!
				src->holdingWindow->holdingWindow->isClosed = SDL_TRUE;
				return NULL;
			}
			else {
				// handle error in updating selected difficulty
				DifficultyLevel selectedDifficulty = getColor(data->selectedDifficulty);
				cmd = createDifficultyCommand(selectedDifficulty);
				return cmd;
			}
		}
	}
	for (int i = 0; i < DIFFICULTY_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->navigationButtons[i], event) == SDL_TRUE){
			// handle navigation buttons event
			data->navigationButtons[i]->handleEventWindow(data->navigationButtons[i],event);
		}
	}
	return cmd;
}
Command* nextDifficultiesButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL; //Better to return an error value
	}
	Command* cmd = createNOPCommand();
	SimpleButton* data = (SimpleButton*) src->data;
	if(data->isEnabled == SDL_FALSE)
	{
		return cmd;
	}
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow, COLOR_SELECTION_VIEW);
	}
	return cmd;
}

Command* backDifficultiesButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd = createNOPCommand();

	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow, MODE_SELECTION_VIEW);
	}
	return cmd;
}

Command* difficultyButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd = createNOPCommand();

	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
	}
	return cmd;
}


ErrorCode updateSelectedDifficulty(int lastSelectedDifficulty, int currentlySelectedDifficulty, DifficultySelectionView* view) {
	// get selected difficulty window
	Window* selectedDiff = (Window*) view->difficultyButtons[currentlySelectedDifficulty];
	char* imageName = malloc(DIFFICULTY_SELECTION_WINDOW_DIFF__PIC_PATH_LENGTH);
	if(imageName == NULL)
	{
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return SDL_FALSE;
	}
	// update image of selected difficulty
	if(sprintf(imageName, DIFFICULTY_SELECTION_WINDOW_DIFFICULTY_BUTTON_PIC_PATH, currentlySelectedDifficulty,DIFFICULTY_SELECTION_WINDOW_PIC_PATH_SLOT_SELECTED) <= 0) {
		printErrorMessage(STRING_ERROR_MESSAGE);
		return SDL_FALSE;
	}
	ErrorCode err =updateImage(selectedDiff, imageName);
	if(err != OK) {
		return err;
	}
	free(imageName);

	// change enabled state to enabled cause some difficulty has been selected
	setEnabledSimpleButton(view->navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX], SDL_TRUE);
	if(lastSelectedDifficulty != DIFFICULTY_UNSELECTED)
	{
		// update image of last selected difficulty
		imageName = malloc(DIFFICULTY_SELECTION_WINDOW_DIFF__PIC_PATH_LENGTH);
		if(imageName == NULL)
		{
			printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
			return MEMORY_ERROR;
		}
		Window* lastSelected = (Window*) view->difficultyButtons[lastSelectedDifficulty];
		if(sprintf(imageName, DIFFICULTY_SELECTION_WINDOW_DIFFICULTY_BUTTON_PIC_PATH, lastSelectedDifficulty,DIFFICULTY_SELECTION_WINDOW_PIC_PATH_SLOT_NOT_SELECTED) <=0) {
			printErrorMessage(STRING_ERROR_MESSAGE);
			return GENERAL_ERROR;
		}
		ErrorCode err = updateImage(lastSelected, imageName);
		if(err != OK) {
			return err;
		}
		free(imageName);
		if(lastSelectedDifficulty == currentlySelectedDifficulty)
		{
			view->selectedDifficulty = DIFFICULTY_UNSELECTED;
			setEnabledSimpleButton(view->navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX], SDL_FALSE);
			return OK;
		}
	}
	view->selectedDifficulty = currentlySelectedDifficulty;

	return OK;
}

char* getDifficultyImagePath(int difficulty) {
	char* imageName = malloc(DIFFICULTY_SELECTION_WINDOW_DIFF__PIC_PATH_LENGTH);
	if(imageName == NULL)
	{
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	if(sprintf(imageName, DIFFICULTY_SELECTION_WINDOW_DIFFICULTY_BUTTON_PIC_PATH, difficulty,DIFFICULTY_SELECTION_WINDOW_PIC_PATH_SLOT_NOT_SELECTED) <= 0) {
		printErrorMessage(STRING_ERROR_MESSAGE);
		return NULL;
	}
	return imageName;
}


void setDifficultySelectionInnerReDraw(Window* src, SDL_bool reDraw) {
	if(src == NULL){
		return;
	}
	DifficultySelectionView* data = (DifficultySelectionView*) src->data;
	for (int i = 0; i< DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT; ++i) {
		data->difficultyButtons[i]->reDrawNeeded = reDraw;
	}
	for (int i = 0; i < DIFFICULTY_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		data->navigationButtons[i]->reDrawNeeded = reDraw;
	}
}
