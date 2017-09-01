#ifndef MODESELECTIONVIEW_H_
#define MODESELECTIONVIEW_H_
#include <stdio.h>
#include <stdlib.h>
#include "Window.h"

#define MODE_UNSELECTED -1

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

Window* createModeSelectionView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState);
Window** createModeButtons(Window* holdingWindow, SDL_Renderer* renderer);
Window** createModeNavigationButtons(Window* holdingWindow, SDL_Renderer* renderer);
void destroyModeSelectionView(Window* src);
void drawModeSelectionView(Window* src);
Command* handleEventModeSelectionView(Window* src, SDL_Event* event);
Command* BackModeButtonHandler(Window* src, SDL_Event* event);
Command* NextModeButtonHandler(Window* src, SDL_Event* event);
Command* ModeButtonHandler(Window* src, SDL_Event* event);
SDL_bool UpdateSelectedMode(int lastSelectedMode, int currentlySelectedMode, ModeSelectionView* view);
void setModeSelectionInnerReDraw(Window* src, SDL_bool reDraw);
char* GetModeImagePath(int mode, SDL_bool isSelected);
#endif
