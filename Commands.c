#include "CommonStructures.h"
#include "Commands.h"
#include "SDL2\SDL.h"
#include "FileSystemUtil.h"

void destroyCommand(Command* src){
	if(!src){
		return;
	}
	src->destroyCommand(src);
}

Command* createGameModeCommand(GameMode mode){
	Command* cmd = (Command*) malloc(sizeof(Command));
	GameModeCommand* data = (GameModeCommand*) malloc(sizeof(GameModeCommand));
	data->mode = mode;
		cmd->destroyCommand = destroyGameModeCommand;
	cmd->handleCommand = handleGameModeCommand;
	cmd->data = data;
	return cmd;
}

Command* createDifficultyCommand(DifficultyLevel difficulty){
	Command* cmd = (Command*) malloc(sizeof(Command));
	DifficultyCommand* data = (DifficultyCommand*) malloc(sizeof(DifficultyCommand));
	data->difficulty= difficulty;
		cmd->destroyCommand = destroyDifficultyCommand;
	cmd->handleCommand = handleDifficultyCommand;
	cmd->data = data;
	return cmd;
}

Command* createQuitCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	QuitCommand* data = (QuitCommand*) malloc(sizeof(QuitCommand));
	cmd->destroyCommand = destroyQuitCommand;
	cmd->handleCommand = handleQuitCommand;
	cmd->data = data;
	return cmd;
}

Command* createResetCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	ResetCommand* data = (ResetCommand*) malloc(sizeof(ResetCommand));
	cmd->destroyCommand = destroyResetCommand;
	cmd->handleCommand = handleResetCommand;
	cmd->data = data;
	return cmd;
}

Command* createUserColorCommand(UserColor color){
	Command* cmd = (Command*) malloc(sizeof(Command));
	UserColorCommand* data = (UserColorCommand*) malloc(sizeof(UserColorCommand));
	data->color = color;
	cmd->destroyCommand = destroyUserColorCommand;
	cmd->handleCommand = handleUserColorCommand;
	cmd->data = data;
	return cmd;
}

Command* createLoadCommand(char* path){
	Command* cmd = (Command*) malloc(sizeof(Command));
	LoadCommand* data = (LoadCommand*) malloc(sizeof(LoadCommand));
	data->path = path;
	if(data->path == NULL) {
		return NULL;
	}
	cmd->destroyCommand = destroyLoadCommand;
	cmd->handleCommand = handleLoadCommand;
	cmd->data = data;
	return cmd;
}

Command* createDefaultCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	DefaultCommand* data = (DefaultCommand*) malloc(sizeof(DefaultCommand));
	cmd->destroyCommand = destroyDefaultCommand;
	cmd->handleCommand = handleDefaultCommand;
	cmd->data = data;
	return cmd;
}

Command* createPrintSettingsCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	PrintSettingsCommand* data = (PrintSettingsCommand*) malloc(sizeof(PrintSettingsCommand));
	cmd->destroyCommand = destroyPrintSettingsCommand;
	cmd->handleCommand = handlePrintSettingsCommand;
	cmd->data = data;
	return cmd;
}

Command* createMoveCommand(SDL_Point origin, SDL_Point destination){
	Command* cmd = (Command*) malloc(sizeof(Command));
	MoveCommand* data = (MoveCommand*) malloc(sizeof(MoveCommand));
	data->originPoint.x = origin.x;
	data->originPoint.y = origin.y;
	data->destinationPoint.x = destination.x;
	data->destinationPoint.y = destination.y;
	cmd->destroyCommand = destroyMoveCommand;
	cmd->handleCommand = handleMoveCommand;
	cmd->data = data;
	return cmd;
}

Command* createStartCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	StartCommand* data = (StartCommand*) malloc(sizeof(StartCommand));
	cmd->destroyCommand = destroyStartCommand;
	cmd->handleCommand = handleStartCommand;
	cmd->data = data;
	return cmd;
}

Command* createSaveCommand(char* path){
	Command* cmd = (Command*) malloc(sizeof(Command));
	SaveCommand* data = (SaveCommand*) malloc(sizeof(SaveCommand));
	data->path = path;
	cmd->destroyCommand = destroySaveCommand;
	cmd->handleCommand = handleSaveCommand;
	cmd->data = data;
	return cmd;
}

Command* createUndoCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	UndoCommand* data = (UndoCommand*) malloc(sizeof(UndoCommand));
	cmd->destroyCommand = destroyUndoCommand;
	cmd->handleCommand = handleUndoCommand;
	cmd->data = data;
	return cmd;
}

Command* createGetMovesCommand(SDL_Point origin){
	Command* cmd = (Command*) malloc(sizeof(Command));
	GetMovesCommand* data = (GetMovesCommand*) malloc(sizeof(GetMovesCommand));
	data->originPoint.x = origin.x;
	data->originPoint.x = origin.y;
	cmd->destroyCommand = destroyGetMovesCommand;
	cmd->handleCommand = handleGetMovesCommand;
	cmd->data = data;
	return cmd;
}
Command* createNOPCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	cmd->data = NOP_COMMAND_DATA;
	cmd->destroyCommand = destroyGeneralCommand;
	cmd->handleCommand = handleNOPCommand;
	return cmd;
}

