#ifndef FILESYSTEMUTIL_H_
#define FILESYSTEMUTIL_H_
#include "CommonStructures.h"
#include <stdlib.h>
#include <stdio.h>

#define REDUNDANT_FILES_AMOUNT 2
#define MAX_SLOTS 5

#define XML_ERROR ERROR
#define XML_OK OK


#define XML_TURN_WHITE 1
#define XML_TURN_BLACK 0

#define XML_DIFFICULTY_NOOB 1
#define XML_DIFFICULTY_EASY 2
#define XML_DIFFICULTY_MODERATE 3
#define XML_DIFFICULTY_HARD 4
#define XML_DIFFICULTY_EXPERT 5

#define XML_MODE_SINGLE_PLAYER 1
#define XML_MODE_MULTIPLAYER 2

#define XML_COLOR_WHITE XML_TURN_WHITE
#define XML_COLOR_BLACK XML_TURN_WHITE

#define XML_TITLE_TAG "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
#define XML_BOARD_TAG "\t<board>\n"
#define XML_BOARD_END_TAG "\t</board>\n"
#define XML_GAME_TAG "<game>\n"
#define XML_GAME_END_TAG "</game>\n"
#define XML_COLOR_TAG "\t<color>%d</color>\n"
#define XML_ROW_TAG "\t\t<row_%d>%s</row_%d>\n"
#define XML_DIFFICULTY_TAG "\t<difficulty>%d</difficulty>\n"
#define XML_MODE_TAG "\t<game_mode>%d</game_mode>\n"
#define XML_TURN_TAG "\t<current_turn>%d</current_turn>\n"
#define XML_FILE_TYPE ".xml"
#define SLOT_PATH_FORMAT "%s%d%s"
#define FIRST_SLOT_NAME 1


int getNumberOfSavedGames();
int saveGame(GameSettings* settings, GameState* state, char* path);
int loadGame(GameSettings* settings, GameState* state, char* path);
int updateDifficulty(GameSettings* settings, FILE* gameFile);
int reArrageSavedGames();
int writeDifficultyToXML(GameSettings* settings, FILE* gameFile);



#endif
