#ifndef COMMONGUIUTIL_H_
#define COMMONGUIUTIL_H_
#include "SDL2\SDL_video.h"
#include "Commands.h"

// redraw states
#define REDRAW_NEEDED 1
#define REDRAW_NOT_NEEDED 0

// SDL error codes
#define SDL_ERROR -1
#define SDL_OK 0


// MAIN_GUI CONSTS
#define INVALID_LOCATION -1
#define MAIN_BUTTON_X_POS 75
#define MAIN_BUTTON_HEIGHT 100
#define MAIN_BUTTON_WIDTH 250
#define MAIN_BUTTON_SPACING 30
#define MAIN_NUMBER_OF_BUTTONS 3
#define MAIN_WINDOW_WIDTH 800
#define MAIN_WINDOW_HEIGHT 600
#define MAIN_WINDOW_BGCOLOR_RED 245
#define MAIN_WINDOW_BGCOLOR_GREEN 230
#define MAIN_WINDOW_BGCOLOR_BLUE 0
#define MAIN_WINDOW_BGCOLOR_ALPHA 255
#define MAIN_WINDOW_TITLE "ChessProg"

#define NEW_GAME_BUTTON_INDEX 0
#define LOAD_GAME_BUTTON_INDEX 1
#define EXIT_BUTTON_INDEX 2

// board window GUI consts
#define BOARD_WINDOW_WIDTH 800
#define BOARD_WINDOW_HEIGHT 600
#define BOARD_WINDOW_BUTTON_HEIGHT 60
#define BOARD_WINDOW_BUTTON_WIDTH 120
#define BOARD_WINDOW_BUTTON_SPACING 15

#define BOARD_STATUS_BUTTON_Y_POS ((BOARD_ROWS_AMOUNT) * SOLDIER_BUTTON_IMAGE_HEIGHT)
#define BOARD_STATUS_BUTTON_X_POS 50
#define BOARD_STATUS_BUTTON_HEIGHT 100
#define BOARD_STATUS_BUTTON_WIDTH 600

#define BOARD_WINDOW_RESTART_BUTTON_INDEX 0
#define BOARD_WINDOW_SAVE_GAME_BUTTON_INDEX 1
#define BOARD_WINDOW_LOAD_GAME_BUTTON_INDEX 2
#define BOARD_WINDOW_UNDO_BUTTON_INDEX 3
#define BOARD_WINDOW_MAIN_MENU_GAME_BUTTON_INDEX 4
#define BOARD_WINDOW_EXIT_BUTTON_INDEX 5

#define BOARD_WINDOW_BUTTONS_AMOUNT 6
#define BOARD_WINDOW_ROWS_AMOUNT 8
#define BOARD_WINDOW_COLUMNS_AMOUNT 8

#define BOARD_WINDOW_BGCOLOR_RED 200
#define BOARD_WINDOW_BGCOLOR_GREEN 140
#define BOARD_WINDOW_BGCOLOR_BLUE 0
#define BOARD_WINDOW_BGCOLOR_ALPHA 255


// load window GUI consts
#define LOAD_GAME_WINDOW_WIDTH 800
#define LOAD_GAME_WINDOW_HEIGHT 600
#define LOAD_GAME_NAVIGTION_PANE_Y_POS 400
#define LOAD_GAME_WINDOW_BUTTON_HEIGHT 50
#define LOAD_GAME_WINDOW_BUTTON_WIDTH 120
#define LOAD_GAME_WINDOW_BUTTON_SPACING 10

#define LOAD_GAME_WINDOW_SLOT_1_BUTTON_INDEX 0
#define LOAD_GAME_WINDOW_SLOT_2_BUTTON_INDEX 1
#define LOAD_GAME_WINDOW_SLOT_3_BUTTON_INDEX 2
#define LOAD_GAME_WINDOW_SLOT_4_BUTTON_INDEX 3
#define LOAD_GAME_WINDOW_SLOT_5_MENU_GAME_BUTTON_INDEX 4
#define LOAD_GAME_WINDOW_BACK_BUTTON_INDEX 0
#define LOAD_GAME_WINDOW_LOAD_BUTTON_INDEX 1

#define LOAD_GAME_WINDOW_BUTTONS_AMOUNT 7
#define LOAD_GAME_WINDOW_SLOTS_AMOUNT MAX_SLOTS
#define LOAD_GAME_WINDOW_NAVIGATIONS_AMOUNT 2

