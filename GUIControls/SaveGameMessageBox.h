#ifndef SAVEGAMEMESSAGEBOX_H_
#define SAVEGAMEMESSAGEBOX_H_

#include "SDL2\SDL.h"
#include "SDL2\SDL_video.h"
#include "CommonGUIUtil.h"

typedef enum mboxbutton_t {
	BUTTON_YES,
	BUTTON_NO,
	BUTTON_CANCEL,
	NO_SELECTION = -1
} MBoxButton;

#define NO_BUTTON_CAPTION "No"
#define YES_BUTTON_CAPTION "Yes"
#define CANCEL_BUTTON_CAPTION "Cancel"
#define MBOX_MESSAGE "Are you sure you don't want to save?"
#define MBOX_TITLE "SAVE?"
#define MBOX_BG_COLOR { 255,   0,   0 }
#define MBOX_TEXT_COLOR { 0,   255,   0 }
#define MBOX_BUTTON_BORDER_COLOR { 0,   0,   255 }
#define MBOX_BUTTON_BG_COLOR { 200,   200,   200}
#define MBOX_BUTTON_BG_COLOR_SELECTED { 10,   240,   70}



MBoxButton getUserSaveGameDescision();
#endif
