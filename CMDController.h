#ifndef CMDCONTROLLER_H_
#define CMDCONTROLLER_H_

#include "UIController.h"

void setCMDController(UIController* controller);
void* CMDInit();
int CMDHandleInput(void* src, GameSettings* settings, GameState* state);
void CMDDraw(void* src);
void CMDDestroyController(void* src);

#endif
