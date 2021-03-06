#include "FileSystemUtil.h"
#include "CommonGUIUtil.h"
#include "CommonStructures.h"
#include "Commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

int getNumberOfSavedGames() {
	DIR *directory;
	struct dirent *file;
	// open directory
	directory = opendir(SAVED_GAMES_DIRECTORY_PATH);
	if(directory == NULL) {
		printErrorMessage(FILE_SYSTEM_ERROR_MESSAGE);
		return SLOTS_LOAD_ERROR;
	}
	int numberOfFiles = 0;
	if (directory != NULL) {
		// count files
		file = readdir(directory);
		while (file != NULL) {
			numberOfFiles++;
			file = readdir(directory);
		}
		closedir(directory);
	} else {
		printErrorMessage(FILE_SYSTEM_ERROR_MESSAGE);
		return SLOTS_LOAD_ERROR;
	}
	// 2 files are redundant
	numberOfFiles -= REDUNDANT_FILES_AMOUNT;
	if(numberOfFiles > MAX_SLOTS) {
		printErrorMessage(SAVED_GAMES_DIR_CORRUPTED_ERROR_MESSAGE);
		return SLOTS_LOAD_ERROR;
	}
	return numberOfFiles;
}

ErrorCode reArrageSavedGames() {
	int numOfSavedGames = getNumberOfSavedGames();
	if(numOfSavedGames > MAX_SLOTS || numOfSavedGames == SLOTS_LOAD_ERROR) {
		printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
		return SAVE_ERROR;
	}
	// no need to re arrange if no slots are available
	if(numOfSavedGames == 0) {
		return OK;
	}

	if (numOfSavedGames == MAX_SLOTS) {
		// path len is dir path + slot number + xml file type + 1 for /0
		int pathLen = strlen(SAVED_GAMES_DIRECTORY_PATH) + sizeof(char) + strlen(XML_FILE_TYPE) + 1;
		char path[pathLen];
		sprintf(path,SLOT_PATH_FORMAT,SAVED_GAMES_DIRECTORY_PATH,MAX_SLOTS,XML_FILE_TYPE);
		int ret = remove(path);
		if (ret != 0) {
			printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
			return SAVE_ERROR;
		}
		numOfSavedGames--;
	}

	// rename (1->2, ..., 4->5)
	for (int slotIndex = numOfSavedGames; slotIndex > 0; --slotIndex) {
		// path len is dir path + slot number + xml file type + 1 for /0
		int pathLen = strlen(SAVED_GAMES_DIRECTORY_PATH) + sizeof(char) + strlen(XML_FILE_TYPE) + 1;
		char oldName[pathLen];
		char newName[pathLen];
		sprintf(oldName,SLOT_PATH_FORMAT,SAVED_GAMES_DIRECTORY_PATH,slotIndex,XML_FILE_TYPE);
		sprintf(newName,SLOT_PATH_FORMAT,SAVED_GAMES_DIRECTORY_PATH,slotIndex + 1 ,XML_FILE_TYPE);
		int ret = rename(oldName,newName);
		if (ret != 0) {
			printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
			return SAVE_ERROR;
		}
	}
	return OK;
}

