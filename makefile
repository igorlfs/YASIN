CC = clang++

OBJ = obj
INCLUDE = lib
SRC = src

CFLAGS = -Wall -Wextra -Wshadow -Wpedantic -std=c++20 -g -fstandalone-debug -I$(INCLUDE) -c
LFLAGS = -lncurses

TARGET = binary

.PHONY: clean obj

$(TARGET): obj $(OBJ)/snake.o $(OBJ)/board.o $(OBJ)/game.o $(OBJ)/main.o
		$(CC) $(LFLAGS) -o $(TARGET) $(OBJ)/*.o

$(OBJ)/snake.o: $(INCLUDE)/drawable/drawable.hpp $(INCLUDE)/drawable/snake.hpp $(SRC)/snake.cpp
		$(CC) -I$(INCLUDE)/drawable $(CFLAGS) $(SRC)/snake.cpp -o $(OBJ)/snake.o

$(OBJ)/board.o: $(INCLUDE)/board.hpp $(SRC)/board.cpp
		$(CC) $(CFLAGS) -c $(SRC)/board.cpp -o $(OBJ)/board.o

$(OBJ)/game.o: $(INCLUDE)/board.hpp $(INCLUDE)/drawable/food.hpp $(INCLUDE)/drawable/snake.hpp $(INCLUDE)/game.hpp $(INCLUDE)/random.hpp $(SRC)/game.cpp
		$(CC) -I$(INCLUDE)/drawable $(CFLAGS) -c $(SRC)/game.cpp -o $(OBJ)/game.o

$(OBJ)/main.o: $(INCLUDE)/game.hpp $(SRC)/main.cpp
		$(CC) -I$(INCLUDE)/drawable $(CFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o
obj:
	@ test -d $(OBJ) && true || mkdir -p $(OBJ)

clean:
	rm -rf ./$(OBJ)/*.o $(TARGET) *~
	test -d $(OBJ) && rmdir $(OBJ) || true
	test -f $(TARGET) && rm $(TARGET) || true
