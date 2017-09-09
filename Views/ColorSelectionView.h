#ifndef COLORSELECTIONVIEW_H_
#define COLORSELECTIONVIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include "Window.h"

#define COLOR_UNSELECTED -1

/*
 * struct that contains the data of the view
 */
typedef struct colorselectionview_t  ColorSelectionView;
struct colorselectionview_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	Window** colorButtons;
	Window** navigationButtons;
	int selectedColor;
	GameSettings* gameSettings;
	GameState* gameState;
};

/*
 * creator function of the view
 */
Window* createColorSelectionView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState);

/*
 * creator function of the selection buttons of view
 */
Window** createColorButtons(Window* holdingWindow, SDL_Renderer* renderer);

/*
 * creator function of the navigation buttons of view
 */
Window** createColorNavigationButtons(Window* holdingWindow, SDL_Renderer* renderer);

/*
 * destroyer function of the buttons of view
 */
void destroyColorSelectionView(Window* src);


/*
 * draw function of the buttons of view
 */
void drawColorSelectionView(Window* src);


/*
 * handler for view GUI events
 */
Command* handleEventColorSelectionView(Window* src, SDL_Event* event);

/*
 * handler for back button
 */
Command* backColorButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for start button
 */
Command* startButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for color button
 */
Command* colorButtonHandler(Window* src, SDL_Event* event);


/*
 * the function updates the selected color,
 * by updating the images of the color selection buttons of the view
 * lastSelectedColor - the color which was selected before the moment of selection
 * currentlySelectedColor - the color that was currently selected by user
 * view - the color selection view
 */
SDL_bool updateSelectedColor(int lastSelectedColor, int currentlySelectedColor, ColorSelectionView* view);

/*
 * the function sets re draw state of the view and each of it's inner components
 */
void setColorSelectionInnerReDraw(Window* src, SDL_bool reDraw);

/*
 * the function gets the path of the image that is relevant to given color and isSelected state.
 */
char* getColorImagePath(int color, SDL_bool isSelected);
#endif
