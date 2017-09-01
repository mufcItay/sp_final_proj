#ifndef SIMPLEBUTTON_H_
#define SIMPLEBUTTON_H_

#include "Window.h" //A button is a widget also
#include "Commands.h" //A button is a widget also

typedef struct simplebutton_t SimpleButton;
struct simplebutton_t{
	SDL_Texture* buttonTexture;
	SDL_Renderer* windowRenderer;
	char* imagePath;
	SDL_bool isEnabled;
};

//You need a create function:
Window* createSimpleButton(Window* holdingWindow, SDL_Renderer* windowRender, SDL_Rect* location,
		char* image , Command* (*handler)(Window* , SDL_Event* ));

//You need this function in order to destroy all data Associate with a button:
void destroySimpleButton(Window*);

void drawSimpleButton(Window* src);

SDL_bool setNewImage(Window* src);

void updateImage(Window* src, char* newImagePath);

void setEnabledSimpleButton(Window* src,SDL_bool enabled);

#endif
