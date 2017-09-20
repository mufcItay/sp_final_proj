#include "PawnPromotionMessageBox.h"

MBoxPawnPromotionButton getUserPawnPromotionDecision() {
	const SDL_MessageBoxButtonData buttons[] = {
		{ 0, BUTTON_QUEEN, QUEEN_BUTTON_CAPTION },
		{ 0, BUTTON_KNIGHT, KNIGHT_BUTTON_CAPTION },
		{ 0, BUTTON_ROCK, ROCK_BUTTON_CAPTION },
		{ 0, BUTTON_BISHOP, BISHOP_BUTTON_CAPTION },
		{ 0, BUTTON_PAWN, PAWN_BUTTON_CAPTION}
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{
			MBOX_PAWN_BG_COLOR,
			MBOX_PAWN_TEXT_COLOR,
			MBOX_PAWN_BUTTON_BORDER_COLOR,
			MBOX_PAWN_BUTTON_BG_COLOR,
			MBOX_PAWN_BUTTON_BG_COLOR_SELECTED
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,
		NULL, /* .window */
		MBOX_PAWN_TITLE, /* .title */
		MBOX_PAWN_MESSAGE, /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		printErrorMessage(MBOX_PAWN_ERROR_MESSAGE);
		return PAWN_NO_SELECTION;
	}

	return buttonid;
}
