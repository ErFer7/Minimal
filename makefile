CC = g++
LDLIBS = -lraylib
CFLAGS = -g -Wall -ggdb3
ENGINE_SRC_DIR = ./engine/src
ENGINE_LIB_DIR = ./engine/include
GAME_SRC_DIR = ./game/src
GAME_LIB_DIR = ./game/include
OBJ_DIR = ./game/obj
LIB = $(shell find $(ENGINE_LIB_DIR) -name '*.h') $(shell find $(GAME_LIB_DIR) -name '*.h')
ENGINE_SRC := $(shell find $(ENGINE_SRC_DIR) -name '*.cpp')
GAME_SRC := $(shell find $(GAME_SRC_DIR) -name '*.cpp')
OBJ := $(patsubst $(ENGINE_SRC_DIR)/%, $(OBJ_DIR)/%,$(ENGINE_SRC:.cpp=.o)) $(patsubst $(GAME_SRC_DIR)/%, $(OBJ_DIR)/%,$(GAME_SRC:.cpp=.o))
COMPILE_OBJ = $(CC) $(CFLAGS) -c $< -o $@

EXECUTABLE = "./game/bin/TestGame"

.PHONY: default
default: makedir main

makedir:
	mkdir -p bin
	mkdir -p $(OBJ_DIR)

main: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJ) $(LDLIBS)

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