#define LOAD_GAME_WINDOW_BGCOLOR_RED 100
#define LOAD_GAME_WINDOW_BGCOLOR_GREEN 0
#define LOAD_GAME_WINDOW_BGCOLOR_BLUE 100
#define LOAD_GAME_WINDOW_BGCOLOR_ALPHA 255


// difficulty window GUI consts
#define DIFFICULTY_SELECTION_WINDOW_WIDTH 800
#define DIFFICULTY_SELECTION_WINDOW_HEIGHT 600
#define DIFFICULTY_SELECTION_NAVIGTION_PANE_Y_POS 400
#define DIFFICULTY_SELECTION_WINDOW_BUTTON_HEIGHT 50
#define DIFFICULTY_SELECTION_WINDOW_BUTTON_WIDTH 120
#define DIFFICULTY_SELECTION_WINDOW_BUTTON_SPACING 10

#define DIFFICULTY_SELECTION_WINDOW_NOOB_BUTTON_INDEX 0
#define DIFFICULTY_SELECTION_WINDOW_EASY_BUTTON_INDEX 1
#define DIFFICULTY_SELECTION_WINDOW_MODERATE_BUTTON_INDEX 2
#define DIFFICULTY_SELECTION_WINDOW_HARD_BUTTON_INDEX 3
#define DIFFICULTY_SELECTION_WINDOW_EXPERT_BUTTON_INDEX 4
#define DIFFICULTY_SELECTION_WINDOW_BACK_BUTTON_INDEX 0
#define DIFFICULTY_SELECTION_WINDOW_NEXT_BUTTON_INDEX 1

#define DIFFICULTY_SELECTION_WINDOW_BUTTONS_AMOUNT 7
#define DIFFICULTY_SELECTION_WINDOW_DIFFICULTIES_AMOUNT 5
#define DIFFICULTY_SELECTION_WINDOW_NAVIGATIONS_AMOUNT 2

#define DIFFICULTY_SELECTION_WINDOW_BGCOLOR_RED 255
#define DIFFICULTY_SELECTION_WINDOW_BGCOLOR_GREEN 255
#define DIFFICULTY_SELECTION_WINDOW_BGCOLOR_BLUE 255
#define DIFFICULTY_SELECTION_WINDOW_BGCOLOR_ALPHA 255


// color window GUI consts
#define COLOR_SELECTION_WINDOW_WIDTH 800
#define COLOR_SELECTION_WINDOW_HEIGHT 600
#define COLOR_SELECTION_WINDOW_BUTTON_HEIGHT 120
#define COLOR_SELECTION_WINDOW_BUTTON_WIDTH 120
#define COLOR_SELECTION_NAVIGTION_PANE_Y_POS 450
#define COLOR_SELECTION_WINDOW_BUTTON_SPACING 10

#define COLOR_SELECTION_WINDOW_WHITE_BUTTON_INDEX 0
#define COLOR_SELECTION_WINDOW_BLACK_BUTTON_INDEX 1
#define COLOR_SELECTION_WINDOW_BACK_BUTTON_INDEX 0
#define COLOR_SELECTION_WINDOW_START_BUTTON_INDEX 1

#define COLOR_SELECTION_WINDOW_BUTTONS_AMOUNT 4
#define COLOR_SELECTION_WINDOW_COLORS_AMOUNT 2
#define COLOR_SELECTION_WINDOW_NAVIGATIONS_AMOUNT 2

#define COLOR_SELECTION_WINDOW_BGCOLOR_RED 0
#define COLOR_SELECTION_WINDOW_BGCOLOR_GREEN 100
#define COLOR_SELECTION_WINDOW_BGCOLOR_BLUE 100
#define COLOR_SELECTION_WINDOW_BGCOLOR_ALPHA 255


// mode window GUI consts
#define MODE_SELECTION_WINDOW_WIDTH 800
#define MODE_SELECTION_WINDOW_HEIGHT 600
#define MODE_SELECTION_NAVIGTION_PANE_Y_POS 450
#define MODE_SELECTION_WINDOW_BUTTON_HEIGHT 80
#define MODE_SELECTION_WINDOW_BUTTON_WIDTH 150
#define MODE_SELECTION_WINDOW_BUTTON_SPACING 15

