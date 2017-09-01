#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include "Window.h"

enum  WindowView {
    MAIN_VIEW,
    COLOR_SELECTION_VIEW,
	DIFFICULTY_SELECTION_VIEW,
	MODE_SELECTION_VIEW,
	LOAD_GAME_VIEW,
	BOARD_VIEW,
	UNINITIALIZED_VIEW
};

typedef struct mainwindow_t  MainWindow;
struct mainwindow_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	Window** mainMenuWidgets;
	Window* boardViewWindow;
	Window* difficultySelectionViewWindow;
	Window* modeSelectionViewWindow;
	Window* colorSelectionViewWindow;
	Window* loadGameViewWindow;
	int numOfWidgets;
	enum WindowView view;
	Window* viewWindow;
	GameSettings* gameSettings;
	GameState* gameState;

};

Window* createMainWindow(GameSettings* gameSettings, GameState* gameState);
Window** createMainWindowWidgets(Window* window, SDL_Renderer* renderer);
void destroyMainWindow(Window* src);
void drawMainWindow(Window* src);
Command* handleEventMainWindow(Window* src, SDL_Event* event);
Command* LoadGameButtonHandler(Window* src, SDL_Event* event);
Command* NewGameButtonHandler(Window* src, SDL_Event* event);
Command* ExitButtonHandler(Window* src, SDL_Event* event);
void setCurrentView(Window* src, enum WindowView view);
void setMainWindowInnerReDraw(Window* src, SDL_bool reDraw);

#endif
