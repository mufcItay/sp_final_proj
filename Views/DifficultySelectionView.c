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
		return NULL ;
	}
	// allocate memory
	Window** difficultyButtons = calloc(DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT,sizeof(Window*));
	if (difficultyButtons == NULL ) {
		return NULL;
	}
	// create the difficulty selection buttons
	for (int i = 0; i < DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT; ++i) {
		SDL_Rect difficultyButtonR = {.x = 0, .y = DIFFICULTY_SELECTION_WINDOW_BUTTON_HEIGHT * i + DIFFICULTY_SELECTION_WINDOW_BUTTON_SPACING *i, .h = DIFFICULTY_SELECTION_WINDOW_BUTTON_HEIGHT, .w = DIFFICULTY_SELECTION_WINDOW_BUTTON_WIDTH};
		char* imagePath = getDifficultyImagePath(i);
		if(imagePath != NULL){
			difficultyButtons[i] = (Window*) createSimpleButton(holdingWindow,renderer, &difficultyButtonR,imagePath ,difficultyButtonHandler);
		}
		// handle creation error
		if (difficultyButtons[i] == NULL) {
			for (int i = 0; i < DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT; ++i) {
					destroyWindow(difficultyButtons[i]); //NULL SAFE
			}
			free(difficultyButtons);
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
		destroyWindow(navigationButtons[DIFFICULTY_SELECTION_WINDOW_BACK_BUTTON_INDEX]); //NULL SAFE
		destroyWindow(navigationButtons[DIFFICULTY_SELECTION_WINDOW_NEXT_BUTTON_INDEX]); //NULL SAFE
		free(navigationButtons);
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
	if (res == NULL || data == NULL || holdingWindow == NULL || renderer == NULL
			|| difficultyWidgets == NULL || navigationButtons == NULL) {
		free(res);
		free(data);
		free(difficultyWidgets);
		free(navigationButtons);
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer); //NULL safe
		destroyWindow(holdingWindow); //NULL safe
		return NULL ;
	}
	// set members
	data->difficultyButtons = difficultyWidgets;
	data->windowRenderer = renderer;
	data->navigationButtons = navigationButtons;
	data->selectedDifficulty = gameSettings->difficulty;
	res->data = (void*) data;
	res->destroyWindow = destroyDifficultySelectionView;
	res->drawWindow = drawDifficultySelectionView;
	res->handleEventWindow = handleEventDifficultySelectionView;
	res->holdingWindow = holdingWindow;
	res->setInnerWidgetsReDraw = setDifficultySelectionInnerReDraw;
	initWindow(res);
	// update to default difficulty selection
	updateSelectedDifficulty(DIFFICULTY_UNSELECTED, gameSettings->difficulty,data);
	return res;

}
void destroyDifficultySelectionView(Window* src) {
	if (src == NULL ) {
		return;
	}
	DifficultySelectionView* data = (DifficultySelectionView*) src->data;
	for (int i = 0; i< DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT; ++i) {
		destroyWindow(data->difficultyButtons[i]);
	}
	for (int i = 0; i < DIFFICULTY_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		destroyWindow(data->navigationButtons[i]);
	}
	free(data->difficultyButtons);
	free(data->navigationButtons);
	SDL_DestroyRenderer(data->windowRenderer);
	free(data);
	free(src);
}

void drawDifficultySelectionView(Window* src) {
	if (src == NULL ) {
		return;
	}
	DifficultySelectionView* data = (DifficultySelectionView*) src->data;
	if(src->reDrawNeeded)
	{
		SDL_SetRenderDrawColor(data->windowRenderer, DIFFICULTY_SELECTION_WINDOW_BGCOLOR_RED, DIFFICULTY_SELECTION_WINDOW_BGCOLOR_GREEN, DIFFICULTY_SELECTION_WINDOW_BGCOLOR_BLUE, DIFFICULTY_SELECTION_WINDOW_BGCOLOR_ALPHA);
		SDL_RenderClear(data->windowRenderer);
	}
	for (int i = 0; i< DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT; ++i) {
		// draw difficulties
		src->reDrawNeeded |= data->difficultyButtons[i]->reDrawNeeded;
		data->difficultyButtons[i]->drawWindow(data->difficultyButtons[i]);
	}
	for (int i = 0; i < DIFFICULTY_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		// draw navigation buttons
		src->reDrawNeeded |= data->navigationButtons[i]->reDrawNeeded;
		data->navigationButtons[i]->drawWindow(data->navigationButtons[i]);
	}
	if(src->reDrawNeeded)
	{
		SDL_RenderPresent(data->windowRenderer);
	}
	src->reDrawNeeded = SDL_FALSE;
}

