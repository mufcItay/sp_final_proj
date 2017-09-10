#ifndef COMMANDS_H_
#define COMMANDS_H_
#include "CommonStructures.h"
#include "SDL2\SDL.h"
#define NOP_COMMAND_DATA NULL

/*
 * enum to indicate game mode
 */
typedef enum gamemode_t {
	SINGLE_PLAYER,
	MULTI_PLAYER,
	MODE_UNDEFINED
} GameMode;

/*
 * enum to indicate difficulty level
 */
typedef enum difficultylevel_t {
	NOOB,
	EASY,
	MODERATE,
	HARD,
	EXPERT,
	DIFFICULTY_UNDEFINED
} DifficultyLevel;

/*
 * enum to indicate user color
 */
typedef enum usercoloer_t {
	WHITE,
	BLACK,
	COLOR_UNDEFINED
} UserColor;

/*
 * struct that holds for each command it's handlers
 */
typedef struct command_t  Command;
struct command_t {
	void* data;
	int (*handleCommand)(Command* ,GameSettings* , GameState* );
	void (*destroyCommand)(Command* );
};

void destroyCommand(Command* src);


/*
 * Creation commands for each of the function.
 * the functions will allocate memory and fill members of the command
 */
Command* createGameModeCommand(GameMode mode);
Command* createDifficultyCommand(DifficultyLevel difficulty);
Command* createQuitCommand();
Command* createResetCommand();
Command* createUserColorCommand(UserColor color);
Command* createLoadCommand(char* path);
Command* createDefaultCommand();
Command* createPrintSettingsCommand();
Command* createMoveCommand(SDL_Point origin, SDL_Point destination);
Command* createStartCommand();
Command* createSaveCommand(char* path);
Command* createUndoCommand();
Command* createGetMovesCommand(SDL_Point origin);
Command* createNOPCommand();


/*
 * Handlers for each of the commands.
 * the handlers will relate to the command and react accordingly,
 * by changing game state and/or game settings
 */
int handleGameModeCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleDifficultyCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleQuitCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleResetCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleUserColorCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleLoadCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleDefaultCommand(Command* cmd, GameSettings* settings, GameState* state);
int handlePrintSettingsCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleMoveCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleStartCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleSaveCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleUndoCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleGetMovesCommand(Command* cmd, GameSettings* settings, GameState* state);
int handleNOPCommand(Command* cmd, GameSettings* settings, GameState* state);

/*
 * Destoyer function for each command. the destroyers will free resources for each of the commands
 */
void destroyGeneralCommand(Command* cmd);
void destroyGameModeCommand(Command* cmd);
void destroyDifficultyCommand(Command* cmd);
void destroyQuitCommand(Command* cmd);
void destroyResetCommand(Command* cmd);
void destroyUserColorCommand(Command* cmd);
void destroyLoadCommand(Command* cmd);
void destroyDefaultCommand(Command* cmd);
void destroyPrintSettingsCommand(Command* cmd);
void destroyMoveCommand(Command* cmd);
void destroyStartCommand(Command* cmd);
void destroySaveCommand(Command* cmd);
void destroyUndoCommand(Command* cmd);
void destroyGetMovesCommand(Command* cmd);

/*
 * struct which holds data for command GetMode
 */
typedef struct gameMode_t  GameModeCommand;
struct gameMode_t {
	GameMode mode;
};

/*
 * struct which holds data for command Difficulty
 */
typedef struct difficulty_t  DifficultyCommand;
struct difficulty_t  {
	DifficultyLevel difficulty;
};

/*
 * struct which holds data for command UserColor
 */
typedef struct user_color_t  UserColorCommand;
struct user_color_t {
	UserColor color;
};

/*
 * struct which holds data for command Load
 */
typedef struct load_t  LoadCommand;
struct load_t {
	char* path;
};

/*
 * struct which holds data for command Defualt
 */
typedef struct default_t  DefaultCommand;
struct default_t {

};

/*
 * struct which holds data for command PrintSettings
 */
typedef struct print_settings_t  PrintSettingsCommand;
struct print_settings_t {

};

/*
 * struct which holds data for command Quit
 */
typedef struct quit_t  QuitCommand;
struct quit_t {

};

/*
 * struct which holds data for command Start
 */
typedef struct start_t  StartCommand;
struct start_t {

};

/*
 * struct which holds data for command Move
 */
typedef struct move_t  MoveCommand;
struct move_t {
	SDL_Point originPoint;
	SDL_Point destinationPoint;
};

/*
 * struct which holds data for command GetMoves
 */
typedef struct get_moves_t  GetMovesCommand;
struct get_moves_t {
	SDL_Point originPoint;
};

/*
 * struct which holds data for command Save
 */
typedef struct save_t  SaveCommand;
struct save_t {
	char* path;
};

/*
 * struct which holds data for command Undo
 */
typedef struct undo_t  UndoCommand;
struct undo_t {

};

/*
 * struct which holds data for command Reset
 */
typedef struct reset_t  ResetCommand;
struct reset_t {

};


#endif