#define MODE_SELECTION_WINDOW_SINGLE_PALYER_BUTTON_INDEX 0
#define MODE_SELECTION_WINDOW_TWO_PLAYERS_INDEX 1
#define MODE_SELECTION_WINDOW_BACK_BUTTON_INDEX 0
#define MODE_SELECTION_WINDOW_NEXT_BUTTON_INDEX 1

#define MODE_SELECTION_WINDOW_BUTTONS_AMOUNT 4
#define MODE_SELECTION_WINDOW_MODES_AMOUNT 2
#define MODE_SELECTION_WINDOW_NAVIGATIONS_AMOUNT 2

#define MODE_SELECTION_WINDOW_BGCOLOR_RED 250
#define MODE_SELECTION_WINDOW_BGCOLOR_GREEN 200
#define MODE_SELECTION_WINDOW_BGCOLOR_BLUE 0
#define MODE_SELECTION_WINDOW_BGCOLOR_ALPHA 255


// soldier button GUI consts
#define SOLDIER_BUTTON_IMAGE_HEIGHT 60
#define SOLDIER_BUTTON_IMAGE_WIDTH 60

#define SOLDIER_COLOR_WHITE 'w'
#define SOLDIER_COLOR_BLACK 'b'
#define SOLDIER_COLOR_EMPTY 'n'

#define SOLDIER_BUTTON_IMAGE_PATH_PREPOSTFIX_LENGTH 34

#define SOLDIER_BUTTON_HIGHLIGHTED 's'
#define SOLDIER_BUTTON_NOT_HIGHLIGHTED 'n'

//saved games paths
#define SAVED_GAMES_DIRECTORY_PATH "./SavedGames/"

// image paths
#define NEW_GAME_PIC_PATH "./pics/MainWindow/newgame.bmp"
#define LOAD_GAME_PIC_PATH "./pics/MainWindow/loadgame.bmp"
#define EXIT_PIC_PATH "./pics/MainWindow/exit.bmp"
#define SOLDIER_PICS_PATTERN "./pics/BoardView/soldiers/%c%c%c%c.BMP"

#define BOARD_WINDOW_RESTART_BUTTON_PIC_PATH "./pics/BoardView/restart.bmp"
#define BOARD_WINDOW_SAVE_GAME_BUTTON_PIC_PATH "./pics/BoardView/save.bmp"
#define BOARD_WINDOW_LOAD_GAME_BUTTON_PIC_PATH "./pics/BoardView/load.bmp"
#define BOARD_WINDOW_UNDO_BUTTON_PIC_PATH "./pics/BoardView/undo.bmp"
#define BOARD_WINDOW_MAIN_MENU_GAME_BUTTON_PIC_PATH "./pics/BoardView/mainmenu.bmp"
#define BOARD_WINDOW_EXIT_BUTTON_PIC_PATH "./pics/BoardView/exitboard.bmp"

#define BOARD_WINDOW_STATUS_NEUTRAL_BUTTON_PIC_PATH "./pics/BoardView/statuses/neutral.bmp"
#define BOARD_WINDOW_STATUS_TIE_BUTTON_PIC_PATH "./pics/BoardView/statuses/tie.bmp"
#define BOARD_WINDOW_STATUS_CHECK_BUTTON_PIC_PATH "./pics/BoardView/statuses/check.bmp"
#define BOARD_WINDOW_STATUS_CHECKMATE_BUTTON_PIC_PATH "./pics/BoardView/statuses/checkmate.bmp"
#define BOARD_WINDOW_STATUS_PAWN_PROMOTION_BUTTON_PIC_PATH "./pics/BoardView/statuses/compp.bmp"
#define BOARD_WINDOW_STATUS_KNIGHT_PROMOTION_BUTTON_PIC_PATH "./pics/BoardView/statuses/compk.bmp"
#define BOARD_WINDOW_STATUS_QUEEN_PROMOTION_BUTTON_PIC_PATH "./pics/BoardView/statuses/compq.bmp"
#define BOARD_WINDOW_STATUS_BISHOP_PROMOTION_BUTTON_PIC_PATH "./pics/BoardView/statuses/compb.bmp"
#define BOARD_WINDOW_STATUS_ROCK_PROMOTION_BUTTON_PIC_PATH "./pics/BoardView/statuses/compr.bmp"


