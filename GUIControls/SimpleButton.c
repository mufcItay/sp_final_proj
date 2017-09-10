#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SimpleButton.h"
#include "CommonGUIUtil.h"
#include "Window.h"

Window* createSimpleButton(Window* holdingWindow, SDL_Renderer* windowRender, SDL_Rect* location,
		char* image, Command* (*handler)(Window* , SDL_Event* )) {
	if (windowRender == NULL || location == NULL || image == NULL ) {
		return NULL ;
	}
	//Allocate memory
	Window* res = (Window*) malloc(sizeof(Window));
	SimpleButton* data = (SimpleButton*) malloc(sizeof(SimpleButton));
	// create image texture and surface
	SDL_Surface* loadingSurface = SDL_LoadBMP(image);
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(windowRender,
			loadingSurface);
	// handle errors
	if (res == NULL || data == NULL || loadingSurface == NULL
			|| buttonTexture == NULL) {
		free(res);
		free(data);
		SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
		SDL_DestroyTexture(buttonTexture); ////It is safe to pass NULL
		return NULL ;
	}
	// free image resources
	SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created
	// set members
	res->location = copyRect(location);
	res->holdingWindow = holdingWindow;
	data->buttonTexture = buttonTexture;
	data->windowRenderer = windowRender;
	res->isClosed = SDL_FALSE;
	res->destroyWindow = destroySimpleButton;
	res->drawWindow = drawSimpleButton;
	res->setInnerWidgetsReDraw = setButtonInnerReDraw;
	res->handleEventWindow = handler;
	res->data = data;
	data->isEnabled = SDL_TRUE;
	initWindow(res);
	updateImage(res,image);
	return res;
}

//You need this function in order to destroy all data Associate with a button:
void destroySimpleButton(Window* src) {
	if (src == NULL ) {
		return;
	}
	SimpleButton* castData = (SimpleButton*) src->data;
	free(castData->imagePath);
	free(src->location);
	SDL_DestroyTexture(castData->buttonTexture);
	free(castData);
	free(src);
}

void setEnabledSimpleButton(Window* src,SDL_bool enabled) {
	if (src == NULL ) {
		return;
	}

	SimpleButton* castData = (SimpleButton*) src->data;
	if(castData->isEnabled != enabled) {
		src->reDrawNeeded = SDL_TRUE;
		castData->isEnabled = enabled;
	}
}

void drawSimpleButton(Window* src) {
	if (src == NULL ) {
		return;
	}
	SimpleButton* castData = (SimpleButton*) src->data;
	if(src->reDrawNeeded == SDL_TRUE)
	{
		setNewImage(src);
		SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,
			src->location);
	}
}


SDL_bool setNewImage(Window* src)
{
	src->reDrawNeeded = SDL_FALSE;
	SimpleButton* data = (SimpleButton*) (src->data);
	char* imagePath = data->imagePath;
	if(data->isEnabled == SDL_FALSE) {
		// set image accoridng to selected state
		imagePath = (char*) malloc(sizeof(char) * strlen(data->imagePath) +sizeof(char) +sizeof(char));// + backslash 0 + new disabled char
		for (int i = 0; i < strlen(data->imagePath); ++i) {
			char* currentStr = data->imagePath + i;
			if(strcmp(currentStr,BMP_FILE_TYPE) == 0) {
				imagePath[i] = DISABLED_BUTTON_CHAR;
				i++;
				sprintf((imagePath + i), "%s",BMP_FILE_TYPE);
				break;
			}
			imagePath[i] = data->imagePath[i];
		}
	}
	// create texture and surface of image
	SDL_Surface* loadingSurface = SDL_LoadBMP(imagePath); //We use the surface as a temp var;
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(data->windowRenderer,
			loadingSurface);
	data->buttonTexture = buttonTexture;
	// handle errors
	if (data == NULL || loadingSurface == NULL
			|| buttonTexture == NULL) {
		destroySimpleButton(src);
		SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
		SDL_DestroyTexture(buttonTexture); ////It is safe to pass NULL
		return SDL_FALSE ;
	}
	//free unnesecerray memory resources
	SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created
	if(data->isEnabled == SDL_FALSE) {
		free(imagePath);
	}
	return SDL_TRUE;
}

void updateImage(Window* src, char* newImagePath){
	SimpleButton* button = (SimpleButton*) (src->data);
	src->reDrawNeeded = SDL_TRUE;
	int newImageLen = strlen(newImagePath) +1;
	// allocate image path string memory
	button->imagePath= (char*) malloc(sizeof(char) * newImageLen);
	strcpy(button->imagePath, newImagePath);
}

void setButtonInnerReDraw(Window* src, SDL_bool reDraw) {
	src->reDrawNeeded = reDraw;
}
