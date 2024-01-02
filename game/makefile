CC = g++
LDLIBS = -lraylib
CFLAGS = -g -Wall -ggdb3
ENGINE_SRC_DIR = ../engine/src
ENGINE_LIB_DIR = ../engine/include
GAME_SRC_DIR = src
GAME_LIB_DIR = include
OBJ_DIR = obj
LIB = $(wildcard $(ENGINE_LIB_DIR)/*.h) $(wildcard $(GAME_LIB_DIR)/*.h)
ENGINE_SRC := $(wildcard $(ENGINE_SRC_DIR)/*.cpp)
GAME_SRC := $(wildcard $(GAME_SRC_DIR)/*.cpp)
OBJ := $(patsubst $(ENGINE_SRC_DIR)/%, $(OBJ_DIR)/%,$(ENGINE_SRC:.cpp=.o)) $(patsubst $(GAME_SRC_DIR)/%, $(OBJ_DIR)/%,$(GAME_SRC:.cpp=.o))
COMPILE_OBJ = $(CC) $(CFLAGS) -c $< -o $@

EXECUTABLE = "bin/TestGame"

.PHONY: default
default: makedir main

makedir:
	mkdir -p bin
	mkdir -p $(OBJ_DIR)

main: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJ) $(LDLIBS)

# Engine
$(OBJ_DIR)/%.o: $(ENGINE_SRC_DIR)/%.cpp $(LIB)
	$(COMPILE_OBJ)

# Game
$(OBJ_DIR)/%.o: $(GAME_SRC_DIR)/%.cpp $(LIB)
	$(COMPILE_OBJ)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/* $(EXECUTABLE)