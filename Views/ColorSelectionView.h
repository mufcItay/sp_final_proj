#ifndef COLORSELECTIONVIEW_H_
#define COLORSELECTIONVIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include "Window.h"

#define COLOR_UNSELECTED -1

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

Window* createColorSelectionView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState);
Window** createColorButtons(Window* holdingWindow, SDL_Renderer* renderer);
Window** createColorNavigationButtons(Window* holdingWindow, SDL_Renderer* renderer);
void destroyColorSelectionView(Window* src);
void drawColorSelectionView(Window* src);
Command* handleEventColorSelectionView(Window* src, SDL_Event* event);
Command* BackColorButtonHandler(Window* src, SDL_Event* event);
Command* StartButtonHandler(Window* src, SDL_Event* event);
Command* ColorButtonHandler(Window* src, SDL_Event* event);
SDL_bool UpdateSelectedColor(int lastSelectedColor, int currentlySelectedColor, ColorSelectionView* view);
void setColorSelectionInnerReDraw(Window* src, SDL_bool reDraw);
char* GetColorImagePath(int color, SDL_bool isSelected);
#endif
