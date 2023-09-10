all: clear compile_assemble_link run

clear:
	cls

OBJS = main.cpp

OBJ_NAME = main.exe 

CC = g++

INCLUDE_PATHS = -IC:\SDL-2.28.2\include\SDL2

LIBRARY_PATHS = -LC:\SDL-2.28.2\lib

# to show only windows screen add -mwindows to LINKER_FLAGS
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

# add -Wextra to see extra warnings
COMPILE_FLAGS = -Wall -std=c++17

compile_assemble_link: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) $(COMPILE_FLAGS) -o $(OBJ_NAME)

run:
	$(OBJ_NAME)
