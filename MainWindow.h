#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include "Window.h"

// enum which indicated a view
enum  WindowView {
    MAIN_VIEW,
    COLOR_SELECTION_VIEW,
	DIFFICULTY_SELECTION_VIEW,
	MODE_SELECTION_VIEW,
	LOAD_GAME_VIEW,
	BOARD_VIEW,
	UNINITIALIZED_VIEW
};

/*
 * struct that hold main window data
 */
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

/*
 * The function creates the view
 */
Window* createMainWindow(GameSettings* gameSettings, GameState* gameState);

/*
 * The function creates the inner windows of the view
 */
Window** createMainWindowWidgets(Window* window, SDL_Renderer* renderer);
/*
 * The function frees resources of the view
 */
void destroyMainWindow(Window* src);
/*
 * The function draws the view
 */
void drawMainWindow(Window* src);
/*
 * The function handles events relating to the view
 */
Command* handleEventMainWindow(Window* src, SDL_Event* event);

/*
 * handler for load button
 */
Command* loadGameButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for new game button
 */
Command* newGameButtonHandler(Window* src, SDL_Event* event);

/*
 * handler for exit button
 */
Command* exitButtonHandler(Window* src, SDL_Event* event);

/*
 * the function sets the current view relating to which view to draw and which view reacts to events
 */
void setCurrentView(Window* src, enum WindowView view);

/*
 * the function sets the re draw state of each of the view's inner components
 */
void setMainWindowInnerReDraw(Window* src, SDL_bool reDraw);

/*
 * the function handles errors happened during handle event in some inner gui component.
 * the return value is the new error code after trying to solve the error.
 */
ErrorCode handleMainWindowError(Window* src, ErrorCode err);

/*
 * The function destroys the viwes of Main Window
 */
void destroyViews(MainWindow* data);

/*
 * The function initialized ands sets to data the view of Main WIndow
 */
void initializeViews(MainWindow* data, Window* res);

#endif
