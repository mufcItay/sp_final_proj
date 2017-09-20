#ifndef PAWNPROMOTIONMESSAGEBOX_H_
#define PAWNPROMOTIONMESSAGEBOX_H_

#include "SDL2\SDL.h"
#include "SDL2\SDL_video.h"
#include "CommonGUIUtil.h"

typedef enum mboxpawnpromotionbutton_t {
	BUTTON_QUEEN,
	BUTTON_KNIGHT,
	BUTTON_ROCK,
	BUTTON_BISHOP,
	BUTTON_PAWN,
	PAWN_NO_SELECTION = -1
} MBoxPawnPromotionButton;

#define QUEEN_BUTTON_CAPTION "Queen"
#define KNIGHT_BUTTON_CAPTION "Knight"
#define ROCK_BUTTON_CAPTION "Rock"
#define BISHOP_BUTTON_CAPTION "Bishop"
#define PAWN_BUTTON_CAPTION "Pawn"
#define MBOX_PAWN_MESSAGE "what is your pawn promotion?"
#define MBOX_PAWN_TITLE "PAWN PROMOTION"
#define MBOX_PAWN_ERROR_MESSAGE "Error showing message box"

#define MBOX_PAWN_BG_COLOR { 255,   0,   0 }
#define MBOX_PAWN_TEXT_COLOR { 0,   255,   0 }
#define MBOX_PAWN_BUTTON_BORDER_COLOR { 0,   0,   255 }
#define MBOX_PAWN_BUTTON_BG_COLOR { 200,   200,   200}
#define MBOX_PAWN_BUTTON_BG_COLOR_SELECTED { 10,   240,   70}


// pawn promotion messages

#define ROCK_PROMOTION_MESSAGE "computer promoted his pawn for a Rock"
#define QUEEN_PROMOTION_MESSAGE "computer promoted his pawn for a Queen"
#define KNIGHT_PROMOTION_MESSAGE "computer promoted his pawn for a Knight"
#define BISHOP_PROMOTION_MESSAGE "computer promoted his pawn for a Bishop"
#define PAWN_PROMOTION_MESSAGE "computer promoted his pawn for a Pawn"


MBoxPawnPromotionButton getUserPawnPromotionDecision();
#endif