int handleGameModeCommand(Command* cmd, GameSettings* settings, GameState* state){
	if(cmd == NULL || settings == NULL || state == NULL) {
		return ERROR;
	}
	GameModeCommand* modeCmd = (GameModeCommand*) cmd->data;
	settings->mode = modeCmd->mode;
	return OK;
}

int handleDifficultyCommand(Command* cmd, GameSettings* settings, GameState* state)
{
	if(cmd == NULL || settings == NULL || state == NULL) {
		return ERROR;
	}
	DifficultyCommand* difficultyCmd = (DifficultyCommand*) cmd->data;
	settings->difficulty = difficultyCmd->difficulty;
	return OK;
}

int handleQuitCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}

int handleResetCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}

int handleUserColorCommand(Command* cmd, GameSettings* settings, GameState* state)
{
	if(cmd == NULL || settings == NULL || state == NULL) {
		return ERROR;
	}
	UserColorCommand* colorCmd = (UserColorCommand*) cmd->data;
	settings->color= colorCmd->color;
	return OK;
}

int handleLoadCommand(Command* cmd, GameSettings* settings, GameState* state) {
	if(cmd == NULL || settings == NULL || state == NULL) {
		return ERROR;
	}

	LoadCommand* loadCmd = (LoadCommand*) cmd->data;
	int ret = loadGame(settings,state,loadCmd->path);
	return ret;
}

int handleDefaultCommand(Command* cmd, GameSettings* settings, GameState* state){
	if(cmd == NULL || settings == NULL || state == NULL) {
		return ERROR;
	}

	setDefaultSettings(settings);
	return OK;
}

int handlePrintSettingsCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}

int handleMoveCommand(Command* cmd, GameSettings* settings, GameState* state){
	if(cmd == NULL || settings == NULL || state == NULL) {
		return ERROR;
	}
	// if move invalid get out. supposed to check it here or in the UI? cause error message happens in UI
	MoveCommand* moveCmd = (MoveCommand*) cmd->data;
	char soldierTypeToMove = state->board[moveCmd->originPoint.x][moveCmd->originPoint.y];
	state->board[moveCmd->originPoint.x][moveCmd->originPoint.y] = SOLDIER_TYPE_EMPTY;
	state->board[moveCmd->destinationPoint.x][moveCmd->destinationPoint.y] = soldierTypeToMove;

	if(settings->mode == SINGLE_PLAYER) {
		// get and perform computer play
	}
	else {
		state->turn =  state->turn == WHITE ? BLACK : WHITE;
	}

	// update undo array

	return OK;
}

int handleStartCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}

int handleSaveCommand(Command* cmd, GameSettings* settings, GameState* state){
	if(cmd == NULL || settings == NULL || state == NULL) {
		return ERROR;
	}
	SaveCommand* saveCmd = (SaveCommand*) cmd->data;
	int ret = saveGame(settings,state,saveCmd->path);
	return ret;
}

int handleUndoCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int handleGetMovesCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int handleNOPCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}

void destroyGeneralCommand(Command* cmd){
	if (cmd == NULL ) {
		return;
	}
	if(cmd->data != NULL) {
		free(cmd->data);
	}

	free(cmd);
}

void destroyGameModeCommand(Command* cmd){
	destroyGeneralCommand(cmd);
}

void destroyDifficultyCommand(Command* cmd){
	destroyGeneralCommand(cmd);
}
void destroyQuitCommand(Command* cmd){
	destroyGeneralCommand(cmd);
}

void destroyResetCommand(Command* cmd){
	destroyGeneralCommand(cmd);
}

void destroyUserColorCommand(Command* cmd){
	destroyGeneralCommand(cmd);
}
void destroyLoadCommand(Command* cmd){
	LoadCommand* loadCmd = (LoadCommand*) cmd->data;
	if(loadCmd->path != NULL) {
		free(loadCmd->path);
	}
	destroyGeneralCommand(cmd);
}
void destroyDefaultCommand(Command* cmd){
	destroyGeneralCommand(cmd);
}
void destroyPrintSettingsCommand(Command* cmd){
	destroyGeneralCommand(cmd);
}
void destroyMoveCommand(Command* cmd){
	destroyGeneralCommand(cmd);
}
void destroyStartCommand(Command* cmd){
	destroyGeneralCommand(cmd);
}
void destroySaveCommand(Command* cmd){
	SaveCommand* saveCmd = (SaveCommand*) cmd->data;
	if(saveCmd->path != NULL) {
		free(saveCmd->path);
	}
	destroyGeneralCommand(cmd);
}
void destroyUndoCommand(Command* cmd){
	destroyGeneralCommand(cmd);
}
void destroyGetMovesCommand(Command* cmd){
	destroyGeneralCommand(cmd);
}