ErrorCode saveGame(GameSettings* settings, GameState* state, char* path) {
	// open file
	FILE* gameFile = fopen(path, "w");
	if (gameFile == NULL) {
		printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
		return SAVE_ERROR;
	}
	// start writing tags
	if (fprintf(gameFile, XML_TITLE_TAG) <= 0) {
		fclose(gameFile);
		printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
		return SAVE_ERROR;
	}
	if (fprintf(gameFile, XML_GAME_TAG) <= 0) {
		fclose(gameFile);
		printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
		return SAVE_ERROR;
	}
	int currentTurnXML = (state->turn == BLACK) ? XML_COLOR_BLACK : XML_COLOR_WHITE;
	if (fprintf(gameFile, XML_TURN_TAG, currentTurnXML) <= 0) {
		fclose(gameFile);
		printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
		return SAVE_ERROR;
	}
	int currentModeXML = (settings->mode == MULTI_PLAYER) ? XML_MODE_MULTIPLAYER : XML_MODE_SINGLE_PLAYER;
	if (fprintf(gameFile, XML_MODE_TAG, currentModeXML) <= 0) {
		fclose(gameFile);
		printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
		return SAVE_ERROR;
	}
	// save difficulty and color only for single player game
	if(settings->mode == SINGLE_PLAYER) {
		if (writeDifficultyToXML(settings, gameFile) == DIFFICULTY_UNDEFINED) {
			fclose(gameFile);
			printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
			return SAVE_ERROR;
		}
		int currentColorXML = (settings->color == BLACK) ? XML_COLOR_BLACK : XML_COLOR_WHITE;
		if (fprintf(gameFile, XML_COLOR_TAG, currentColorXML) <= 0) {
			fclose(gameFile);
			printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
			return SAVE_ERROR;
		}
	}
	if (fprintf(gameFile, XML_BOARD_TAG) <= 0) {
		fclose(gameFile);
		printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
		return SAVE_ERROR;
	}
	// write the board
	for (int i = BOARD_ROWS_AMOUNT; i > 0; i--) {
		// create a char[] for each line in board
		char row[BOARD_COLUMNS_AMOUNT + 1];
		for (int j = 0; j < BOARD_COLUMNS_AMOUNT; ++j) {
			row[j] = state->board[i-1][j];
		}
		row[BOARD_COLUMNS_AMOUNT] = '\0';
		// write the whole line to file
		if (fprintf(gameFile, XML_ROW_TAG, i, row, i) <= 0) {
			fclose(gameFile);
			printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
			return SAVE_ERROR;
		}
	}
	if (fprintf(gameFile, XML_BOARD_END_TAG) <= 0) {
		fclose(gameFile);
		printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
		return SAVE_ERROR;
	}
	if (fprintf(gameFile, XML_GAME_END_TAG) <= 0) {
		fclose(gameFile);
		printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
		return SAVE_ERROR;
	}
	fclose(gameFile);
	return OK;
}

ErrorCode loadGame(GameSettings* settings, GameState* state, char* path) {
	// open the xml file
	FILE* gameFile = fopen(path, "r");
	if (gameFile == NULL) {
		printErrorMessage(LOAD_GAME_ERROR_MESSAGE);
		return LOAD_ERROR;
	}
	// read tags
	fscanf(gameFile, XML_TITLE_TAG);
	fscanf(gameFile, XML_GAME_TAG);
	int currentTurnXML = COLOR_UNDEFINED;
	if (fscanf(gameFile, XML_TURN_TAG, &currentTurnXML) <= 0 || isTurnValid(currentTurnXML) == INVALID_ARGUMENT) {
		fclose(gameFile);
		printErrorMessage(LOAD_GAME_ERROR_MESSAGE);
		return LOAD_ERROR;
	}

	state->turn = currentTurnXML == XML_COLOR_WHITE ? WHITE : BLACK;
	int currentModeXML = MODE_UNDEFINED;
	if (fscanf(gameFile, XML_MODE_TAG, &currentModeXML) <= 0 || isModeValid(currentModeXML) == INVALID_ARGUMENT) {
		fclose(gameFile);
		printErrorMessage(LOAD_GAME_ERROR_MESSAGE);
		return LOAD_ERROR;
	}
	settings->mode = (currentModeXML == XML_MODE_MULTIPLAYER) ? MULTI_PLAYER : SINGLE_PLAYER;

	if(settings->mode == SINGLE_PLAYER) {
		if (updateDifficulty(settings, gameFile) == DIFFICULTY_UNDEFINED || isDifficultyValid(settings->difficulty) == INVALID_ARGUMENT) {
			fclose(gameFile);
			printErrorMessage(LOAD_GAME_ERROR_MESSAGE);
			return LOAD_ERROR;
		}
		int currentColorXML = COLOR_UNDEFINED;
		if (fscanf(gameFile, XML_COLOR_TAG, &currentColorXML) <= 0 || isColorValid(currentColorXML) == INVALID_ARGUMENT) {
			fclose(gameFile);
			printErrorMessage(LOAD_GAME_ERROR_MESSAGE);
			return LOAD_ERROR;
		}
		settings->color = (settings->color == XML_COLOR_BLACK) ? BLACK : WHITE;
	}
	fscanf(gameFile, XML_BOARD_TAG);
	// parse board tag
	for (int i = BOARD_ROWS_AMOUNT; i > 0; i--) {
		int rowIndex = -1;
		// read line by line and fill the board
		char soldierTypes[BOARD_COLUMNS_AMOUNT];
		int temp = 0;
		if (fscanf(gameFile, XML_ROW_TAG, &rowIndex, soldierTypes, &temp) <= 0) {
			fclose(gameFile);
			printErrorMessage(LOAD_GAME_ERROR_MESSAGE);
			return LOAD_ERROR;
		}
		for (int j = 0; j < BOARD_COLUMNS_AMOUNT; ++j) {
			if(isSoldierValid(soldierTypes[j]) == INVALID_ARGUMENT) {
				fclose(gameFile);
				printErrorMessage(LOAD_GAME_ERROR_MESSAGE);
				return LOAD_ERROR;
			}
			state->board[i-1][j] = soldierTypes[j];
		}
	}
	fscanf(gameFile, XML_BOARD_END_TAG);
	fscanf(gameFile, XML_GAME_END_TAG);
	fclose(gameFile);
	return OK;
}

