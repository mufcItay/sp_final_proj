#ifndef MINMAX_H_
#define MINMAX_H_
#include <stdlib.h>
#include <stdio.h>
#include "CommonStructures.h"
#include "Commands.h"

/*
 * struct that holds data for a min max tree node to calculate suggested move in the chess game
 */
typedef struct min_max_node_t {
    MoveCommand* moveCmd;
    int score;
    GameState* gameState;
} MinMaxNode;

/**
 * Frees all memory allocation associated with a given node. If ndoe==NULL
 * the function does nothing.
 *
 * @param node - the node to delete
 */
void minMaxNodeDestroy(MinMaxNode* node);

/*
 * The function returns the best move command a
 */
MoveCommand* getBestMove(GameState* state, GameSettings* settings);

/**
 * recursive function that starts from current game state and build a tree of all possible ontinue turns,
 * such that the calue of each game state is evaluated by the coring function in a way that will maximize the score
 * of next move. when the function returns "currentNode" will get a column index for the suggested move.
 * @param currentNode - the node containing current game state
 * @param maxDepth - The maximum depth of the miniMax algorithm
 * @param currentDepth - the current depth in the building tree process (the function is recursive and will finallly reach currentDepth = maxDepth)
 * @return
 * UNDEFINED VALUE  if  malloc has failed.
 * On success the function returns a number between [0,SP_FIAR_GAME_N_COLUMNS -1]
 * which is the best move for the current player.
 */
ErrorCode buildMinMaxTree(GameSettings* settings, MinMaxNode *currentNode, unsigned int maxDepth, unsigned int currentDepth);

/**
 * Given a game state, this function calculates the score current board
 *
 * @param game state - The current game state
 * @return the score of current board
 */
int getBoardScore(GameState* gameState);

/*
 * the functino calculates the minimum out of two values
 */
int min(int x, int y);


/*
 * the function updates min and max indicators while building min max tree
 */
void updateScoreAndCmd(MinMaxNode *currentNode, int maxScore, MoveCommand* maxCmd, int minScore, MoveCommand* minCmd);

/*
 * the function frees resources of the possible commands array
 */
void destroyPossibleCommandsArray(int possibleCommandsAmount, MoveCommand** possibleComands);

#endif
