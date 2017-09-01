#include "CommonStructures.h"
#include "Commands.h"
#include "SDL2\SDL.h"

void destroyCommand(Command* src){
	if(!src){
		return;
	}
	src->destroyCommand(src);
}

Command* CreateGameModeCommand(GameMode mode){
	Command* cmd = (Command*) malloc(sizeof(Command));
	GameModeCommand* data = (GameModeCommand*) malloc(sizeof(GameModeCommand));
	data->mode = mode;
		cmd->destroyCommand = DestroyGameModeCommand;
	cmd->handleCommand = HandleGameModeCommand;
	cmd->data = data;
	return cmd;
}

Command* CreateDifficultyCommand(DifficultyLevel difficulty){
	Command* cmd = (Command*) malloc(sizeof(Command));
	DifficultyCommand* data = (DifficultyCommand*) malloc(sizeof(DifficultyCommand));
	data->difficulty= difficulty;
		cmd->destroyCommand = DestroyDifficultyCommand;
	cmd->handleCommand = HandleDifficultyCommand;
	cmd->data = data;
	return cmd;
}

Command* CreateQuitCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	QuitCommand* data = (QuitCommand*) malloc(sizeof(QuitCommand));
	cmd->destroyCommand = DestroyQuitCommand;
	cmd->handleCommand = HandleQuitCommand;
	cmd->data = data;
	return cmd;
}

Command* CreateResetCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	ResetCommand* data = (ResetCommand*) malloc(sizeof(ResetCommand));
	cmd->destroyCommand = DestroyResetCommand;
	cmd->handleCommand = HandleResetCommand;
	cmd->data = data;
	return cmd;
}

Command* CreateUserColorCommand(UserColor color){
	Command* cmd = (Command*) malloc(sizeof(Command));
	UserColorCommand* data = (UserColorCommand*) malloc(sizeof(UserColorCommand));
	data->color = color;
	cmd->destroyCommand = DestroyUserColorCommand;
	cmd->handleCommand = HandleUserColorCommand;
	cmd->data = data;
	return cmd;
}

Command* CreateLoadCommand(char* path){
	Command* cmd = (Command*) malloc(sizeof(Command));
	LoadCommand* data = (LoadCommand*) malloc(sizeof(LoadCommand));
	data->path = malloc(sizeof(char) * strlen(path));
	if(data->path == NULL) {
		return NULL;
	}
	strcpy(data->path, path);
	cmd->destroyCommand = DestroyLoadCommand;
	cmd->handleCommand = HandleLoadCommand;
	cmd->data = data;
	return cmd;
}

Command* CreateDefaultCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	DefaultCommand* data = (DefaultCommand*) malloc(sizeof(DefaultCommand));
	cmd->destroyCommand = DestroyDefaultCommand;
	cmd->handleCommand = HandleDefaultCommand;
	cmd->data = data;
	return cmd;
}

Command* CreatePrintSettingsCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	PrintSettingsCommand* data = (PrintSettingsCommand*) malloc(sizeof(PrintSettingsCommand));
	cmd->destroyCommand = DestroyPrintSettingsCommand;
	cmd->handleCommand = HandlePrintSettingsCommand;
	cmd->data = data;
	return cmd;
}

Command* CreateMoveCommand(SDL_Point origin, SDL_Point destination){
	Command* cmd = (Command*) malloc(sizeof(Command));
	MoveCommand* data = (MoveCommand*) malloc(sizeof(MoveCommand));
	data->originPoint.x = origin.x;
	data->originPoint.x = origin.y;
	data->destinationPoint.x = destination.x;
	data->destinationPoint.x = destination.y;
	cmd->destroyCommand = DestroyMoveCommand;
	cmd->handleCommand = HandleMoveCommand;
	cmd->data = data;
	return cmd;
}

Command* CreateStartCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	StartCommand* data = (StartCommand*) malloc(sizeof(StartCommand));
	cmd->destroyCommand = DestroyStartCommand;
	cmd->handleCommand = HandleStartCommand;
	cmd->data = data;
	return cmd;
}

Command* CreateSaveCommand(char* path){
	Command* cmd = (Command*) malloc(sizeof(Command));
	SaveCommand* data = (SaveCommand*) malloc(sizeof(SaveCommand));
	data->path = malloc(sizeof(char) * strlen(path));
	if(data->path == NULL) {
		return NULL;
	}
	strcpy(data->path, path);
	cmd->destroyCommand = DestroySaveCommand;
	cmd->handleCommand = HandleSaveCommand;
	cmd->data = data;
	return cmd;
}

Command* CreateUndoCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	UndoCommand* data = (UndoCommand*) malloc(sizeof(UndoCommand));
	cmd->destroyCommand = DestroyUndoCommand;
	cmd->handleCommand = HandleUndoCommand;
	cmd->data = data;
	return cmd;
}

Command* CreateGetMovesCommand(SDL_Point origin){
	Command* cmd = (Command*) malloc(sizeof(Command));
	GetMovesCommand* data = (GetMovesCommand*) malloc(sizeof(GetMovesCommand));
	data->originPoint.x = origin.x;
	data->originPoint.x = origin.y;
	cmd->destroyCommand = DestroyGetMovesCommand;
	cmd->handleCommand = HandleGetMovesCommand;
	cmd->data = data;
	return cmd;
}
Command* CreateNOPCommand(){
	Command* cmd = (Command*) malloc(sizeof(Command));
	cmd->data = NOP_COMMAND_DATA;
	cmd->destroyCommand = DestroyGeneralCommand;
	cmd->handleCommand = HandleNOPCommand;
	return cmd;
}

int HandleGameModeCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleDifficultyCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleQuitCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleResetCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleUserColorCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleLoadCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleDefaultCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandlePrintSettingsCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleMoveCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleStartCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleSaveCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleUndoCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleGetMovesCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}
int HandleNOPCommand(Command* cmd, GameSettings* settings, GameState* state){return OK;}

void DestroyGeneralCommand(Command* cmd){
	if (cmd == NULL ) {
		return;
	}
	if(cmd->data != NULL) {
		free(cmd->data);
	}

	free(cmd);
}

void DestroyGameModeCommand(Command* cmd){
	DestroyGeneralCommand(cmd);
}

void DestroyDifficultyCommand(Command* cmd){
	DestroyGeneralCommand(cmd);
}
void DestroyQuitCommand(Command* cmd){
	DestroyGeneralCommand(cmd);
}

void DestroyResetCommand(Command* cmd){
	DestroyGeneralCommand(cmd);
}

void DestroyUserColorCommand(Command* cmd){
	DestroyGeneralCommand(cmd);
}
void DestroyLoadCommand(Command* cmd){
	LoadCommand* data = (LoadCommand*) cmd->data;
	free(data->path);
	DestroyGeneralCommand(cmd);
}
void DestroyDefaultCommand(Command* cmd){
	DestroyGeneralCommand(cmd);
}
void DestroyPrintSettingsCommand(Command* cmd){
	DestroyGeneralCommand(cmd);
}
void DestroyMoveCommand(Command* cmd){
	DestroyGeneralCommand(cmd);
}
void DestroyStartCommand(Command* cmd){
	DestroyGeneralCommand(cmd);
}
void DestroySaveCommand(Command* cmd){
	SaveCommand* data = (SaveCommand*) cmd->data;
	free(data->path);
	DestroyGeneralCommand(cmd);
}
void DestroyUndoCommand(Command* cmd){
	DestroyGeneralCommand(cmd);
}
void DestroyGetMovesCommand(Command* cmd){
	DestroyGeneralCommand(cmd);
}
