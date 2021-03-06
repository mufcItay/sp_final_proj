#include "SaveGameMessageBox.h"

MBoxSaveGameButton getUserSaveGameDescision() {
	const SDL_MessageBoxButtonData buttons[] = {
		{ 0, BUTTON_YES, YES_BUTTON_CAPTION },
		{ 0, BUTTON_NO, NO_BUTTON_CAPTION },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, BUTTON_CANCEL, CANCEL_BUTTON_CAPTION },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{
			MBOX_SAVE_BG_COLOR,
			MBOX_SAVE_TEXT_COLOR,
			MBOX_SAVE_BUTTON_BORDER_COLOR,
			MBOX_SAVE_BUTTON_BG_COLOR,
			MBOX_SAVE_BUTTON_BG_COLOR_SELECTED
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,
		NULL, /* .window */
		MBOX_SAVE_TITLE, /* .title */
		MBOX_SAVE_MESSAGE, /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		printErrorMessage(MBOX_SAVE_ERROR_MESSAGE);
		return SAVE_NO_SELECTION;
	}

	return buttonid;
}
