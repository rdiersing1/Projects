/*
 * Board.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe and Robert Diersing
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include <vector>
#include "Square.h"
#include "Player.h"
#include "Dictionary.h"

class Board {
public:
	Board (std::string board_file_name, Dictionary*);
	std::vector < std::vector<std::string> > readBoard() const;
	void placeTiles(std::string, Player*, unsigned);
	std::vector<bool> checkNearby(int, int, bool &) const;

private:
	int _x, _y;
	int _startx, _starty;
	std::vector < std::vector<Square> > squareMatrix;
	bool empty;
	Dictionary* dict;

	void insertTiles(std::vector<Tile*>, bool, int, int, Player*);
	void evaluate(const std::vector < std::vector <Square> >&, bool, bool, bool, int, int, int&);
};


#endif /* BOARD_H_ */
