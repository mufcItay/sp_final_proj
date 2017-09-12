#ifndef DIFFICULTYSELECTIONVIEW_H_
#define DIFFICULTYSELECTIONVIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include "Window.h"

#define DIFFICULTY_UNSELECTED -1

/*
 * struct that contains the data of the view
 */
typedef struct difficultyselectionview_t  DifficultySelectionView;
struct difficultyselectionview_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	Window** difficultyButtons;
	Window** navigationButtons;
	int selectedDifficulty;
	GameSettings* gameSettings;
	GameState* gameState;
};

/*
 * creator function of the view
 */
Window* createDifficultySelectionView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState);

/*
 * creator function of the selection buttons of view
 */
Window** createDifficultyButtons(Window* holdingWindow, SDL_Renderer* renderer);

/*
 * creator function of the navigation buttons of view
 */
Window** createDifficultyNavigationButtons(Window* holdingWindow, SDL_Renderer* renderer);


/*
 * destroyer function of the buttons of view
 */
void destroyDifficultySelectionView(Window* src);

/*
 * draw function of the buttons of view
 */
ErrorCode drawDifficultySelectionView(Window* src);

/*
 * handler for view GUI events
 */
Command* handleEventDifficultySelectionView(Window* src, SDL_Event* event);

/*
 * handler for back button
 */
Command* backDifficultiesButtonHandler(Window* src, SDL_Event* event);



/*
 * handler for next button
 */
Command* nextDifficultiesButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for difficulty button
 */
Command* difficultyButtonHandler(Window* src, SDL_Event* event);

/*
 * the function updates the selected difficulty,
 * by updating the images of the difficulty selection buttons of the view
 * lastSelectedDifficulty - the difficulty which was selected before the moment of selection
 * currentlySelectedDifficulty - the difficulty that was currently selected by user
 * view - the difficulty selection view
 */
SDL_bool updateSelectedDifficulty(int lastSelectedDifficulty, int currentlySelectedDifficulty, DifficultySelectionView* view);

/*
 * the function sets re draw state of the view and each of it's inner components
 */
void setDifficultySelectionInnerReDraw(Window* src, SDL_bool reDraw);

/*
 * the function gets the path of the image that is relevant to given difficulty and isSelected state.
 */
char* getDifficultyImagePath(int difficulty);

/*
 * The function destroys the difficulty buttons of the view
 */
void destroyDifficultyButtons(DifficultySelectionView* data);

/*
 * The function destroys the navigation buttons of the view
 */
void destroyNavigationDifficultyButtons(DifficultySelectionView* data);

#endif




