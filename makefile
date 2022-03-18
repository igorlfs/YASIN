CC = clang++

# -fstandalone-debug -> debug with gdb but compiled with clang
CFLAGS = -Wall -Wextra -std=c++17 -g -fstandalone-debug
LFLAGS = -lncurses

BUILD = build
INCLUDE = include
SRC = src

TARGET = $(BUILD)/binary

$(TARGET): $(BUILD)/snake.o $(BUILD)/board.o $(BUILD)/game.o $(BUILD)/main.o
		$(CC) $(LFLAGS) -o $(TARGET) $(BUILD)/*.o

$(BUILD)/snake.o: $(INCLUDE)/drawable/drawable.hpp $(INCLUDE)/drawable/snake.hpp $(SRC)/snake.cpp
		$(CC) $(CFLAGS) -I$(INCLUDE)/drawable  -c $(SRC)/snake.cpp -o $(BUILD)/snake.o

$(BUILD)/board.o: $(INCLUDE)/board.hpp $(SRC)/board.cpp
		$(CC) $(CFLAGS) -I$(INCLUDE) -c $(SRC)/board.cpp -o $(BUILD)/board.o

$(BUILD)/game.o: $(INCLUDE)/board.hpp $(INCLUDE)/drawable/food.hpp $(INCLUDE)/drawable/snake.hpp $(INCLUDE)/game.hpp $(INCLUDE)/random.hpp $(SRC)/game.cpp
		$(CC) $(CFLAGS) -I$(INCLUDE)/drawable -I$(INCLUDE) -c $(SRC)/game.cpp -o $(BUILD)/game.o

$(BUILD)/main.o: $(INCLUDE)/game.hpp $(SRC)/main.cpp
		$(CC) $(CFLAGS) -I$(INCLUDE)/drawable -I$(INCLUDE) -c $(SRC)/main.cpp -o $(BUILD)/main.o

clean:
	rm -rf $(BUILD)/*
