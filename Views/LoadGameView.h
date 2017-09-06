#ifndef LOADGAMEVIEW_H_
#define LOADGAMEVIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include "Window.h"
#include "MainWindow.h"


#define SLOT_UNSELECTED -1


typedef struct loadgameview_t  LoadGameView;
struct loadgameview_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	Window** slotButtons;
	Window** menuButtons;
	int selectedSlot;
	int slotsAmount;
	enum WindowView lastView;
	GameSettings* gameSettings;
	GameState* gameState;
};

Window* createLoadGameView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState);
Window** createSlotButtons(Window* holdingWindow, SDL_Renderer* renderer);
Window** createLoadGameMenuButtons(Window* holdingWindow, SDL_Renderer* renderer);
void destroyLoadGameView(Window* src);
void drawLoadGameView(Window* src);
Command* handleEventLoadGameView(Window* src, SDL_Event* event);
Command* backLoadGameButtonHandler(Window* src, SDL_Event* event);
Command* loadSlotButtonHandler(Window* src, SDL_Event* event);
Command* slotButtonHandler(Window* src, SDL_Event* event);
SDL_bool getUpdatedImagePathForSlot(int lastSelectedSlot, int currentlySelectedSlot, LoadGameView* view);
void setLoadGameInnerReDraw(Window* src, SDL_bool reDraw);
char* getSlotImagePath(int slot);
#endif
