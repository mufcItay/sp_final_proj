#ifndef UICONTROLLER_H_
#define UICONTROLLER_H_
#include "CommonGUIUtil.h"
#include "Commands.h"


typedef struct uicontroller_t UIController;
struct uicontroller_t {
	void* (*Init)(GameSettings* ,GameState* );
	void (*Draw) (void* );
	int (*HandleInput)(void* );
	void (*DestroyController)(void* );
};

#endif