Command* handleEventDifficultySelectionView(Window* src, SDL_Event* event){
	if(src == NULL || event==NULL){
		return NULL;
	}
	Command* cmd = createNOPCommand();
	DifficultySelectionView* data = (DifficultySelectionView*) src->data;
	for (int i = 0; i< DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->difficultyButtons[i], event) == SDL_TRUE){
			// handle difficulty selection change
			data->difficultyButtons[i]->handleEventWindow(data->difficultyButtons[i],event);
			if(updateSelectedDifficulty(data->selectedDifficulty,i,data) == SDL_FALSE) {
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
		return NULL; //Better to return an error value
	}
	Command* cmd = createNOPCommand();

	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow, MODE_SELECTION_VIEW);
	}
	return cmd;
}

Command* difficultyButtonHandler(Window* src, SDL_Event* event){
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	Command* cmd = createNOPCommand();

	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
	}
	return cmd;
}


SDL_bool updateSelectedDifficulty(int lastSelectedDifficulty, int currentlySelectedDifficulty, DifficultySelectionView* view) {
	// get selected difficulty window
	Window* selectedDiff = (Window*) view->difficultyButtons[currentlySelectedDifficulty];
	char* imageName = malloc(DIFFICULTY_SELECTION_WINDOW_DIFF__PIC_PATH_LENGTH);
	if(imageName == NULL)
	{
		return SDL_FALSE;
	}
	// update image of selected difficulty
	sprintf(imageName, DIFFICULTY_SELECTION_WINDOW_DIFFICULTY_BUTTON_PIC_PATH, currentlySelectedDifficulty,DIFFICULTY_SELECTION_WINDOW_PIC_PATH_SLOT_SELECTED);
	updateImage(selectedDiff, imageName);
	free(imageName);

	// change enabled state to enabled cause some difficulty has been selected
	setEnabledSimpleButton(view->navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX], SDL_TRUE);
	if(lastSelectedDifficulty != DIFFICULTY_UNSELECTED)
	{
		// update image of last selected difficulty
		imageName = malloc(DIFFICULTY_SELECTION_WINDOW_DIFF__PIC_PATH_LENGTH);
		if(imageName == NULL)
		{
			return SDL_FALSE;
		}
		Window* lastSelected = (Window*) view->difficultyButtons[lastSelectedDifficulty];
		sprintf(imageName, DIFFICULTY_SELECTION_WINDOW_DIFFICULTY_BUTTON_PIC_PATH, lastSelectedDifficulty,DIFFICULTY_SELECTION_WINDOW_PIC_PATH_SLOT_NOT_SELECTED);
		updateImage(lastSelected, imageName);
		free(imageName);
		if(lastSelectedDifficulty == currentlySelectedDifficulty)
		{
			view->selectedDifficulty = DIFFICULTY_UNSELECTED;
			setEnabledSimpleButton(view->navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX], SDL_FALSE);
			return SDL_TRUE;
		}
	}
	view->selectedDifficulty = currentlySelectedDifficulty;

	return SDL_TRUE;
}

char* getDifficultyImagePath(int difficulty) {
	char* imageName = malloc(DIFFICULTY_SELECTION_WINDOW_DIFF__PIC_PATH_LENGTH);
	if(imageName == NULL)
	{
		return NULL;
	}
	sprintf(imageName, DIFFICULTY_SELECTION_WINDOW_DIFFICULTY_BUTTON_PIC_PATH, difficulty,DIFFICULTY_SELECTION_WINDOW_PIC_PATH_SLOT_NOT_SELECTED);
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
