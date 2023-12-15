# Compiler
CC = g++

#Directories
BIN_DIR := bin
INC_DIR := include
LIB_DIR := lib/sdl2-lib
SRC_DIR := src

# Files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRC_FILES))
EXE_FILE := $(BIN_DIR)/main.exe

# Compiler flags
CFLAGS := -std=c++17 -I$(INC_DIR)

# Linker flags
LDFLAGS := -L$(LIB_DIR) -lmingw32 -lSDL2main -lSDL2 

# Build rule for executable
$(EXE_FILE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Build rule for object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for cleaning the project
clean:
	rm -rf $(BIN_DIR)/*

# Rule for running the executable
run: $(EXE_FILE)
	./$(EXE_FILE)

# all:
# 	g++ -Iinclude -Llib/sdl2-lib -o main src/main.cpp -lmingw32 -lSDL2main -lSDL2 -mwindows