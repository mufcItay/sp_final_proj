#ifndef COMMONSTRUCTURES_H_
#define COMMONSTRUCTURES_H_
#include "SDL2\SDL.h"

// Error codes
#define ERROR 1
#define OK 0

#define BMP_FILE_TYPE ".bmp"

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
 * The function sets defualt values to GameSettings structure
 */
void setDefaultSettings(GameSettings* settings);
#endif
