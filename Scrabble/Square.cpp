
//Author: Robert Diersing

#include "Square.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Square::Square() : mLetter(1), mWord(1), curtile(NULL), start(false) {}

Square::Square(int mLetter, int mWord, bool start) : mLetter(mLetter), mWord(mWord), curtile(NULL), start(start) {}

bool Square::is_empty() const {
	if (curtile == NULL) {
		return true;
	}
	return false;
}

void Square::placeTile(Tile* tile) {
	if (curtile != NULL) {
		throw invalid_argument("Invalid tile place: square is not empty");
	}
	curtile = tile;
}

int Square::getLetterMultiplier() const {
	return mLetter;
}

int Square::getWordMultiplier() const {
	return mWord;
}

bool Square::is_start() const {
	return start;
}

int Square::getTilePoints() const {
	if (curtile == NULL) {
		throw logic_error("Tried to get points of a null tile");
	}
	return curtile->getPoints();
}

char Square::getTileChar() const {
	if (curtile == NULL) {
		throw logic_error("Tried to get points of a null tile");
	}
	if (curtile->isBlank()) {
		return curtile->getUse();
	}
	return curtile->getLetter();
}