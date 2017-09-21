#include <stdlib.h>

#include "CommonGUIUtil.h"

SDL_Rect* copyRect(SDL_Rect* src){
	if(src == NULL){
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL;
	}
	SDL_Rect* res = malloc(sizeof(SDL_Rect));
	if(res==NULL){
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	res->h = src->h;
	res->w = src->w;
	res->x = src->x;
	res->y = src->y;
	return res;
}

SDL_Rect* createInvlidRect(){
	SDL_Rect* res = malloc(sizeof(SDL_Rect));
	if(res==NULL){
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	res->h = INVALID_LOCATION;
	res->w = INVALID_LOCATION;
	res->x = INVALID_LOCATION;
	res->y = INVALID_LOCATION;
	return res;
}

SDL_bool isCharLoweCase(char c)
{
	return (c >= 'a' && c <= 'z');
}

char toLowerCase(char c) {
	char lower = c;
	if(isCharLoweCase(c) == SDL_FALSE) {
		lower += ('a' - 'A');
	}
	return lower;
}

DifficultyLevel getDifficulty(int difficultyButtonIndex) {
	switch(difficultyButtonIndex) {
		case DIFFICULTY_SELECTION_WINDOW_NOOB_BUTTON_INDEX:
			return NOOB;
			break;
		case DIFFICULTY_SELECTION_WINDOW_EASY_BUTTON_INDEX:
			return EASY;
			break;
		case DIFFICULTY_SELECTION_WINDOW_MODERATE_BUTTON_INDEX:
			return MODERATE;
			break;
		case DIFFICULTY_SELECTION_WINDOW_HARD_BUTTON_INDEX:
			return HARD;
			break;
		case DIFFICULTY_SELECTION_WINDOW_EXPERT_BUTTON_INDEX:
			return EXPERT;
			break;
	}
	return DIFFICULTY_UNDEFINED;
}

GameMode getMode(int modeButtonIndex) {
	switch(modeButtonIndex) {
		case MODE_SELECTION_WINDOW_SINGLE_PALYER_BUTTON_INDEX:
			return SINGLE_PLAYER;
			break;
		case MODE_SELECTION_WINDOW_TWO_PLAYERS_INDEX:
			return MULTI_PLAYER;
			break;
	}

	return MODE_UNDEFINED;
}

UserColor getColor(int colorButtonIndex) {
	switch(colorButtonIndex) {
		case COLOR_SELECTION_WINDOW_WHITE_BUTTON_INDEX:
			return WHITE;
			break;
		case COLOR_SELECTION_WINDOW_BLACK_BUTTON_INDEX:
			return BLACK;
			break;
	}

	return COLOR_UNDEFINED;
}
