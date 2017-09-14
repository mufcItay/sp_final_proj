#include "ColorSelectionView.h"
#include <stdlib.h>
#include "SimpleButton.h"
#include "CommonGUIUtil.h"
#include "Window.h"
#include "MainWindow.h"
#include "CommonStructures.h"
#include "Commands.h"

void destroyColorButtons(Window** colorButtons) {
	for (int i = 0; i < COLOR_SELECTION_WINDOW_COLORS_AMOUNT; ++i) {
		destroyWindow(colorButtons[i]);
	}
	free(colorButtons);
}

Window** createColorButtons(Window* holdingWindow, SDL_Renderer* renderer) {
	if (holdingWindow == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Window** colorButtons = calloc(COLOR_SELECTION_WINDOW_COLORS_AMOUNT, sizeof(Window*));
	if (colorButtons == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	// init the buttons in the screeen
	for (int i = 0; i < COLOR_SELECTION_WINDOW_COLORS_AMOUNT; ++i) {
		// create the rectangle for i button
		SDL_Rect colorButtonR = { .x = 0, .y =
				COLOR_SELECTION_WINDOW_BUTTON_HEIGHT * i
						+ COLOR_SELECTION_WINDOW_BUTTON_SPACING * i, .h =
				COLOR_SELECTION_WINDOW_BUTTON_HEIGHT, .w =
				COLOR_SELECTION_WINDOW_BUTTON_WIDTH };
		// for each button get button image and create the relevant button
		char* imagePath = getColorImagePath(i, SDL_FALSE);
		if (imagePath != NULL) {
			colorButtons[i] = (Window*) createSimpleButton(holdingWindow,
					renderer, &colorButtonR, imagePath,
					colorButtonHandler);
		}
		// if button creation failed destroy all buttons
		if (colorButtons[i] == NULL || imagePath == NULL) {
			printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
			destroyColorButtons(colorButtons);
			return NULL;
		}
		initWindow(colorButtons[i]);
	}
	return colorButtons;
}

void destroyNavigationButtonsColorView(Window** navigationButtons) {
	destroyWindow(navigationButtons[COLOR_SELECTION_WINDOW_BACK_BUTTON_INDEX]);
	destroyWindow(navigationButtons[COLOR_SELECTION_WINDOW_START_BUTTON_INDEX]);
	free(navigationButtons);
}

Window** createColorNavigationButtons(Window* holdingWindow, SDL_Renderer* renderer) {
	Window** navigationButtons = calloc(COLOR_SELECTION_WINDOW_NAVIGATIONS_AMOUNT, sizeof(Window*));
	if (navigationButtons == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	// create button rectangle positions
	SDL_Rect startR = { .x = 0, .y = COLOR_SELECTION_NAVIGTION_PANE_Y_POS, .h =
			COLOR_SELECTION_WINDOW_BUTTON_HEIGHT, .w =
			COLOR_SELECTION_WINDOW_BUTTON_WIDTH };
	SDL_Rect backR = { .x = COLOR_SELECTION_WINDOW_BUTTON_WIDTH
			+ BOARD_WINDOW_BUTTON_SPACING, .y =
			COLOR_SELECTION_NAVIGTION_PANE_Y_POS, .h =
			COLOR_SELECTION_WINDOW_BUTTON_HEIGHT, .w =
			COLOR_SELECTION_WINDOW_BUTTON_WIDTH };
	// acatually create the navigation buttons of the view
	navigationButtons[COLOR_SELECTION_WINDOW_BACK_BUTTON_INDEX] =
			createSimpleButton(holdingWindow, renderer, &backR,
					COLOR_SELECTION_WINDOW_BACK_BUTTON_PIC_PATH,
					backColorButtonHandler);
	initWindow(navigationButtons[COLOR_SELECTION_WINDOW_BACK_BUTTON_INDEX]);
	navigationButtons[COLOR_SELECTION_WINDOW_START_BUTTON_INDEX] =
			createSimpleButton(holdingWindow, renderer, &startR,
					COLOR_SELECTION_WINDOW_START_BUTTON_PIC_PATH,
					startButtonHandler);
	initWindow(navigationButtons[COLOR_SELECTION_WINDOW_START_BUTTON_INDEX]);
	// if creation of navigation buttons failed, destroy them
	if (navigationButtons[COLOR_SELECTION_WINDOW_BACK_BUTTON_INDEX] == NULL
			|| navigationButtons[COLOR_SELECTION_WINDOW_START_BUTTON_INDEX]
					== NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		destroyNavigationButtonsColorView(navigationButtons);
		return NULL;
	}

	return navigationButtons;
}

Window* createColorSelectionView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState) {
	Window* res = malloc(sizeof(Window));
	if(res == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	ColorSelectionView* data = malloc(sizeof(ColorSelectionView));
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	data->gameState = gameState;
	data->gameSettings = gameSettings;
	MainWindow* main = (MainWindow*) holdingWindow->data;
	SDL_Rect difficultiesR = { .x = 0, .y = 0, .h =
			COLOR_SELECTION_WINDOW_HEIGHT, .w = COLOR_SELECTION_WINDOW_WIDTH };
	res->location = &difficultiesR;
	SDL_Renderer* renderer = main->windowRenderer;
	Window** colorWidgets = createColorButtons(res, renderer);
	Window** navigationButtons = createColorNavigationButtons(res, renderer);
	// if some allocation or button creation failed, free all memory resources
	// set data and window members
	data->colorButtons = colorWidgets;
	data->windowRenderer = renderer;
	data->navigationButtons = navigationButtons;
	// selected color is zero based
	data->selectedColor = gameSettings->color - 1;
	res->data = (void*) data;
	if (res == NULL || data == NULL || holdingWindow == NULL || renderer == NULL
			|| colorWidgets == NULL || navigationButtons == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		destroyColorSelectionView(res);
		return NULL;
	}
	res->destroyWindow = destroyColorSelectionView;
	res->drawWindow = drawColorSelectionView;
	res->handleEventWindow = handleEventColorSelectionView;
	res->holdingWindow = holdingWindow;
	res->setInnerWidgetsReDraw = setColorSelectionInnerReDraw;
	initWindow(res);
	// update view to default selection
	if(updateSelectedColor(COLOR_UNSELECTED, data->selectedColor, data) == SDL_FALSE) {
		return NULL;
	}
	return res;
}

void destroyColorSelectionView(Window* src) {
	if (src == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return;
	}
	//free buttons
	ColorSelectionView* data = (ColorSelectionView*) src->data;
	destroyNavigationButtonsColorView(data->navigationButtons);
	destroyColorButtons(data->colorButtons);
	// free window resources
	SDL_DestroyRenderer(data->windowRenderer);
	free(data);
	free(src);
}

ErrorCode drawColorSelectionView(Window* src) {
	if (src == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}
	ErrorCode err = OK;
	ColorSelectionView* data = (ColorSelectionView*) src->data;
	if (src->reDrawNeeded) {
		// set the render color for re draw
		err |= SDL_SetRenderDrawColor(data->windowRenderer,
				COLOR_SELECTION_WINDOW_BGCOLOR_RED,
				COLOR_SELECTION_WINDOW_BGCOLOR_GREEN,
				COLOR_SELECTION_WINDOW_BGCOLOR_BLUE,
				COLOR_SELECTION_WINDOW_BGCOLOR_ALPHA);
		err |= SDL_RenderClear(data->windowRenderer);
		if(err != OK) {
			printErrorMessage(SDL_ERROR_MESSAGE);
			err = SDL_ERROR;
			return err;
		}
	}
	// draw buttons
	for (int i = 0; i < COLOR_SELECTION_WINDOW_COLORS_AMOUNT; ++i) {
		src->reDrawNeeded |= data->colorButtons[i]->reDrawNeeded;
		err |= data->colorButtons[i]->drawWindow(data->colorButtons[i]);
		if(err!= OK) {
			return err;
		}
	}
	for (int i = 0; i < COLOR_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		src->reDrawNeeded |= data->navigationButtons[i]->reDrawNeeded;
		err |= data->navigationButtons[i]->drawWindow(data->navigationButtons[i]);
		if(err!= OK) {
			return err;
		}
	}
	// actual render
	if (src->reDrawNeeded) {
		SDL_RenderPresent(data->windowRenderer);
	}
	// return to no re draw needed state
	src->reDrawNeeded = SDL_FALSE;
	return err;
}

Command* handleEventColorSelectionView(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	// the command to return is waiting
	Command* cmd;
	ColorSelectionView* data = (ColorSelectionView*) src->data;
	// handle button click on color button
	for (int i = 0; i < COLOR_SELECTION_WINDOW_COLORS_AMOUNT; ++i) {
		if (event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->colorButtons[i], event) == SDL_TRUE) {
			data->colorButtons[i]->handleEventWindow(data->colorButtons[i], event);
			// update current selection or return null to indicate an error
			if (updateSelectedColor(data->selectedColor, i, data) == SDL_FALSE) {
				// TODO: command?
				cmd = createQuitCommand();
				src->holdingWindow->holdingWindow->isClosed = SDL_TRUE;
				return cmd;
			} else {
				UserColor selectedColor = getColor(data->selectedColor);
				cmd = createUserColorCommand(selectedColor);
				return cmd;
			}
		}
	}
	// handle navigation button click
	for (int i = 0; i < COLOR_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		if (event->type == SDL_MOUSEBUTTONUP && isEventWindowRelated(data->navigationButtons[i], event) == SDL_TRUE) {
			cmd = data->navigationButtons[i]->handleEventWindow(
					data->navigationButtons[i], event);
			if (cmd->data != NOP_COMMAND_DATA) {
				return cmd;
			}
		}
	}

	// if we reached here, no operation is needed
	cmd = createNOPCommand();
	return cmd;
}
Command* startButtonHandler(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd = createNOPCommand();
	SimpleButton* data = (SimpleButton*) src->data;
	// only if button is enabled
	if (data->isEnabled == SDL_FALSE) {
		return cmd;
	}
	if (event->type
			== SDL_MOUSEBUTTONUP&& event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow, BOARD_VIEW);
		cmd = createStartCommand();
	}

	return cmd;
}

Command* backColorButtonHandler(Window* src, SDL_Event* event) {
	Command* cmd = createNOPCommand();
	if (src == NULL || event == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	if (event->type
			== SDL_MOUSEBUTTONUP&& event->button.button == SDL_BUTTON_LEFT) {
		setCurrentView(src->holdingWindow->holdingWindow,
				DIFFICULTY_SELECTION_VIEW);
	}

	return cmd;
}

Command* colorButtonHandler(Window* src, SDL_Event* event) {
	Command* cmd = createNOPCommand();
	if (src == NULL || event == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	if (event->type
			== SDL_MOUSEBUTTONUP&& event->button.button == SDL_BUTTON_LEFT) {
	}
	return cmd;
}

SDL_bool updateSelectedColor(int lastSelectedColor, int currentlySelectedColor,ColorSelectionView* view) {
	// get selected color window
	Window* selectedColorWindow = (Window*) view->colorButtons[currentlySelectedColor];
	char* imagePath = getColorImagePath(currentlySelectedColor, SDL_TRUE);
	// update image for selected Color
	SDL_bool err = updateImage(selectedColorWindow, imagePath);
	setEnabledSimpleButton(view->navigationButtons[COLOR_SELECTION_WINDOW_START_BUTTON_INDEX],SDL_TRUE);
	if(err == SDL_FALSE) {
		return SDL_FALSE;
	}
	// if we switch between selections
	if (lastSelectedColor != COLOR_UNSELECTED) {
		// update last selected button
		imagePath = getColorImagePath(lastSelectedColor, SDL_FALSE);
		Window* lastSelected = (Window*) view->colorButtons[lastSelectedColor];
		err = updateImage(lastSelected, imagePath);
		if(err == SDL_FALSE) {
			return SDL_FALSE;
		}
		if (lastSelectedColor == currentlySelectedColor) {
			view->selectedColor = COLOR_UNSELECTED;
			setEnabledSimpleButton(view->navigationButtons[MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX], SDL_FALSE);
			return SDL_TRUE;
		}
	}
	// set currently selected color
	view->selectedColor = currentlySelectedColor;
	return SDL_TRUE;
}

char* getColorImagePath(int difficulty, SDL_bool isSelected) {
	if (difficulty == COLOR_SELECTION_WINDOW_BLACK_BUTTON_INDEX) {
		if (isSelected == SDL_TRUE) {
			return COLOR_SELECTION_WINDOW_BLACK_BUTTON_SELECTED_PIC_PATH;
		}
		return COLOR_SELECTION_WINDOW_BLACK_BUTTON_NOT_SELECTED_PIC_PATH;
	}
	if (isSelected == SDL_TRUE) {
		return COLOR_SELECTION_WINDOW_WHITE_BUTTON_SELECTED_PIC_PATH;
	}
	return COLOR_SELECTION_WINDOW_WHITE_BUTTON_NOT_SELECTED_PIC_PATH;
}

void setColorSelectionInnerReDraw(Window* src, SDL_bool reDraw) {
	if (src == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return;
	}
	ColorSelectionView* data = (ColorSelectionView*) src->data;
	for (int i = 0; i < COLOR_SELECTION_WINDOW_COLORS_AMOUNT; ++i) {
		data->colorButtons[i]->reDrawNeeded = reDraw;
	}
	for (int i = 0; i < COLOR_SELECTION_WINDOW_NAVIGATIONS_AMOUNT; ++i) {
		data->navigationButtons[i]->reDrawNeeded = reDraw;
	}
}
