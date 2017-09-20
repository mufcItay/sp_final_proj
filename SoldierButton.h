#ifndef SOLDIERBUTTON_H_
#define SOLDIERBUTTON_H_

#include "Window.h"

/*
 * struct that holds soldier button data
 */
typedef struct soldierbutton_t SoldierButton;
struct soldierbutton_t{
	SDL_Texture* buttonTexture;
	SDL_Renderer* windowRenderer;
	SDL_Window* window;
	char soldierType;
	char soldierBGColor;
	int rowIndex;
	int columnIndex;
	SDL_bool isSelected;
	SDL_bool isHighlighted;
};

/*
 * The function creates the button.
 * holdingWindow - the window which has the window as a member
 * col - the soldier column in board
 * row - the soldier row in board
 * type - the soldier type
 * windowRender - the component the draws the window
 */
Window* createSoldierButton(Window* holdingWindow, SDL_Renderer* windowRenderer,int row, int col, char type);

/*
 * The function frees all resources of the button
 */
void destroySoldierButton(Window* src);

/*
 * the function handles an event that is related to the given soldier button
 */
Command* handleEventSoldierButton(Window* src, SDL_Event* event);

/*
 * The function draws the soldier button
 */
ErrorCode drawSoldierButton(Window* src);

/*
 * the function returns the path to the image of the soldier button
 */
char* getImagePath(SoldierButton* src);

/*
 * The function sets a new image to the button. completes updatign the image of the button
 */
SDL_bool setImageData(Window* data);

/*
 * The function updates the soldier's type and by that changes the button image
 */
void updateSoldierData(Window* src, char newType);

/*
 * the function sets re draw state of the view and each of it's inner components
 */
void setSoldierButtonInnerReDraw(Window* src, SDL_bool reDraw);
#endif
