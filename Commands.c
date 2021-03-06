#include "SDL.h"
#include "FileSystemUtil.h"
#include "CommonStructures.h"
#include "Commands.h"

void destroyCommand(Command* src){
	if(!src){
		return;
	}
	src->destroyCommand(src);
}

Command* createGameModeCommand(GameMode mode){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	GameModeCommand* data = (GameModeCommand*) malloc(sizeof(GameModeCommand));
	// handle error
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
	data->mode = mode;
	cmd->destroyCommand = destroyGameModeCommand;
	cmd->handleCommand = handleGameModeCommand;
	cmd->data = data;
	return cmd;
}

Command* createDifficultyCommand(DifficultyLevel difficulty){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	DifficultyCommand* data = (DifficultyCommand*) malloc(sizeof(DifficultyCommand));
	// handle error
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
	data->difficulty= difficulty;
	cmd->destroyCommand = destroyDifficultyCommand;
	cmd->handleCommand = handleDifficultyCommand;
	cmd->data = data;
	return cmd;
}

Command* createQuitCommand(){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	QuitCommand* data = (QuitCommand*) malloc(sizeof(QuitCommand));
	// handle error
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
	cmd->destroyCommand = destroyQuitCommand;
	cmd->handleCommand = handleQuitCommand;
	cmd->data = data;
	return cmd;
}

Command* createResetCommand(){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	ResetCommand* data = (ResetCommand*) malloc(sizeof(ResetCommand));
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
	cmd->destroyCommand = destroyResetCommand;
	cmd->handleCommand = handleResetCommand;
	cmd->data = data;
	return cmd;
}

Command* createUserColorCommand(UserColor color){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	// handle error
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	UserColorCommand* data = (UserColorCommand*) malloc(sizeof(UserColorCommand));
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
	data->color = color;
	cmd->destroyCommand = destroyUserColorCommand;
	cmd->handleCommand = handleUserColorCommand;
	cmd->data = data;
	return cmd;
}

Command* createLoadCommand(char* path){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	LoadCommand* data = (LoadCommand*) malloc(sizeof(LoadCommand));
	// handle error
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
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
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	DefaultCommand* data = (DefaultCommand*) malloc(sizeof(DefaultCommand));
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
	cmd->destroyCommand = destroyDefaultCommand;
	cmd->handleCommand = handleDefaultCommand;
	cmd->data = data;
	return cmd;
}

Command* createPrintSettingsCommand(){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	PrintSettingsCommand* data = (PrintSettingsCommand*) malloc(sizeof(PrintSettingsCommand));
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
	cmd->destroyCommand = destroyPrintSettingsCommand;
	cmd->handleCommand = handlePrintSettingsCommand;
	cmd->data = data;
	return cmd;
}

Command* createMoveCommand(SDL_Point origin, SDL_Point destination){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	MoveCommand* data = (MoveCommand*) malloc(sizeof(MoveCommand));
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
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
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	StartCommand* data = (StartCommand*) malloc(sizeof(StartCommand));
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
	cmd->destroyCommand = destroyStartCommand;
	cmd->handleCommand = handleStartCommand;
	cmd->data = data;
	return cmd;
}

Command* createSaveCommand(char* path){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	SaveCommand* data = (SaveCommand*) malloc(sizeof(SaveCommand));
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}

	data->path = path;
	cmd->destroyCommand = destroySaveCommand;
	cmd->handleCommand = handleSaveCommand;
	cmd->data = data;
	return cmd;
}

Command* createUndoCommand(){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	UndoCommand* data = (UndoCommand*) malloc(sizeof(UndoCommand));
	// handle error
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
	cmd->destroyCommand = destroyUndoCommand;
	cmd->handleCommand = handleUndoCommand;
	cmd->data = data;
	return cmd;
}

Command* createGetMovesCommand(SDL_Point origin){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	GetMovesCommand* data = (GetMovesCommand*) malloc(sizeof(GetMovesCommand));
	// handle error
	if(data == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		free(cmd);
		return NULL;
	}
	data->originPoint.x = origin.x;
	data->originPoint.x = origin.y;
	cmd->destroyCommand = destroyGetMovesCommand;
	cmd->handleCommand = handleGetMovesCommand;
	cmd->data = data;
	return cmd;
}
Command* createNOPCommand(){
	// allocate memory
	Command* cmd = (Command*) malloc(sizeof(Command));
	if(cmd == NULL) {
		printErrorMessage(MEMORY_ALLOCATION_ERROR_MESSAGE);
		return NULL;
	}
	cmd->data = NOP_COMMAND_DATA;
	cmd->destroyCommand = destroyGeneralCommand;
	cmd->handleCommand = handleNOPCommand;
	return cmd;
}

