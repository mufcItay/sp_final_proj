#ifndef SIMPLEBUTTON_H_
#define SIMPLEBUTTON_H_

#include "Window.h" //A button is a widget also
#include "Commands.h" //A button is a widget also

/*
 * struct that holds button's members
 */
typedef struct simplebutton_t SimpleButton;
struct simplebutton_t{
	SDL_Texture* buttonTexture;
	SDL_Renderer* windowRenderer;
	char* imagePath;
	SDL_bool isEnabled;
};

/*
 * The function creates the button.
 * holdingWindow - the window which has the window as a member
 * handler - the event handler of the window
 * image - the image of the button
 * windowRender - the component the draws the window
 * location - the location of the window
 */
Window* createSimpleButton(Window* holdingWindow, SDL_Renderer* windowRender, SDL_Rect* location,
		char* image , Command* (*handler)(Window* , SDL_Event* ));

/*
 * The function frees all resources of the button
 */
void destroySimpleButton(Window*);

/*
 * The function draws the button
 */
ErrorCode drawSimpleButton(Window* src);

/*
 * The function sets a new image to the button. completes updatign the image of the button
 */
SDL_bool setNewImage(Window* src);

/*
 * The function updates the button image to a new one according to newImagePath
 */
SDL_bool updateImage(Window* src, char* newImagePath);

/*
 * The function sets the enabled state of each of the button
 */
void setEnabledSimpleButton(Window* src,SDL_bool enabled);

/*
 * the function sets re draw state of the view and each of it's inner components
 */
void setButtonInnerReDraw(Window* src, SDL_bool reDraw);

#endif
