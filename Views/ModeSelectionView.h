#ifndef MODESELECTIONVIEW_H_
#define MODESELECTIONVIEW_H_
#include <stdio.h>
#include <stdlib.h>
#include "Window.h"

#define MODE_UNSELECTED -1

/*
 * struct that contains the data of the view
 */
typedef struct modeselectionview_t  ModeSelectionView;
struct modeselectionview_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	Window** modeButtons;
	Window** navigationButtons;
	int selectedMode;
	GameSettings* gameSettings;
	GameState* gameState;
};


/*
 * creator function of the view
 */
Window* createModeSelectionView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState);

/*
 * creator function of the selection buttons of view
 */
Window** createModeButtons(Window* holdingWindow, SDL_Renderer* renderer);

/*
 * creator function of the navigation buttons of view
 */
Window** createModeNavigationButtons(Window* holdingWindow, SDL_Renderer* renderer);

/*
 * destroyer function of the buttons of view
 */
void destroyModeSelectionView(Window* src);

/*
 * draw function of the buttons of view
 */
void drawModeSelectionView(Window* src);

/*
 * handler for view GUI events
 */
Command* handleEventModeSelectionView(Window* src, SDL_Event* event);

/*
 * handler for back button
 */
Command* backModeButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for next button
 */
Command* nextModeButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for mode button
 */
Command* modeButtonHandler(Window* src, SDL_Event* event);

/*
 * the function updates the selected mode,
 * by updating the images of the mode selection buttons of the view
 * lastSelectedMode - the mode which was selected before the moment of selection
 * currentlySelectedMode - the mode that was currently selected by user
 * view - the mode selection view
 */
SDL_bool updateSelectedMode(int lastSelectedMode, int currentlySelectedMode, ModeSelectionView* view);

/*
 * the function sets re draw state of the view and each of it's inner components
 */
void setModeSelectionInnerReDraw(Window* src, SDL_bool reDraw);

/*
 * the function gets the path of the image that is relevant to given mode and isSelected state.
 */
char* getModeImagePath(int mode, SDL_bool isSelected);

/*
 * The function frees resources of mode buttons
 */
void destroyModeButtons(ModeSelectionView* data);

/*
 * The function frees resources of mode view navigation buttons
 */
void destroyModeNavigationButtons(ModeSelectionView* data);
#endif
