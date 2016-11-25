#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class Board {

public: 
	Board();
	void makeMove(std::string);
	void makeMove(char, char);
	void print() const;
	bool full() const;
	bool at(char i) const;
	bool operator==(const Board&) const;

private:
	bool* boardData;
	// Has constant capacity of 8

};

#endif // !BOARD_H_
