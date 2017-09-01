#ifndef DIFFICULTYSELECTIONVIEW_H_
#define DIFFICULTYSELECTIONVIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include "Window.h"


#define DIFFICULTY_UNSELECTED -1

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

Window* createDifficultySelectionView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState);
Window** createDifficultyButtons(Window* holdingWindow, SDL_Renderer* renderer);
Window** createDifficultyNavigationButtons(Window* holdingWindow, SDL_Renderer* renderer);
void destroyDifficultySelectionView(Window* src);
void drawDifficultySelectionView(Window* src);
Command* handleEventDifficultySelectionView(Window* src, SDL_Event* event);
Command* BackDifficultiesButtonHandler(Window* src, SDL_Event* event);
Command* NextDifficultiesButtonHandler(Window* src, SDL_Event* event);
Command* DifficultyButtonHandler(Window* src, SDL_Event* event);
SDL_bool UpdateSelectedDifficulty(int lastSelectedDifficulty, int currentlySelectedDifficulty, DifficultySelectionView* view);
void setDifficultySelectionInnerReDraw(Window* src, SDL_bool reDraw);
char* GetDifficultyImagePath(int difficulty);
#endif
