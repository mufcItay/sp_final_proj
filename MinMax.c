#include <stdlib.h>
#include <stdio.h>
#include "MinMax.h"
#include "CommonStructures.h"
#include "Commands.h"


void minMaxNodeDestroy(MinMaxNode* node) {
    if(node != NULL) {
        if(node->gameState != NULL) {
            destroyGameState(node->gameState);
        }
        if(node->moveCmd != NULL) {
        	destroyMoveCommand((Command*)node->moveCmd);
        }
        free(node);
    }
}

int min(int x, int y) {
    if (x < y) {
        return x;
    }
    return y;
}


MoveCommand* getBestMove(GameState* state, GameSettings* settings) {
	MoveCommand* suggestedMove = NULL;
	MinMaxNode *currentNode = malloc(sizeof(MinMaxNode));
    if (currentNode == NULL) {
        printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
        return NULL;
    }
    currentNode->gameState = copyGameState(state);
    if(currentNode->gameState == NULL) {
    	return NULL;
    }

    if (currentNode->gameState->board != NULL) {
        // wait for recursive tree build. at the end current node will get suggested move's column index
        ErrorCode res = buildMinMaxTree(settings, currentNode, settings->difficulty, 0);
        if (res != OK) {
            minMaxNodeDestroy(currentNode);
            return NULL;
        }
        suggestedMove = (MoveCommand*) createMoveCommand(currentNode->moveCmd->originPoint, currentNode->moveCmd->destinationPoint);
    }

    minMaxNodeDestroy(currentNode);

    return suggestedMove;
}

void destroyPossibleCommandsArray(int possibleCommandsAmount,
		MoveCommand** possibleComands) {
	// free resources of possible commands
	for (int cmdIndex = 0; cmdIndex < possibleCommandsAmount; ++cmdIndex) {
		if (possibleComands[cmdIndex] != NULL) {
			free(possibleComands[cmdIndex]);
		}
	}
	free(possibleComands);
}

ErrorCode buildMinMaxTree(GameSettings* settings, MinMaxNode *currentNode, unsigned int maxDepth, unsigned int currentDepth) {
	ErrorCode err = OK;
	// if there it is the final step of building the tree, max depth was reached
    if (maxDepth == currentDepth) {
        currentNode->score = getBoardScore(currentNode->gameState);
        return err;
    }
    int maxScore = INT_MIN;
    MoveCommand* maxCmd = NULL;
    int minScore = INT_MAX;
    MoveCommand* minCmd = NULL;

    int possibleCommandsAmount;
    for(int rowIndex = 0; rowIndex< BOARD_ROWS_AMOUNT; ++rowIndex) {
    	for(int colIndex = 0; colIndex< BOARD_COLUMNS_AMOUNT; ++colIndex) {
			// check all possible moves
    		MoveCommand** possibleComands = getValidCommands(rowIndex, colIndex, currentNode->gameState,&possibleCommandsAmount);
			for(int cmdIndex = 0; cmdIndex < possibleCommandsAmount;++cmdIndex) {
				MinMaxNode *childNode = malloc(sizeof(MinMaxNode));
				if (childNode == NULL) {
					printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
					return MEMORY_ERROR;
				}
				//create a childNode with a copy of the game
				childNode->gameState = copyGameState(currentNode->gameState);
				if (childNode->gameState== NULL) {
					minMaxNodeDestroy(childNode);
					printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
					return MEMORY_ERROR;
				}

				MoveCommand* cmd = possibleComands[cmdIndex];
				err = handleMoveCommand((Command*) cmd,settings, childNode->gameState);
				if(err != OK) {
					return err;
				}
				// check if there is a winner.
				GameBoardStatuses status = getGameStatus(childNode->gameState);
				if (status != NEUTRAL) {
					// if the game is over, we don't need to check anymore moves - its redundant.
					childNode->score = getBoardScore(childNode->gameState);
					childNode->moveCmd = cmd;
				} else {
					// if after the step we made the game continues, we continue building the tree
					buildMinMaxTree(settings, childNode, maxDepth, currentDepth + 1);
				}

				// collect the minimal and maximal scores of future moves to decide between them
				if (childNode->score < minScore) {
					minScore = childNode->score;
					minCmd = cmd;
				}
				if (childNode->score > maxScore) {
					maxScore = childNode->score;
					maxCmd = cmd;
				}
				// clear memory of child node after checking how it's move affects the score
				minMaxNodeDestroy(childNode);
			}
			if(possibleComands != NULL) {
			// free resources of possible commands
			destroyPossibleCommandsArray(possibleCommandsAmount,
					possibleComands);
			}
    	}
    }
    // according to the current player turn decide to take minimal child node score or maximal.
    updateScoreAndCmd(currentNode, maxScore, maxCmd, minScore, minCmd);
    return OK;
}

int getBoardScore(GameState* gameState) {
	return 0;
}



void updateScoreAndCmd(MinMaxNode *currentNode, int maxScore, MoveCommand* maxCmd, int minScore, MoveCommand* minCmd) {
    if (currentNode->gameState->turn == WHITE) {
        if (maxCmd != NULL) {
            currentNode->score = maxScore;
            currentNode->moveCmd = maxCmd;
        } else {
            currentNode->score = minScore;
            currentNode->moveCmd = minCmd;
        }
    } else {
        if (minCmd != NULL) {
            currentNode->score = minScore;
            currentNode->moveCmd = minCmd;
        } else {
            currentNode->score = maxScore;
            currentNode->moveCmd = maxCmd;
        }
    }
}
