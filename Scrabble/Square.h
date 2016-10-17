
//Author: Robert Diersing

#ifndef SQUARE_H_
#define SQUARE_H_

#include "Tile.h"
#include <stdexcept>

class Square {
public:
	Square();
	Square(int, int, bool);
	bool is_empty() const;
	void placeTile(Tile*);
	int getLetterMultiplier() const;
	int getWordMultiplier() const;
	bool is_start() const;
	int getTilePoints() const;
	char getTileChar() const;

private:
	int mLetter;
	int mWord;
	Tile* curtile;
	bool start;
};

#endif // !SQUARE_H_
