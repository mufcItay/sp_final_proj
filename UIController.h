#ifndef UICONTROLLER_H_
#define UICONTROLLER_H_
#include "CommonGUIUtil.h"
#include "Commands.h"

/*
 * struct that holds function pointers the the relevant ui functions
 */
typedef struct uicontroller_t UIController;
struct uicontroller_t {
	void* (*init)(GameSettings* ,GameState* );
	void (*draw) (void* );
	int (*handleInput)(void* ,GameSettings* ,GameState*);
	void (*destroyController)(void* );
};

#endif
