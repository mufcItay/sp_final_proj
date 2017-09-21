#ifndef SAVEGAMEMESSAGEBOX_H_
#define SAVEGAMEMESSAGEBOX_H_

#include "SDL.h"
#include "SDL_video.h"
#include "CommonGUIUtil.h"

typedef enum mboxsavegamebutton_t {
	BUTTON_YES,
	BUTTON_NO,
	BUTTON_CANCEL,
	SAVE_NO_SELECTION = -1
} MBoxSaveGameButton;

#define NO_BUTTON_CAPTION "No"
#define YES_BUTTON_CAPTION "Yes"
#define CANCEL_BUTTON_CAPTION "Cancel"
#define MBOX_SAVE_MESSAGE "Do you you want to save before switching from game screen?"
#define MBOX_SAVE_TITLE "SAVE?"
#define MBOX_SAVE_ERROR_MESSAGE "Error showing message box"

#define MBOX_SAVE_BG_COLOR { 255,   0,   0 }
#define MBOX_SAVE_TEXT_COLOR { 0,   255,   0 }
#define MBOX_SAVE_BUTTON_BORDER_COLOR { 0,   0,   255 }
#define MBOX_SAVE_BUTTON_BG_COLOR { 200,   200,   200}
#define MBOX_SAVE_BUTTON_BG_COLOR_SELECTED { 10,   240,   70}



MBoxSaveGameButton getUserSaveGameDescision();
#endif
