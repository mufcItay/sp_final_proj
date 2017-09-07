#include "ColorSelectionView.h"

#include <stdlib.h>
#include "SimpleButton.h"
#include "CommonGUIUtil.h"
#include "Window.h"
#include "MainWindow.h"
#include "CommonStructures.h"
#include "Commands.h"

Window** createColorButtons(Window* holdingWindow, SDL_Renderer* renderer)
{
	if (holdingWindow == NULL) {
		return NULL ;
	}
	Window** colorButtons = calloc(COLOR_SELECTION_WINDOW_COLORS_AMOUNT,sizeof(Window*));
	if (colorButtons == NULL ) {
		return NULL;
	}
	for (int i = 0; i < COLOR_SELECTION_WINDOW_COLORS_AMOUNT; ++i) {
		SDL_Rect difficultyButtonR = {.x = 0, .y = COLOR_SELECTION_WINDOW_BUTTON_HEIGHT * i + COLOR_SELECTION_WINDOW_BUTTON_SPACING *i, .h = COLOR_SELECTION_WINDOW_BUTTON_HEIGHT, .w = COLOR_SELECTION_WINDOW_BUTTON_WIDTH};
		char* imagePath = getColorImagePath(i, SDL_FALSE);
		if(imagePath != NULL){
			colorButtons[i] = (Window*) createSimpleButton(holdingWindow,renderer, &difficultyButtonR,imagePath ,colorButtonHandler);
		}
		if (colorButtons[i] == NULL) {
			for (int i = 0; i < COLOR_SELECTION_WINDOW_COLORS_AMOUNT; ++i) {
					destroyWindow(colorButtons[i]); //NULL SAFE
			}
			free(colorButtons);
		}
		initWindow(colorButtons[i]);
	}
	return colorButtons;
}

Window** createColorNavigationButtons(Window* holdingWindow, SDL_Renderer* renderer){
	Window** navigationButtons = calloc(COLOR_SELECTION_WINDOW_NAVIGATIONS_AMOUNT,sizeof(Window*));
	if (navigationButtons == NULL ) {
		return NULL;
	}
	SDL_Rect startR = { .x = 0, .y = COLOR_SELECTION_NAVIGTION_PANE_Y_POS, .h = COLOR_SELECTION_WINDOW_BUTTON_HEIGHT, .w = COLOR_SELECTION_WINDOW_BUTTON_WIDTH};
	SDL_Rect backR = { .x = COLOR_SELECTION_WINDOW_BUTTON_WIDTH + BOARD_WINDOW_BUTTON_SPACING , .y = COLOR_SELECTION_NAVIGTION_PANE_Y_POS, .h = COLOR_SELECTION_WINDOW_BUTTON_HEIGHT, .w = COLOR_SELECTION_WINDOW_BUTTON_WIDTH};
	navigationButtons[COLOR_SELECTION_WINDOW_BACK_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &backR,COLOR_SELECTION_WINDOW_BACK_BUTTON_PIC_PATH ,backColorButtonHandler);
	initWindow(navigationButtons[COLOR_SELECTION_WINDOW_BACK_BUTTON_INDEX]);
	navigationButtons[COLOR_SELECTION_WINDOW_START_BUTTON_INDEX] = createSimpleButton(holdingWindow,renderer, &startR, COLOR_SELECTION_WINDOW_START_BUTTON_PIC_PATH, startButtonHandler);
	initWindow(navigationButtons[COLOR_SELECTION_WINDOW_START_BUTTON_INDEX]);

	if (navigationButtons[COLOR_SELECTION_WINDOW_BACK_BUTTON_INDEX] == NULL || navigationButtons[COLOR_SELECTION_WINDOW_START_BUTTON_INDEX] == NULL ) {
		destroyWindow(navigationButtons[COLOR_SELECTION_WINDOW_BACK_BUTTON_INDEX]); //NULL SAFE
		destroyWindow(navigationButtons[COLOR_SELECTION_WINDOW_START_BUTTON_INDEX]); //NULL SAFE
		free(navigationButtons);
		return NULL ;
	}

	return navigationButtons;
}

Window* createColorSelectionView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState) {
	Window* res = malloc(sizeof(Window));
	ColorSelectionView* data = malloc(sizeof(ColorSelectionView));
	data->gameState = gameState;
	data->gameSettings = gameSettings;
	MainWindow* main = (MainWindow*)holdingWindow->data;
	SDL_Rect difficultiesR = { .x = 0, .y = 0, .h = COLOR_SELECTION_WINDOW_HEIGHT, .w = COLOR_SELECTION_WINDOW_WIDTH};
	res->location = &difficultiesR;
	SDL_Renderer* renderer = main->windowRenderer;
	Window** difficultyWidgets = createColorButtons(res, renderer);
	Window** navigationButtons = createColorNavigationButtons(res, renderer);
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
	data->colorButtons = difficultyWidgets;
	data->windowRenderer = renderer;
	data->navigationButtons = navigationButtons;
	data->selectedColor = gameSettings->color;
	res->data = (void*) data;
	res->destroyWindow = destroyColorSelectionView;
	res->drawWindow = drawColorSelectionView;
	res->handleEventWindow = handleEventColorSelectionView;
	res->holdingWindow = holdingWindow;
	res->setInnerWidgetsReDraw = setColorSelectionInnerReDraw;
	initWindow(res);
	updateSelectedColor(COLOR_UNSELECTED, gameSettings->color,data);
	return res;

}
void destroyColorSelectionView(Window* src) {
	if (src == NULL ) {
		return;
	}
	ColorSelectionView* data = (ColorSelectionView*) src->data;
	for (int i = 0; i< COLOR_SELECTION_WINDOW_COLORS_AMOUNT; ++i) {
		destroyWindow(data->colorButtons[i]);
	}
	for (int i = 0; i < COLOR_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		destroyWindow(data->navigationButtons[i]);
	}
	free(data->colorButtons);
	free(data->navigationButtons);
	SDL_DestroyRenderer(data->windowRenderer);
	free(data);
	free(src);
}

