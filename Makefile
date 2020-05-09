CC = g++

STD_LIBS = -lstdc++

FLAGS = -std=c++17 -g -Wall -Wextra -Werror $(LIBS) -o
BUILD_DIR = ./bin
SRC_DIR = ./src
LIBS = $(STD_LIBS)
INCLUDE = $(SRC_DIR)/main.cpp
EXEC = vector

all:
	$(CC) $(INCLUDE) $(FLAGS) $(BUILD_DIR)/$(EXEC)

clean:
	rm $(BUILD_DIR)/*

install:
	cp $(BUILD_DIR)/$(EXEC) /bin

run:
	$(BUILD_DIR)/$(EXEC)