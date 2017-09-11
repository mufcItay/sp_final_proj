#ifndef GUICONTROLLER_H_
#define GUICONTROLLER_H_

#include "SDL2\SDL.h"
#include "SDL2\SDL_video.h"
#include "CommonGUIUtil.h"
#include "UIController.h"

/*
 * The function sets the functions of the GUI relevant controller
 */
void setGUIController(UIController* controller);
/*
 * The function initialzes GUI
 */
void* GUIInit();
/*
 * The function is responsible for handling user input, returning error code
 */
ErrorCode GUIHandleInput(void* src, GameSettings* settings, GameState* state);

/*
 * the function draws the GUI according to programs current state
 */
void GUIDraw(void* src);

/*
 * The function frees all resources held by the GUI controller
 */
void GUIDestroyController(void* src);

#endif