ErrorCode handleGameModeCommand(Command* cmd, GameSettings* settings, GameState* state){
	if(cmd == NULL || settings == NULL || state == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}
	GameModeCommand* modeCmd = (GameModeCommand*) cmd->data;
	settings->mode = modeCmd->mode;

	return OK;
}

ErrorCode handleDifficultyCommand(Command* cmd, GameSettings* settings, GameState* state)
{
	if(cmd == NULL || settings == NULL || state == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}
	DifficultyCommand* difficultyCmd = (DifficultyCommand*) cmd->data;
	settings->difficulty = difficultyCmd->difficulty;
	return OK;
}

ErrorCode handleQuitCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}

ErrorCode handleUserColorCommand(Command* cmd, GameSettings* settings, GameState* state)
{
	if(cmd == NULL || settings == NULL || state == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}
	UserColorCommand* colorCmd = (UserColorCommand*) cmd->data;
	settings->color= colorCmd->color;
	return OK;
}

ErrorCode handleLoadCommand(Command* cmd, GameSettings* settings, GameState* state) {
	if(cmd == NULL || settings == NULL || state == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}

	LoadCommand* loadCmd = (LoadCommand*) cmd->data;
	int ret = loadGame(settings,state,loadCmd->path);
	if(ret == LOAD_ERROR) {
		printErrorMessage(LOAD_GAME_ERROR_MESSAGE);
	}
	return ret;
}

ErrorCode handleDefaultCommand(Command* cmd, GameSettings* settings, GameState* state){
	if(cmd == NULL || settings == NULL || state == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}

	setDefaultSettings(settings);
	return OK;
}

ErrorCode handlePrintSettingsCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}

ErrorCode handleMoveCommand(Command* cmd, GameSettings* settings, GameState* state){
	if(cmd == NULL || settings == NULL || state == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}

	// TODO: if move invalid get out. supposed to check it here or in the UI? cause error message happens in UI
	MoveCommand* moveCmd = (MoveCommand*) cmd->data;
	char soldierTypeToMove = state->board[moveCmd->originPoint.x][moveCmd->originPoint.y];
	state->board[moveCmd->originPoint.x][moveCmd->originPoint.y] = SOLDIER_TYPE_EMPTY;
	state->board[moveCmd->destinationPoint.x][moveCmd->destinationPoint.y] = soldierTypeToMove;
	switchTurn(state);

	if(settings->mode == SINGLE_PLAYER) {
		// TODO: get and perform computer play
		switchTurn(state);
	}

	// TODO: update undo array

	return OK;
}

ErrorCode handleStartCommand(Command* cmd, GameSettings* settings, GameState* state){
	if(cmd == NULL || settings == NULL || state == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}

	ErrorCode err = setInitialGameState(state);
	if(settings->mode == SINGLE_PLAYER && settings->color == BLACK) {
		// TODO: play first computer turn using MINMAX
		switchTurn(state);
	}
	return err;
}


ErrorCode handleResetCommand(Command* cmd, GameSettings* settings, GameState* state) {
	if(cmd == NULL || settings == NULL || state == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}

	ErrorCode err = handleStartCommand(cmd, settings, state);
	return err;
}

ErrorCode handleSaveCommand(Command* cmd, GameSettings* settings, GameState* state){
	if(cmd == NULL || settings == NULL || state == NULL) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
		return NULL_POINTER_ERROR;
	}
	SaveCommand* saveCmd = (SaveCommand*) cmd->data;
	int ret = saveGame(settings,state,saveCmd->path);
	if(ret == SAVE_ERROR) {
		printErrorMessage(SAVE_GAME_ERROR_MESSAGE);
	}
	return ret;
}

ErrorCode handleUndoCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
ErrorCode handleGetMovesCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
ErrorCode handleNOPCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}

void destroyGeneralCommand(Command* cmd){
	if (cmd == NULL ) {
		printErrorMessage(NULL_POINTER_ERROR_MESSAGE);
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
