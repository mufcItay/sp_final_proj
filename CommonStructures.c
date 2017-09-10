#include "CommonStructures.h"
#include "Commands.h"


GameState* createGameState(){
	GameState* state = (GameState*) malloc(sizeof(char**) + sizeof(int) + sizeof(void**));
	state->board = createInitialBoard();
	state->turn = WHITE;
	return state;

}

GameSettings* createGameSettings(){
	GameSettings* settings = (GameSettings*) malloc(sizeof(GameSettings));

	setDefaultSettings(settings);
	return settings;
}

void setDefaultSettings(GameSettings* settings) {
	settings->mode =  DEFAULT_GAME_MODE;
	settings->difficulty=  DEFAULT_DIFFICULTY;
	settings->color=  DEFAULT_USER_COLOR;
}



void destroyGameState(GameState* gameState) {
	for (int i = 0; i < BOARD_ROWS_AMOUNT; ++i) {
		free(gameState->board[i]);
	}
	free(gameState->board);
	//free(gameState->moveHistory);
	free(gameState);
}

void destroyGameSettings(GameSettings* gameSettings) {
	free(gameSettings);
}

char** createInitialBoard()
{
	char ** board = malloc(sizeof(char*) * BOARD_ROWS_AMOUNT);
	for(int i =0; i< BOARD_ROWS_AMOUNT;++i)
	{
		board[i] = (char*) malloc(sizeof(char) * BOARD_COLUMNS_AMOUNT);
	}

	board[0][0]=SOLDIER_TYPE_BLACK_ROCK; board[0][1]=SOLDIER_TYPE_BLACK_KNIGHT;board[0][2]=SOLDIER_TYPE_BLACK_BISHOP;board[0][3]=SOLDIER_TYPE_BLACK_QUEEN; board[0][4]=SOLDIER_TYPE_BLACK_KING;board[0][5]=SOLDIER_TYPE_BLACK_BISHOP;board[0][6]=SOLDIER_TYPE_BLACK_KNIGHT;board[0][7]=SOLDIER_TYPE_BLACK_ROCK;
	board[1][0]=SOLDIER_TYPE_BLACK_PAWN; board[1][1]=SOLDIER_TYPE_BLACK_PAWN;board[1][2]=SOLDIER_TYPE_BLACK_PAWN;board[1][3]=SOLDIER_TYPE_BLACK_PAWN; board[1][4]=SOLDIER_TYPE_BLACK_PAWN;board[1][5]=SOLDIER_TYPE_BLACK_PAWN;board[1][6]=SOLDIER_TYPE_BLACK_PAWN;board[1][7]=SOLDIER_TYPE_BLACK_PAWN;
	board[2][0]=SOLDIER_TYPE_EMPTY; board[2][1]=SOLDIER_TYPE_EMPTY;board[2][2]=SOLDIER_TYPE_EMPTY;board[2][3]=SOLDIER_TYPE_EMPTY; board[2][4]=SOLDIER_TYPE_EMPTY;board[2][5]=SOLDIER_TYPE_EMPTY;board[2][6]=SOLDIER_TYPE_EMPTY;board[2][7]=SOLDIER_TYPE_EMPTY;
	board[3][0]=SOLDIER_TYPE_EMPTY; board[3][1]=SOLDIER_TYPE_EMPTY;board[3][2]=SOLDIER_TYPE_EMPTY;board[3][3]=SOLDIER_TYPE_EMPTY; board[3][4]=SOLDIER_TYPE_EMPTY;board[3][5]=SOLDIER_TYPE_EMPTY;board[3][6]=SOLDIER_TYPE_EMPTY;board[3][7]=SOLDIER_TYPE_EMPTY;
	board[4][0]=SOLDIER_TYPE_EMPTY; board[4][1]=SOLDIER_TYPE_EMPTY;board[4][2]=SOLDIER_TYPE_EMPTY;board[4][3]=SOLDIER_TYPE_EMPTY; board[4][4]=SOLDIER_TYPE_EMPTY;board[4][5]=SOLDIER_TYPE_EMPTY;board[4][6]=SOLDIER_TYPE_EMPTY;board[4][7]=SOLDIER_TYPE_EMPTY;
	board[5][0]=SOLDIER_TYPE_EMPTY; board[5][1]=SOLDIER_TYPE_EMPTY;board[5][2]=SOLDIER_TYPE_EMPTY;board[5][3]=SOLDIER_TYPE_EMPTY; board[5][4]=SOLDIER_TYPE_EMPTY;board[5][5]=SOLDIER_TYPE_EMPTY;board[5][6]=SOLDIER_TYPE_EMPTY;board[5][7]=SOLDIER_TYPE_EMPTY;
	board[6][0]=SOLDIER_TYPE_WHITE_PAWN; board[6][1]=SOLDIER_TYPE_WHITE_PAWN;board[6][2]=SOLDIER_TYPE_WHITE_PAWN;board[6][3]=SOLDIER_TYPE_WHITE_PAWN; board[6][4]=SOLDIER_TYPE_WHITE_PAWN;board[6][5]=SOLDIER_TYPE_WHITE_PAWN;board[6][6]=SOLDIER_TYPE_WHITE_PAWN;board[6][7]=SOLDIER_TYPE_WHITE_PAWN;
	board[7][0]=SOLDIER_TYPE_WHITE_ROCK; board[7][1]=SOLDIER_TYPE_WHITE_KNIGHT;board[7][2]=SOLDIER_TYPE_WHITE_BISHOP;board[7][3]=SOLDIER_TYPE_WHITE_QUEEN; board[7][4]=SOLDIER_TYPE_WHITE_KING;board[7][5]=SOLDIER_TYPE_WHITE_BISHOP;board[7][6]=SOLDIER_TYPE_WHITE_KNIGHT;board[7][7]=SOLDIER_TYPE_WHITE_ROCK;

	return board;
}
