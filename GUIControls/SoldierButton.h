#ifndef SOLDIERBUTTON_H_
#define SOLDIERBUTTON_H_

#include "Window.h"

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
};

Window* createSoldierButton(Window* holdingWindow, SDL_Renderer* windowRenderer,int row, int col, char type);

//You need this function in order to destroy all data Associate with a button:
void destroySoldierButton(Window* src);

Command* handleEventSoldierButton(Window* src, SDL_Event* event);

void drawSoldierButton(Window* src);

char* getImagePath(SoldierButton* src);

SDL_bool setImageData(Window* data);

void updateSoldierData(Window* src, char newType);

#endif
