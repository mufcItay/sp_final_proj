#include <stdlib.h>
#include <stdio.h>
#include "SoldierButton.h"
#include "GameBoardView.h"
#include "CommonGUIUtil.h"
#include "Commands.h"

Window* createSoldierButton(Window* holdingWindow, SDL_Renderer* windowRenderer,int row, int col, char type) {
	//Allocate memory
	Window* res = (Window*) malloc(sizeof(Window));
	SoldierButton* data = (SoldierButton*) malloc(sizeof(SoldierButton));
	// hnadle memory error
	if (res == NULL || data == NULL || windowRenderer == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(res);
		free(data);
		//We first destroy the renderer
		return NULL ;
	}
	// create rectangle and actual button
	SDL_Rect location = { .x = col * SOLDIER_BUTTON_IMAGE_WIDTH , .y = row * SOLDIER_BUTTON_IMAGE_HEIGHT, .h = SOLDIER_BUTTON_IMAGE_HEIGHT, .w = SOLDIER_BUTTON_IMAGE_WIDTH };
	// set data members
	res->location = copyRect(&location);
	res->holdingWindow = holdingWindow;
	data->buttonTexture = NULL;
	data->rowIndex = row;
	data->columnIndex = col;
	data->windowRenderer = windowRenderer;
	data->soldierBGColor = ((row%2 + col%2)%2) ? SOLDIER_COLOR_WHITE: SOLDIER_COLOR_BLACK;
	data->isSelected = SDL_FALSE;
	data->isHighlighted = SDL_FALSE;
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
	soldier->isHighlighted = SDL_FALSE;
	soldier->soldierType = newType;
}

SDL_bool setImageData(Window* src)
{
	src->reDrawNeeded = SDL_FALSE;
	SoldierButton* data = (SoldierButton*) (src->data);
	// get current image path
	char* imagePath = getImagePath(data);
	printErrorMessage(imagePath);
	if(imagePath == NULL) {
		return SDL_FALSE;
	}
	// set the surface and texture to be able to draw the soldier image
	SDL_Surface* loadingSurface = SDL_LoadBMP(imagePath); //We use the surface as a temp var;
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(data->windowRenderer,
			loadingSurface);
	// free old texture
	if(data->buttonTexture != NULL) {
		SDL_DestroyTexture(data->buttonTexture);
	}

	data->buttonTexture = buttonTexture;
	// handle errors
	if (data == NULL || loadingSurface == NULL || buttonTexture == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(data);
		SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
		SDL_DestroyTexture(buttonTexture); ////It is safe to pass NULL
		return SDL_FALSE ;
	}

	// free memory
	SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created
	free(imagePath);
	return SDL_TRUE;
}

void destroySoldierButton(Window* src) {
	if (src == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
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
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	Command* cmd = createNOPCommand();
	SoldierButton* castData = (SoldierButton*) src->data;
	GameBoardData* gameBoard = (GameBoardData*)(src->holdingWindow->data);

	// get moves command
	if(event->type == SDL_MOUSEBUTTONUP  && event->button.button == SDL_BUTTON_RIGHT){
		// get the moved and use isHighlighted
		// show possible moves
		SDL_Point origin = {.x =castData->rowIndex , .y = castData->columnIndex};
		cmd = createGetMovesCommand(origin);
		return cmd;
	}

	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
		if(castData->soldierType == SOLDIER_TYPE_EMPTY) {
			return cmd;
		}
		// set selected state
		castData->isSelected = SDL_TRUE;
		gameBoard->selectedSoldier = src;
	}
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		if(gameBoard->selectedSoldier == NULL) {
			return cmd;
		}
		// perform movement
		cmd = moveSelectedSoldierTo(gameBoard,src);
		gameBoard->selectedSoldier = NULL;
		castData->isSelected = SDL_FALSE;

		return cmd;
	}

	return cmd;
}

ErrorCode drawSoldierButton(Window* src) {
	if (src == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}

	ErrorCode err = OK;
	SoldierButton* castData = (SoldierButton*) src->data;
	//if the image has changed
	if(src->reDrawNeeded == SDL_TRUE) {
		if(setImageData(src) == SDL_FALSE) {
			return MEMORY_ERROR;
		}
		err |= SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,
			src->location);
	}
	return err;
}


char* getImagePath(SoldierButton* src)
{
	char soldierColorChar;
	char soldierTypeChar;
	char backgroundColorChar = src->soldierBGColor;
	char isHighlightedChar = SOLDIER_BUTTON_NOT_HIGHLIGHTED;//(src->isHighlighted == SDL_TRUE) ? SOLDIER_BUTTON_HIGHLIGHTED:SOLDIER_BUTTON_NOT_HIGHLIGHTED;
	if(src->soldierType == SOLDIER_TYPE_EMPTY) {
		soldierColorChar = SOLDIER_COLOR_EMPTY;
		soldierTypeChar = SOLDIER_TYPE_EMPTY;
	}
	else {
		soldierColorChar = isCharLoweCase(src->soldierType) ? SOLDIER_COLOR_WHITE:SOLDIER_COLOR_BLACK;
		soldierTypeChar = toLowerCase(src->soldierType);
	}
	// allocate memory for path string
	char* imageName = malloc(sizeof(char) +  sizeof(char) * SOLDIER_BUTTON_IMAGE_PATH_PREPOSTFIX_LENGTH);
	if(imageName == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	if(sprintf(imageName , SOLDIER_PICS_PATTERN, backgroundColorChar, soldierColorChar, soldierTypeChar, isHighlightedChar) <= 0)  {
		printErrorMessage(STRING_ERROR_MESSAGE);
		return NULL;
	}
	return imageName;
}

/*
 * the function sets re draw state of the view and each of it's inner components
 */
void setSoldierButtonInnerReDraw(Window* src, SDL_bool reDraw) {
	src->reDrawNeeded = reDraw;
}
