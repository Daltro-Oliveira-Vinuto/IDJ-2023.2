run: clear compile_and_assemble link  load #load_on_valgrind open_valgrind_txt

all: clear compile_and_assemble link load 

clear_objects:
	mv *.o ./trash

clear:
	clear

OBJS := 	src/*.cpp

OBJ_NAME := main.exe

C++ := g++

# only for windows:
# INCLUDE_PATHS := -IC:\SDL-2.28.2\include\SDL2

# only for windows:
# LIBRARY_PATHS := -LC:\SDL-2.28.2\lib

INCLUDE_PATHS := -I/usr/include/SDL2 -Iinclude/

LIBRARY_PATHS := 

# to show only windows screen add -mwindows to LINKER_FLAGS on Windows
LINKER_FLAGS := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

# add -Wextra to see extra warnings
COMPILE_FLAGS := -Wall -std=c++17 -g

compile_assemble_link: $(OBJS)
	$(C++) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) $(COMPILE_FLAGS) -o $(OBJ_NAME)

load:
	./$(OBJ_NAME)


compile_and_assemble:
	$(C++) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILE_FLAGS) -c 


link: 
	$(C++) *.o $(LINKER_FLAGS) -o $(OBJ_NAME)  


VALGRIND_FLAGS := --leak-check=full --log-file=valgrind.txt   #--track-origins=yes   --show-leak-kinds=all  

load_on_valgrind:
	valgrind $(VALGRIND_FLAGS) ./$(OBJ_NAME)

clean:
	rm -f -r *.o bin/*.exe *.exe

clean_o:
	rm -f -r *.o

open_valgrind_txt:
	subl valgrind.txt

debug:
	gdb  main.exe -ex "b 1"  -ex "r" -ex "layout src"  main.exe 