#define LOAD_GAME_WINDOW_SLOT_BUTTON_PIC_PATH "./pics/loadGameView/%d%c.bmp"
#define LOAD_GAME_WINDOW_LOAD_BUTTON_PIC_PATH "./pics/loadGameView/load.bmp"
#define LOAD_GAME_WINDOW_BACK_BUTTON_PIC_PATH "./pics/loadGameView/back.bmp"
#define LOAD_GAME_WINDOW_PIC_PATH_SLOT_SELECTED 's'
#define LOAD_GAME_WINDOW_PIC_PATH_SLOT_NOT_SELECTED 'n'
#define LOAD_GAME_WINDOW_SLOT__PIC_PATH_LENGTH 27

#define DIFFICULTY_SELECTION_WINDOW_DIFFICULTY_BUTTON_PIC_PATH "./pics/difficultyView/%d%c.bmp"
#define DIFFICULTY_SELECTION_WINDOW_NEXT_BUTTON_PIC_PATH "./pics/difficultyView/next.bmp"
#define DIFFICULTY_SELECTION_WINDOW_BACK_BUTTON_PIC_PATH "./pics/difficultyView/back.bmp"
#define DIFFICULTY_SELECTION_WINDOW_PIC_PATH_SLOT_SELECTED 's'
#define DIFFICULTY_SELECTION_WINDOW_PIC_PATH_SLOT_NOT_SELECTED 'n'
#define DIFFICULTY_SELECTION_WINDOW_DIFF__PIC_PATH_LENGTH 29

#define COLOR_SELECTION_WINDOW_BLACK_BUTTON_NOT_SELECTED_PIC_PATH "./pics/colorView/blackn.bmp"
#define COLOR_SELECTION_WINDOW_WHITE_BUTTON_NOT_SELECTED_PIC_PATH "./pics/colorView/whiten.bmp"
#define COLOR_SELECTION_WINDOW_BLACK_BUTTON_SELECTED_PIC_PATH "./pics/colorView/blacks.bmp"
#define COLOR_SELECTION_WINDOW_WHITE_BUTTON_SELECTED_PIC_PATH "./pics/colorView/whites.bmp"
#define COLOR_SELECTION_WINDOW_BACK_BUTTON_PIC_PATH "./pics/colorView/back.bmp"
#define COLOR_SELECTION_WINDOW_START_BUTTON_PIC_PATH "./pics/colorView/start.bmp"

#define MODE_SELECTION_WINDOW_SINGLE_PLAYER_BUTTON_SELECTED_PIC_PATH "./pics/modeView/ones.bmp"
#define MODE_SELECTION_WINDOW_SINGLE_PLAYER_BUTTON_NOT_SELECTED_PIC_PATH "./pics/modeView/onen.bmp"
#define MODE_SELECTION_WINDOW_TWO_PLAYERS_BUTTON_SELECTED_PIC_PATH "./pics/modeView/twos.bmp"
#define MODE_SELECTION_WINDOW_TWO_PLAYERS_BUTTON_NOT_SELECTED_PIC_PATH "./pics/modeView/twon.bmp"
#define MODE_SELECTION_WINDOW_BACK_BUTTON_PIC_PATH "./pics/modeView/back.bmp"
#define MODE_SELECTION_WINDOW_NEXT_BUTTON_PIC_PATH "./pics/modeView/next.bmp"
#define MODE_SELECTION_WINDOW_START_BUTTON_PIC_PATH "./pics/modeView/start.bmp"

#define BMP_FILE_TYPE ".bmp"
#define DISABLED_BUTTON_CHAR 'd'


// masks to get status out of the INT enum
#define GAME_RESULT_STATUS_BITMASK 0x000F
#define PROMOTION_STATUS_BITMASK 0xFFF0
/*
 * The function makes deep copy of a rectangle
 */
SDL_Rect* copyRect(SDL_Rect* src);
/*
 * The function creates a stub invalid rectangle
 */
SDL_Rect* createInvlidRect();
/*
 * the function is a utility to check if given char is lower case
 */
SDL_bool isCharLoweCase(char c);

/*
 * the function converts difficulty button index to DifficutyLevel enum
 */
DifficultyLevel getDifficulty(int difficultyButtonIndex);

/*
 * the function converts mode button index to GameMode enum
 */
GameMode getMode(int modeButtonIndex);

/*
 * the function converts color button index to UserColor enum
 */
UserColor getColor(int colorButtonIndex);


#endif
