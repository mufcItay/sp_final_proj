#ifndef LOADGAMEVIEW_H_
#define LOADGAMEVIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include "Window.h"
#include "MainWindow.h"


#define SLOT_UNSELECTED -1

/*
 * struct that contains the data of the view
 */
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

/*
 * creator function of the view
 */
Window* createLoadGameView(Window* holdingWindow, GameSettings* gameSettings, GameState* gameState);

/*
 * creator function of the selection buttons of view
 */
Window** createSlotButtons(Window* holdingWindow, SDL_Renderer* renderer);

/*
 * creator function of the menu buttons of view
 */
Window** createLoadGameMenuButtons(Window* holdingWindow, SDL_Renderer* renderer);

/*
 * destroyer function of the buttons of view
 */
void destroyLoadGameView(Window* src);

/*
 * draw function of the buttons of view
 */
ErrorCode drawLoadGameView(Window* src);

/*
 * handler for view GUI events
 */
Command* handleEventLoadGameView(Window* src, SDL_Event* event);

/*
 * handler for back button
 */
Command* backLoadGameButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for load button
 */
Command* loadSlotButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for slot button
 */
Command* slotButtonHandler(Window* src, SDL_Event* event);

/*
 * the function updates the selected slot,
 * by updating the images of the slot selection buttons of the view
 * lastSelectedSlot - the slot which was selected before the moment of selection
 * currentlySelectedSlot - the slot that was currently selected by user
 * view - the slot selection view
 */
ErrorCode getUpdatedImagePathForSlot(int lastSelectedSlot, int currentlySelectedSlot, LoadGameView* view);

/*
 * the function sets re draw state of the view and each of it's inner components
 */
void setLoadGameInnerReDraw(Window* src, SDL_bool reDraw);

/*
 * the function gets the path of the image that is relevant to given slot.
 */
char* getSlotImagePath(int slot);

/*
 * The function deletes old slot buttons and creates new ones for updating saved games live
 */
Window** updateSlotButtons(Window* holdingWindow);

/*
 * The function destroys the menu buttons of load view
 */
void destroyLoadMenuButtons(Window** menuButtons);

/*
 * The function destroys the slot buttons of the view
 */
void destroyLoadSlotButtons(LoadGameView* view, Window** slotButtons);

#endif

