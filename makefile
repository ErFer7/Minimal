COMPILER = g++
DEBUG_FLAGS = -g -ggdb3
RELEASE_FLAGS = -O3

ENGINE_LIBS = -lraylib
FLAGS = -Wall -Wextra -pedantic -std=c++20

ENGINE_SRC_DIR = ./engine/src
ENGINE_LIB_DIR = ./engine/include

GAME_SRC_DIR = ./runtime-test/src
GAME_LIB_DIR = ./runtime-test/include

OBJ_DIR = ./runtime-test/obj
BIN_DIR = ./runtime-test/bin
LIB = $(shell find $(ENGINE_LIB_DIR) -name '*.h') $(shell find $(GAME_LIB_DIR) -name '*.h')
ENGINE_SRC := $(shell find $(ENGINE_SRC_DIR) -name '*.cpp')
GAME_SRC := $(shell find $(GAME_SRC_DIR) -name '*.cpp')
OBJ := $(patsubst $(ENGINE_SRC_DIR)/%, $(OBJ_DIR)/%,$(ENGINE_SRC:.cpp=.o)) $(patsubst $(GAME_SRC_DIR)/%, $(OBJ_DIR)/%,$(GAME_SRC:.cpp=.o))
COMPILE_OBJ = $(COMPILER) $(CFLAGS) -c $< -o $@

NAME = TestGame
EXECUTABLE = $(BIN_DIR)/$(NAME)

.PHONY: default
default: makedir main

makedir:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)

main: $(OBJ)
	$(COMPILER) $(CFLAGS) -o $(EXECUTABLE) $(OBJ) $(ENGINE_LIBS)

# Engine
$(OBJ_DIR)/%.o: $(ENGINE_SRC_DIR)/%.cpp $(LIB)
	mkdir -p $(@D)
	$(COMPILE_OBJ)

# Game
$(OBJ_DIR)/%.o: $(GAME_SRC_DIR)/%.cpp $(LIB)
	mkdir -p $(@D)
	$(COMPILE_OBJ)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/* $(EXECUTABLE)