CC = gcc
OBJS =  CommonStructures.o \
		Commands.o \
		UIController.o \
		CMDController.o \
		CommonGUIUtil.o \
		Window.o \
		FileSystemUtil.o \
		GUIController.o \
		MainWindow.o \
		MinMax.o \
		main.o  \
		InfoMessageBox.o \
		PawnPromotionMessageBox.o \
		SaveGameMessageBox.o \
		SimpleButton.o \
		SoldierButton.o \
		ColorSelectionView.o \
		DifficultySelectionView.o \
		ModeSelectionView.o \
		GameBoardView.o \
		LoadGameView.o

EXEC = ChessProg

COMP_FLAG = -std=c99 -Wall -Wextra #\
  #-pedantic-errors

SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT 
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@

CommonStructures.o: CommonStructures.h CommonStructures.c
	$(CC) $(COMP_FLAG)  $(SDL_COMP_FLAG) -c $*.c
Commands.o: Commands.h Commands.c  CommonStructures.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
UIController.o: UIController.h Commands.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
CommonGUIUtil.o: CommonGUIUtil.c CommonGUIUtil.h  UIController.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
CMDController.o: CMDController.c CMDController.h  UIController.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Window.o: Window.c Window.h  CommonStructures.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
FileSystemUtil.o: FileSystemUtil.c FileSystemUtil.h CommonStructures.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GUIController.o: GUIController.c GUIController.h  Commands.h CommonStructures.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
MainWindow.o: MainWindow.c MainWindow.h Window.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
MinMax.o: MinMax.c MinMax.h Commands.h  CommonStructures.h 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
main.o: main.c UIController.h CommonStructures.h Commands.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
InfoMessageBox.o: InfoMessageBox.c InfoMessageBox.h CommonGUIUtil.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
PawnPromotionMessageBox.o:  PawnPromotionMessageBox.c PawnPromotionMessageBox.h CommonGUIUtil.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SaveGameMessageBox.o: SaveGameMessageBox.c SaveGameMessageBox.h CommonGUIUtil.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SimpleButton.o: SimpleButton.c SimpleButton.h Window.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SoldierButton.o: SoldierButton.c SoldierButton.h Window.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ColorSelectionView.o: ColorSelectionView.c ColorSelectionView.h Window.h CommonStructures.h  CommonGUIUtil.h Commands.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
DifficultySelectionView.o:  DifficultySelectionView.c DifficultySelectionView.h Window.h CommonStructures.h  CommonGUIUtil.h Commands.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c 
ModeSelectionView.o:  ModeSelectionView.c ModeSelectionView.h Window.h CommonStructures.h  CommonGUIUtil.h Commands.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameBoardView.o:  GameBoardView.c GameBoardView.h Window.h CommonStructures.h  CommonGUIUtil.h Commands.h 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
LoadGameView.o:  LoadGameView.c LoadGameView.h Window.h CommonStructures.h  CommonGUIUtil.h Commands.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)