#ifndef COMMONSTRUCTURES_H_
#define COMMONSTRUCTURES_H_
#include "SDL2\SDL.h"

// Error codes enum
typedef enum errorcodes_t {
	SLOTS_LOAD_ERROR = -2,
	SDL_ERROR = -1,
	OK = 0,
	MEMORY_ERROR,
	SAVE_ERROR,
	LOAD_ERROR,
	GENERAL_ERROR,
	NULL_POINTER_ERROR,
	CONTROLLER_END,
	IMAGE_ERROR
} ErrorCode;


#define BMP_FILE_TYPE ".bmp"
#define ERROR_MESSAGE_PREFIX "ERROR: "

#define MAX_SLOTS 5


// default settings values
#define DEFAULT_GAME_MODE 1
#define DEFAULT_DIFFICULTY 2
#define DEFAULT_USER_COLOR 1

// board consts
#define BOARD_ROWS_AMOUNT 8
#define BOARD_COLUMNS_AMOUNT 8

// soldier type consts
#define SOLDIER_TYPE_WHITE_ROCK 'r'
#define SOLDIER_TYPE_WHITE_PAWN 'm'
#define SOLDIER_TYPE_WHITE_QUEEN 'q'
#define SOLDIER_TYPE_WHITE_KING 'k'
#define SOLDIER_TYPE_WHITE_KNIGHT 'n'
#define SOLDIER_TYPE_WHITE_BISHOP 'b'
#define SOLDIER_TYPE_BLACK_ROCK 'R'
#define SOLDIER_TYPE_BLACK_PAWN 'M'
#define SOLDIER_TYPE_BLACK_QUEEN 'Q'
#define SOLDIER_TYPE_BLACK_KING 'K'
#define SOLDIER_TYPE_BLACK_KNIGHT 'N'
#define SOLDIER_TYPE_BLACK_BISHOP 'B'
#define SOLDIER_TYPE_EMPTY '_'

// struct which holds the game sttings
typedef struct gamesettings_t {
	int color;
	int difficulty;
	int mode;
} GameSettings;


// struct which holds the game state
typedef struct gameState_t {
	char** board;
	void** moveHistory;
	int turn;
} GameState;

/*
 * The function creates GameState structure with defualt values
 */
GameState* createGameState();

/*
 * The function creates GameSettings structure with defualt values
 */
GameSettings* createGameSettings();

/*
 * The function frees resources of GameState structure
 */
void destroyGameState(GameState* gameState);

/*
 * The function frees resources of GameSettings structure
 */
void destroyGameSettings(GameSettings* gameSettings);

/*
 * The function creates the initial board
 */
char** createInitialBoard();

/*
 * The function sets default values to GameSettings structure
 */
void setDefaultSettings(GameSettings* settings);

/*
 * the function sets the game state to initial values (inital board, player turn and undo history).
 */
ErrorCode setInitialGameState(GameState* state);

/*
 * the function prints to console given error message.
 */
void printErrorMessage(const char* message);
#endif
