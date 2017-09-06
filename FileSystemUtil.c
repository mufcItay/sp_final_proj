#include <stdlib.h>
#include <stdio.h>
#include "FileSystemUtil.h"
#include "CommonGUIUtil.h"
#include "CommonStructures.h"
#include "Commands.h"
#include <dirent.h>

int getNumberOfSavedGames() {
	DIR *directory;
	struct dirent *file;
	directory = opendir(SAVED_GAMES_DIRECTORY_PATH);
	int numberOfFiles = 0;
	if (directory != NULL) {
		file = readdir(directory);
		while (file != NULL) {
			numberOfFiles++;
			file = readdir(directory);
		}
		closedir(directory);
	} else {
		perror("Couldn't open the directory");
	}
	// 2 files are redundant
	return numberOfFiles - REDUNDANT_FILES_AMOUNT;
}

int saveGame(GameSettings* settings, GameState* state, char* path) {
	FILE* gameFile = fopen(path, "w");
	if (gameFile == NULL) {
		return XML_ERROR;
	}
	if (fprintf(gameFile, XML_TITLE_TAG) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	if (fprintf(gameFile, XML_GAME_TAG) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	int currentTurnXML = (state->turn == BLACK) ? XML_COLOR_BLACK : XML_COLOR_WHITE;
	if (fprintf(gameFile, XML_TURN_TAG, currentTurnXML) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	int currentModeXML = (settings->mode == MULTI_PLAYER) ? XML_COLOR_BLACK : XML_COLOR_WHITE;
	if (fprintf(gameFile, XML_MODE_TAG, currentModeXML) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	if (writeDifficultyToXML(settings, gameFile) == DIFFICULTY_UNDEFINED) {
		fclose(gameFile);
		return XML_ERROR;
	}
	int currentColorXML = (settings->color == BLACK) ? XML_COLOR_BLACK : XML_COLOR_WHITE;
	if (fprintf(gameFile, XML_COLOR_TAG, currentColorXML) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	if (fprintf(gameFile, XML_BOARD_TAG) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	for (int i = BOARD_ROWS_AMOUNT; i > 0; i--) {
		char row[BOARD_COLUMNS_AMOUNT + 1];
		for (int j = 0; j < BOARD_COLUMNS_AMOUNT; ++j) {
			row[j] = state->board[i-1][j];
		}
		row[BOARD_COLUMNS_AMOUNT] = '\0';
		if (fprintf(gameFile, XML_ROW_TAG, i, row, i) <= 0) {
			fclose(gameFile);
			return XML_ERROR;
		}
	}
	if (fprintf(gameFile, XML_BOARD_END_TAG) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	if (fprintf(gameFile, XML_GAME_END_TAG) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	fclose(gameFile);
	return XML_OK;
}

int loadGame(GameSettings* settings, GameState* state, char* path) {
	FILE* gameFile = fopen(path, "r");
	if (gameFile == NULL) {
		return XML_ERROR;
	}
	fscanf(gameFile, XML_TITLE_TAG);
	fscanf(gameFile, XML_GAME_TAG);
	int currentTurnXML = COLOR_UNDEFINED;
	if (fscanf(gameFile, XML_TURN_TAG, &currentTurnXML) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	state->turn = currentTurnXML == XML_COLOR_WHITE ? WHITE : BLACK;
	int currentModeXML = MODE_UNDEFINED;
	if (fscanf(gameFile, XML_MODE_TAG, &currentModeXML) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	settings->mode = (currentModeXML == XML_MODE_MULTIPLAYER) ? MULTI_PLAYER : SINGLE_PLAYER;
	if (updateDifficulty(settings, gameFile) == DIFFICULTY_UNDEFINED) {
		fclose(gameFile);
		return XML_ERROR;
	}
	int currentColorXML = COLOR_UNDEFINED;
	if (fscanf(gameFile, XML_COLOR_TAG, &currentColorXML) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	settings->color = (settings->color == XML_COLOR_BLACK) ? BLACK : WHITE;
	if (fscanf(gameFile, XML_BOARD_TAG) <= 0) {
		fclose(gameFile);
		return XML_ERROR;
	}
	for (int i = BOARD_ROWS_AMOUNT; i > 0; i--) {
		int rowIndex = -1;
		char soldierTypes[BOARD_COLUMNS_AMOUNT + 1];
		if (fscanf(gameFile, XML_ROW_TAG, &rowIndex, soldierTypes, &rowIndex) <= 0) {
			fclose(gameFile);
			return XML_ERROR;
		}
		for (int j = 0; j < BOARD_COLUMNS_AMOUNT; ++j) {
			state->board[rowIndex][j] = soldierTypes[j];
		}
	}
	fscanf(gameFile, XML_BOARD_END_TAG);
	fscanf(gameFile, XML_GAME_END_TAG);
	fclose(gameFile);
	return XML_OK;
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
		return DIFFICULTY_UNDEFINED;
	}

	return currentDifficultyXML;
}

int updateDifficulty(GameSettings* settings, FILE* gameFile) {
	int currentDifficultyXML = DIFFICULTY_UNDEFINED;
	if (fscanf(gameFile, XML_DIFFICULTY_TAG, &currentDifficultyXML) <= 0) {
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
