#ifndef CMDCONTROLLER_H_
#define CMDCONTROLLER_H_

#include "UIController.h"

void SetCMDController(UIController* controller);
void* CMDInit();
int CMDHandleInput(void* src);
void CMDDraw(void* src);
void CMDDestroyController(void* src);

#endif