void drawColorSelectionView(Window* src) {
	if (src == NULL ) {
		return;
	}
	ColorSelectionView* data = (ColorSelectionView*) src->data;
	if(src->reDrawNeeded)
	{
		SDL_SetRenderDrawColor(data->windowRenderer, COLOR_SELECTION_WINDOW_BGCOLOR_RED, COLOR_SELECTION_WINDOW_BGCOLOR_GREEN, COLOR_SELECTION_WINDOW_BGCOLOR_BLUE, COLOR_SELECTION_WINDOW_BGCOLOR_ALPHA);
		SDL_RenderClear(data->windowRenderer);
	}
	for (int i = 0; i< COLOR_SELECTION_WINDOW_COLORS_AMOUNT; ++i) {
		src->reDrawNeeded |= data->colorButtons[i]->reDrawNeeded;
		data->colorButtons[i]->drawWindow(data->colorButtons[i]);
	}
	for (int i = 0; i < COLOR_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		src->reDrawNeeded |= data->navigationButtons[i]->reDrawNeeded;
		data->navigationButtons[i]->drawWindow(data->navigationButtons[i]);
	}
	if(src->reDrawNeeded)
	{
		SDL_RenderPresent(data->windowRenderer);
	}
	src->reDrawNeeded = SDL_FALSE;
}

Command* handleEventColorSelectionView(Window* src, SDL_Event* event){
	if(src == NULL || event==NULL){
		return NULL;
	}
	Command* cmd;
	ColorSelectionView* data = (ColorSelectionView*) src->data;
	for (int i = 0; i< COLOR_SELECTION_WINDOW_COLORS_AMOUNT; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->colorButtons[i], event) == SDL_TRUE){
			data->colorButtons[i]->handleEventWindow(data->colorButtons[i],event);
			if(updateSelectedColor(data->selectedColor,i,data) == SDL_FALSE) {
				// exit the program properly TODO: CHECK!!!
				src->holdingWindow->holdingWindow->isClosed = SDL_TRUE;
				return NULL;
			}
			else {
				UserColor selectedColor = getColor(data->selectedColor);
				cmd = createUserColorCommand(selectedColor);
				return cmd;
			}
		}
	}
	for (int i = 0; i < COLOR_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		if(event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->navigationButtons[i], event) == SDL_TRUE){
			cmd = data->navigationButtons[i]->handleEventWindow(data->navigationButtons[i],event);
			if(cmd->data != NOP_COMMAND_DATA) {
				return cmd;
			}
		}
	}

	cmd = createNOPCommand();
	return cmd;
}
Command* startButtonHandler(Window* src, SDL_Event* event){
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
		setCurrentView(src->holdingWindow->holdingWindow, BOARD_VIEW);

		cmd = createStartCommand();
	}

	return cmd;
}

Command* backColorButtonHandler(Window* src, SDL_Event* event){
	Command* cmd = createNOPCommand();

	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow, DIFFICULTY_SELECTION_VIEW);
	}

	return cmd;
}

Command* colorButtonHandler(Window* src, SDL_Event* event){
	Command* cmd = createNOPCommand();
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
	}
	return cmd;
}


SDL_bool updateSelectedColor(int lastSelectedColor, int currentlySelectedColor, ColorSelectionView* view) {

	Window* selectedColor = (Window*) view->colorButtons[currentlySelectedColor];
	char* imagePath = getColorImagePath(currentlySelectedColor, SDL_TRUE);
	// get image for selected Color
	updateImage(selectedColor, imagePath);

	if(lastSelectedColor != COLOR_UNSELECTED)
	{
		imagePath = getColorImagePath(lastSelectedColor, SDL_FALSE);
		Window* lastSelected = (Window*) view->colorButtons[lastSelectedColor];
		updateImage(lastSelected, imagePath);
		if(lastSelectedColor == currentlySelectedColor)
		{
			view->selectedColor = COLOR_UNSELECTED;
			setEnabledSimpleButton(view->navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX], SDL_FALSE);
			return SDL_TRUE;
		}
	}
	view->selectedColor = currentlySelectedColor;

	return SDL_TRUE;
}

char* getColorImagePath(int difficulty, SDL_bool isSelected) {
	if(difficulty == COLOR_SELECTION_WINDOW_BLACK_BUTTON_INDEX) {
		if(isSelected == SDL_TRUE){
			return COLOR_SELECTION_WINDOW_BLACK_BUTTON_SELECTED_PIC_PATH;
		}
		return COLOR_SELECTION_WINDOW_BLACK_BUTTON_NOT_SELECTED_PIC_PATH;
	}
	if(isSelected == SDL_TRUE){
		return COLOR_SELECTION_WINDOW_WHITE_BUTTON_SELECTED_PIC_PATH;
	}
	return COLOR_SELECTION_WINDOW_WHITE_BUTTON_NOT_SELECTED_PIC_PATH;
}


void setColorSelectionInnerReDraw(Window* src, SDL_bool reDraw) {
	if(src == NULL){
		return;
	}
	ColorSelectionView* data = (ColorSelectionView*) src->data;
	for (int i = 0; i< COLOR_SELECTION_WINDOW_COLORS_AMOUNT; ++i) {
		data->colorButtons[i]->reDrawNeeded = reDraw;
	}
	for (int i = 0; i < COLOR_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		data->navigationButtons[i]->reDrawNeeded = reDraw;
	}
}
