#include <stdlib.h>
#include <stdio.h>
#include "SoldierButton.h"
#include "GameBoardView.h"
#include "CommonGUIUtil.h"
#include "Commands.h"

Window* createSoldierButton(Window* holdingWindow, SDL_Renderer* windowRenderer,int row, int col, char type) {
	//Allocate data
	Window* res = (Window*) malloc(sizeof(Window));
	SoldierButton* data = (SoldierButton*) malloc(sizeof(SoldierButton));
	if (res == NULL || data == NULL || windowRenderer == NULL) {
		free(res);
		free(data);
		//We first destroy the renderer
		return NULL ;
	}
	SDL_Rect location = { .x = col * SOLDIER_BUTTON_IMAGE_WIDTH , .y = row * SOLDIER_BUTTON_IMAGE_HEIGHT, .h = SOLDIER_BUTTON_IMAGE_HEIGHT, .w = SOLDIER_BUTTON_IMAGE_WIDTH };
	res->location = copyRect(&location);
	res->holdingWindow = holdingWindow;
	data->rowIndex = row;
	data->columnIndex = col;
	data->windowRenderer = windowRenderer;
	data->soldierBGColor = ((row%2 + col%2)%2) ? SOLDIER_COLOR_WHITE: SOLDIER_COLOR_BLACK;
	data->isSelected = SDL_FALSE;
	data->soldierType = type;
	res->destroyWindow = destroySoldierButton;
	res->drawWindow = drawSoldierButton;
	res->data = data;
	res->setInnerWidgetsReDraw = setSoldierButtonInnerReDraw;
	res->isClosed = SDL_FALSE;
	res->handleEventWindow = handleEventSoldierButton;
	setImageData(res);
	return res;
}

void updateSoldierData(Window* src, char newType)
{
	SoldierButton* soldier = (SoldierButton*) (src->data);
	src->reDrawNeeded = SDL_TRUE;
	soldier->isSelected = SDL_FALSE;
	soldier->soldierType = newType;
}

SDL_bool setImageData(Window* src)
{
	src->reDrawNeeded = SDL_FALSE;
	SoldierButton* data = (SoldierButton*) (src->data);
	char* imagePath = getImagePath(data);
	SDL_Surface* loadingSurface = SDL_LoadBMP(imagePath); //We use the surface as a temp var;
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(data->windowRenderer,
			loadingSurface);
	data->buttonTexture = buttonTexture;
	if (data == NULL || loadingSurface == NULL
			|| buttonTexture == NULL) {
		free(data);
		SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
		SDL_DestroyTexture(buttonTexture); ////It is safe to pass NULL
		return SDL_FALSE ;
	}
	SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created
	free(imagePath);
	return SDL_TRUE;
}

void destroySoldierButton(Window* src) {
	if (src == NULL ) {
		return;
	}
	SoldierButton* castData = (SoldierButton*) src->data;
	free(src->location);
	SDL_DestroyTexture(castData->buttonTexture);
	SDL_DestroyRenderer(castData->windowRenderer);
	free(castData);
	free(src);
}

Command* handleEventSoldierButton(Window* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return NULL; //Better to return an error value
	}
	Command* cmd = createNOPCommand();
	SoldierButton* castData = (SoldierButton*) src->data;
	GameBoardData* gameBoard = (GameBoardData*)(src->holdingWindow->data);

	if(event->type == SDL_MOUSEBUTTONUP  && event->button.button == SDL_BUTTON_RIGHT){
		// show possible moves
		SDL_Point origin = {.x =castData->rowIndex , .y = castData->columnIndex};
		cmd = createGetMovesCommand(origin);
		return cmd;
	}

	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
		if(castData->soldierType == SOLDIER_TYPE_EMPTY) {
			return cmd;
		}

		castData->isSelected = SDL_TRUE;
		gameBoard->selectedSoldier = src;
	}
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		if(gameBoard->selectedSoldier == NULL) {
			return NULL;
		}
		// perform movement
		cmd = moveSelectedSoldierTo(gameBoard,src);
		gameBoard->selectedSoldier = NULL;
		castData->isSelected = SDL_FALSE;
		return cmd;
	}

	return cmd;
}

void drawSoldierButton(Window* src) {
	if (src == NULL ) {
		return;
	}

	SoldierButton* castData = (SoldierButton*) src->data;
	//if has changed
	if(src->reDrawNeeded == SDL_TRUE)
	{
		setImageData(src);
		SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,
			src->location);
	}
}


char* getImagePath(SoldierButton* src)
{
	char soldierColorChar;
	char soldierTypeChar;
	char backgroundColorChar = src->soldierBGColor;
	char isSelectedChar = SOLDIER_BUTTON_NOT_SELECTED;//(src->isSelected == SDL_TRUE) ? SOLDIER_BUTTON_SELECTED:SOLDIER_BUTTON_NOT_SELECTED;
	if(src->soldierType == SOLDIER_TYPE_EMPTY)
	{
		soldierColorChar = SOLDIER_COLOR_EMPTY;
		soldierTypeChar = SOLDIER_TYPE_EMPTY;
	}
	else
	{
		soldierColorChar = isCharLoweCase(src->soldierType) ? SOLDIER_COLOR_WHITE:SOLDIER_COLOR_BLACK;
		soldierTypeChar = src->soldierType;
	}
	char* imageName = malloc(sizeof(char) +  sizeof(char) * SOLDIER_BUTTON_IMAGE_PATH_PREPOSTFIX_LENGTH);
    sprintf(imageName , SOLDIER_PICS_PATTERN, backgroundColorChar, soldierColorChar, soldierTypeChar, isSelectedChar);
	return imageName;
}

/*
 * the function sets re draw state of the view and each of it's inner components
 */
void setSoldierButtonInnerReDraw(Window* src, SDL_bool reDraw) {
	src->reDrawNeeded = reDraw;
}
