#include "InfoMessageBox.h"


ErrorCode showInfoMessageBox(const char* message) {
	const SDL_MessageBoxButtonData buttons[] = {
		{ 0, BUTTON_OK, OK_BUTTON_CAPTION },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{
			MBOX_INFO_BG_COLOR,
			MBOX_INFO_TEXT_COLOR,
			MBOX_INFO_BUTTON_BORDER_COLOR,
			MBOX_INFO_BUTTON_BG_COLOR,
			MBOX_INFO_BUTTON_BG_COLOR_SELECTED
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,
		NULL, /* .window */
		MBOX_INFO_TITLE, /* .title */
		message, /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		printErrorMessage(MBOX_INFO_ERROR_MESSAGE);
		return INFO_NO_SELECTION;
	}

	return buttonid;
}
