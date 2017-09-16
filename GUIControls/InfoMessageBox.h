#ifndef INFOMESSAGEBOX_H_
#define INFOMESSAGEBOXH_

#include "SDL2\SDL.h"
#include "SDL2\SDL_video.h"
#include "CommonGUIUtil.h"

typedef enum mboxpawnpromotionbutton_t {
	BUTTON_OK,
	INFO_NO_SELECTION,
} MBoxInfoButton;

#define OK_BUTTON_CAPTION "Queen"
#define MBOX_INFO_TITLE "Info"
#define MBOX_INFO_ERROR_MESSAGE "Error showing message box"

#define MBOX_INFO_BG_COLOR { 255,   0,   0 }
#define MBOX_INFO_TEXT_COLOR { 0,   255,   0 }
#define MBOX_INFO_BUTTON_BORDER_COLOR { 0,   0,   255 }
#define MBOX_INFO_BUTTON_BG_COLOR { 200,   200,   200}
#define MBOX_INFO_BUTTON_BG_COLOR_SELECTED { 10,   240,   70}

// pawn promotion messages

#define ROCK_PROMOTION_MESSAGE "computer promoted his pawn for a Rock"
#define QUEEN_PROMOTION_MESSAGE "computer promoted his pawn for a Queen"
#define KNIGHT_PROMOTION_MESSAGE "computer promoted his pawn for a Knight"
#define BISHOP_PROMOTION_MESSAGE "computer promoted his pawn for a Bishop"
#define PAWN_PROMOTION_MESSAGE "computer promoted his pawn for a Pawn"


ErrorCode showInfoMessageBox(const char* message);
#endif
