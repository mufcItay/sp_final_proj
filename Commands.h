#ifndef COMMANDS_H_
#define COMMANDS_H_
#include "CommonStructures.h"
#include "SDL2\SDL.h"
#define NOP_COMMAND_DATA NULL

typedef enum gamemode_t {
	SINGLE_PLAYER,
	MULTI_PLAYER,
	MODE_UNDEFINED
} GameMode;

typedef enum difficultylevel_t {
	NOOB,
	EASY,
	MODERATE,
	HARD,
	EXPERT,
	DIFFICULTY_UNDEFINED
} DifficultyLevel;

typedef enum usercoloer_t {
	WHITE,
	BLACK,
	COLOR_UNDEFINED
} UserColor;

typedef struct command_t  Command;
struct command_t {
	void* data;
	int (*handleCommand)(Command* ,GameSettings* , GameState* );
	void (*destroyCommand)(Command* );
};

void destroyCommand(Command* src);


Command* CreateGameModeCommand(GameMode mode);
Command* CreateDifficultyCommand(DifficultyLevel difficulty);
Command* CreateQuitCommand();
Command* CreateResetCommand();
Command* CreateUserColorCommand(UserColor color);
Command* CreateLoadCommand(char* path);
Command* CreateDefaultCommand();
Command* CreatePrintSettingsCommand();
Command* CreateMoveCommand(SDL_Point origin, SDL_Point destination);
Command* CreateStartCommand();
Command* CreateSaveCommand(char* path);
Command* CreateUndoCommand();
Command* CreateGetMovesCommand(SDL_Point origin);
Command* CreateNOPCommand();


int HandleGameModeCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleDifficultyCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleQuitCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleResetCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleUserColorCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleLoadCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleDefaultCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandlePrintSettingsCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleMoveCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleStartCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleSaveCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleUndoCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleGetMovesCommand(Command* cmd, GameSettings* settings, GameState* state);
int HandleNOPCommand(Command* cmd, GameSettings* settings, GameState* state);

void DestroyGeneralCommand(Command* cmd);
void DestroyGameModeCommand(Command* cmd);
void DestroyDifficultyCommand(Command* cmd);
void DestroyQuitCommand(Command* cmd);
void DestroyResetCommand(Command* cmd);
void DestroyUserColorCommand(Command* cmd);
void DestroyLoadCommand(Command* cmd);
void DestroyDefaultCommand(Command* cmd);
void DestroyPrintSettingsCommand(Command* cmd);
void DestroyMoveCommand(Command* cmd);
void DestroyStartCommand(Command* cmd);
void DestroySaveCommand(Command* cmd);
void DestroyUndoCommand(Command* cmd);
void DestroyGetMovesCommand(Command* cmd);


typedef struct gameMode_t  GameModeCommand;
struct gameMode_t {
	GameMode mode;
};

typedef struct difficulty_t  DifficultyCommand;
struct difficulty_t  {
	DifficultyLevel difficulty;
};

typedef struct user_color_t  UserColorCommand;
struct user_color_t {
	UserColor color;
};

typedef struct load_t  LoadCommand;
struct load_t {
	char* path;
};

typedef struct default_t  DefaultCommand;
struct default_t {

};
typedef struct print_settings_t  PrintSettingsCommand;
struct print_settings_t {

};

typedef struct quit_t  QuitCommand;
struct quit_t {

};

typedef struct start_t  StartCommand;
struct start_t {

};

typedef struct move_t  MoveCommand;
struct move_t {
	SDL_Point originPoint;
	SDL_Point destinationPoint;
};


typedef struct get_moves_t  GetMovesCommand;
struct get_moves_t {
	SDL_Point originPoint;
};

typedef struct save_t  SaveCommand;
struct save_t {
	char* path;
};

typedef struct undo_t  UndoCommand;
struct undo_t {

};

typedef struct reset_t  ResetCommand;
struct reset_t {

};


#endif
