CC = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: Scrabble
	-@echo "--All Built--"

Scrabble: Scrabble.cpp Bag.o Bag.h Board.o Board.h Player.o Player.h UserInterface.o UserInterface.h Dictionary.o Dictionary.h Square.o Square.h Tile.h
	$(CC) $(CPPFLAGS) Scrabble.cpp Bag.o Board.o Player.o UserInterface.o Dictionary.o Square.o -o $@

UserInterface.o: UserInterface.cpp UserInterface.h Player.o Player.h Bag.o Bag.h Board.o Board.h
	$(CC) $(CPPFLAGS) -c UserInterface.cpp Player.o Bag.o Board.o -o $@

Board.o: Board.cpp Board.h Dictionary.o Dictionary.h Player.o Player.h Square.o Square.h
	$(CC) $(CPPFLAGS) -c Board.cpp Square.o Player.o -o $@

Player.o: Player.cpp Player.h
	$(CC) $(CPPFLAGS) -c Player.cpp -o $@

Square.o: Square.cpp Square.h Tile.h
	$(CC) $(CPPFLAGS) -c Square.cpp -o $@

Dictionary.o: Dictionary.cpp Dictionary.h
	$(CC) $(CPPFLAGS) -c Dictionary.cpp -o $@

Bag.o: Bag.cpp Bag.h
	$(CC) $(CPPFLAGS) -c Bag.cpp -o $@