int writeDifficultyToXML(GameSettings* settings, FILE* gameFile) {
	int currentDifficultyXML = DIFFICULTY_UNDEFINED;
	switch (settings->difficulty) {
	case NOOB:
		currentDifficultyXML = XML_DIFFICULTY_NOOB;
		break;
	case EASY:
		currentDifficultyXML = XML_DIFFICULTY_EASY;
		break;
	case MODERATE:
		currentDifficultyXML = XML_DIFFICULTY_MODERATE;
		break;
	case HARD:
		currentDifficultyXML = XML_DIFFICULTY_HARD;
		break;
	case EXPERT:
		currentDifficultyXML = XML_DIFFICULTY_EXPERT;
		break;
	default:
		return DIFFICULTY_UNDEFINED;
	}
	if (fprintf(gameFile, XML_DIFFICULTY_TAG, currentDifficultyXML) <= 0) {
		printErrorMessage(STRING_ERROR_MESSAGE);
		return DIFFICULTY_UNDEFINED;
	}

	return currentDifficultyXML;
}

int updateDifficulty(GameSettings* settings, FILE* gameFile) {
	int currentDifficultyXML = DIFFICULTY_UNDEFINED;
	if (fscanf(gameFile, XML_DIFFICULTY_TAG, &currentDifficultyXML) <= 0) {
		printErrorMessage(LOAD_GAME_ERROR_MESSAGE);
		return DIFFICULTY_UNDEFINED;
	}
	switch (currentDifficultyXML) {
	case XML_DIFFICULTY_NOOB:
		settings->difficulty = NOOB;
		break;
	case XML_DIFFICULTY_EASY:
		settings->difficulty = EASY;
		break;
	case XML_DIFFICULTY_MODERATE:
		settings->difficulty = MODERATE;
		break;
	case XML_DIFFICULTY_HARD:
		settings->difficulty = HARD;
		break;
	case XML_DIFFICULTY_EXPERT:
		settings->difficulty = EXPERT;
		break;
	default:
		return DIFFICULTY_UNDEFINED;
	}

	return settings->difficulty;
}

ErrorCode isDifficultyValid(int difficulty){
	if(difficulty == EXPERT) {
		printErrorMessage(EXPERT_DIFFICULTY_NOT_SUPPORTED_MESSAGE);
		return INVALID_ARGUMENT;
	}
	if(difficulty < NOOB || difficulty > HARD) {
		printErrorMessage(INVALID_ARGUMENT_LOAD_MESSAGE);
		return INVALID_ARGUMENT;
	}
	return OK;
}
ErrorCode isTurnValid(int turn){
	if(turn != BLACK && turn != WHITE) {
		printErrorMessage(INVALID_ARGUMENT_LOAD_MESSAGE);
		return INVALID_ARGUMENT;
	}
	return OK;
}
ErrorCode isColorValid(int color){
	if(color != BLACK && color != WHITE) {
		printErrorMessage(INVALID_ARGUMENT_LOAD_MESSAGE);
		return INVALID_ARGUMENT;
	}
	return OK;
}
ErrorCode isModeValid(int mode){
	if(mode != MULTI_PLAYER && mode != SINGLE_PLAYER) {
		printErrorMessage(INVALID_ARGUMENT_LOAD_MESSAGE);
		return INVALID_ARGUMENT;
	}
	return OK;
}
ErrorCode isSoldierValid(char soldier){
	int res = 0;
	if(soldier != SOLDIER_TYPE_EMPTY) {
		soldier = toLowerCase(soldier);
	}
	res |= soldier == SOLDIER_TYPE_EMPTY;
	res |= soldier == SOLDIER_TYPE_WHITE_PAWN;
	res |= soldier == SOLDIER_TYPE_WHITE_BISHOP;
	res |= soldier == SOLDIER_TYPE_WHITE_KNIGHT;
	res |= soldier == SOLDIER_TYPE_WHITE_ROCK;
	res |= soldier == SOLDIER_TYPE_WHITE_QUEEN;
	res |= soldier == SOLDIER_TYPE_WHITE_KING;
	if(res == 0) {
		printErrorMessage(INVALID_ARGUMENT_LOAD_MESSAGE);
		return INVALID_ARGUMENT;
	}
	return OK;
}

