#LINUX_SDL_INCLUDE = -I/usr/local/lib/sdl_2.0.5/include -D_REENTRANT
#LINUX_SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main
LINUX_SDL_INCLUDE = -IC:/SDL2/include -D_REENTRANT
LINUX_SDL_LIB = -LC:/SDL2/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main


OBJ_SRCS := 
ASM_SRCS := 
C_SRCS := 
S_UPPER_SRCS := 
O_SRCS := 
EXECUTABLES := 
OBJS := 
C_DEPS := 

# Every subdirectory with source files must be described here
SUBDIRS := \
. \
GUIControls \
Views \


C_SRCS += \
./CommonStructures.c \
./Commands.c \
./CommonGUIUtil.c \
./FileSystemUtil.c \
./UIController.c \
./CMDController.c \
./Window.c \
./GUIController.c \
./MainWindow.c \
./MinMax.c \
./main.c \
./InfoMessageBox.c \
./PawnPromotionMessageBox.c \
./SaveGameMessageBox.c \
./SimpleButton.c \
./SoldierButton.c \
./ColorSelectionView.c \
./DifficultySelectionView.c \
./ModeSelectionView.c \
./GameBoardView.c \
./LoadGameView.c

OBJS += \
./CommonStructures.o \
./Commands.o \
./CMDController.o \
./CommonGUIUtil.o \
./Window.o \
./UIController.o \
./FileSystemUtil.o \
./GUIController.o \
./MainWindow.o \
./MinMax.o \
./main.o  \
./InfoMessageBox.o \
./PawnPromotionMessageBox.o \
./SaveGameMessageBox.o \
./SimpleButton.o \
./SoldierButton.o \
./ColorSelectionView.o \
./DifficultySelectionView.o \
./ModeSelectionView.o \
./GameBoardView.o \
./LoadGameView.o


C_DEPS += \
./CommonStructures.d \
./Commands.d \
./CMDController.d \
./Window.d \
./CommonGUIUtil.d \
./UIController.d \
./FileSystemUtil.d \
./GUIController.d \
./MainWindow.d \
./MinMax.d \
./main.d \
./InfoMessageBox.d \
./PawnPromotionMessageBox.d \
./SaveGameMessageBox.d \
./SimpleButton.d \
./SoldierButton.d \
./ColorSelectionView.d \
./DifficultySelectionView.d \
./ModeSelectionView.d \
./GameBoardView.d \
./LoadGameView.d


#gcc LINUX_SDL_INCLUDE -I"./" -I"./GUIControls" -I"./Views" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	
# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"C:/SDL2/include" -I"C:/CProj/git_workspace" -I"C:/CProj/git_workspace/GUIControls" -I"C:/CProj/git_workspace/Views" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

	@echo 'Finished building: $<'
	@echo ' '

		
USER_OBJS :=

LIBS := -lmingw32 -lSDL2main -lSDL2

all: SDLTest.exe

SDLTest.exe: $(OBJS) $(USER_OBJS)
	gcc -LC:/SDL2/lib -o "SDLTest.exe" $(OBJS) $(USER_OBJS) $(LIBS)
