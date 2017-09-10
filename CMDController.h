#ifndef CMDCONTROLLER_H_
#define CMDCONTROLLER_H_

#include "UIController.h"

/*
 * The function sets the functions of the command line relevant controller
 */
void setCMDController(UIController* controller);

/*
 * The function initialzes command line resources
 */
void* CMDInit();

/*
 * The function is responsible for handling user input, returning error code
 */
int CMDHandleInput(void* src, GameSettings* settings, GameState* state);

/*
 * the function draws the command line according to program's current state
 */
void CMDDraw(void* src);

/*
 * The function frees all resources held by the command line controller
 */
void CMDDestroyController(void* src);

#endif



