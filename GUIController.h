#ifndef GUICONTROLLER_H_
#define GUICONTROLLER_H_

#include "SDL2\SDL.h"
#include "SDL2\SDL_video.h"
#include "CommonGUIUtil.h"
#include "UIController.h"

void SetGUIController(UIController* controller);
void* GUIInit();
int GUIHandleInput(void* src);
void GUIDraw(void* src);
void GUIDestroyController(void* src);

#endif
