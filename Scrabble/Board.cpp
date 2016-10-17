/*
 * Board.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe and Robert Diersing
 */

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Board.h"

using namespace std;

//Board constructor
Board::Board (string board_file_name, Dictionary* dict) : empty(true), dict(dict)
{
	ifstream boardFile (board_file_name.c_str());
	string row;

	_x = _y = _startx = _starty = 0; // to appease compiler
	if (!boardFile.is_open())
		throw invalid_argument("Cannot open file: " + board_file_name);
	getline (boardFile, row);
	stringstream s1 (row);
	s1 >> _x >> _y;
	getline (boardFile, row);
	stringstream s2 (row);
	s2 >> _startx >> _starty;
	_startx --; _starty --;  // coordinates from 0 in array

	squareMatrix.resize(_y);
	for (int i = 0; i < _y; ++i) {
		squareMatrix.at(i).resize(_x);
	}

	Square sSquare;												//Creates all possible types of squares
	Square ldSquare(2, 1, false);
	Square ltSquare(3, 1, false);
	Square dSquare(1, 2, false);
	Square tSquare(1, 3, false);
	Square stSquare(1, 1, true);

	for (int i = 0 ; i < _y; ++ i)
	{
		getline (boardFile, row);
		for (int j = 0; j < _x; ++ j)							//Inserts copies of possible squares in matrix
		{
			if (i == _starty && j == _startx) { squareMatrix.at(i).at(j) = stSquare; }
			else switch (row[j]) {
			case '.': squareMatrix.at(i).at(j) = sSquare;	
			break;
			case '2': squareMatrix.at(i).at(j) = ldSquare;
			break;
			case '3' : squareMatrix.at(i).at(j) = ltSquare;
			break;
			case 'd' : squareMatrix.at(i).at(j) = dSquare;
			break;
			case 't' : squareMatrix.at(i).at(j) = tSquare;
			break;
			default:
				string error = "Improper character in Board file: ";
				throw invalid_argument(error + row[j]);
			}
		}
	}
	boardFile.close ();
}

//converts board into a matrix of strings to be read by the io
vector < vector<string> > Board::readBoard() const {

	vector < vector<string> > stringBoard;
	stringBoard.resize(_y);
	for (int i = 0; i < _y; ++i) {
		stringBoard.at(i).resize(_x);
	}

	for (int i = 0; i < _y; ++i) {
		for (int j = 0; j < _x; ++j) {
			Square currSquare = squareMatrix.at(i).at(j);
			if (currSquare.is_empty()) {
				if (i == _starty && j == _startx) {
					stringBoard.at(i).at(j) = "***";
				}
				else if (currSquare.getLetterMultiplier() == 1 && currSquare.getWordMultiplier() == 1) {
					stringBoard.at(i).at(j) = "...";
				}
				else if (currSquare.getLetterMultiplier() == 2) {
					stringBoard.at(i).at(j) = "2L ";
				}
				else if (currSquare.getLetterMultiplier() == 3) {
					stringBoard.at(i).at(j) = "3L ";
				}
				else if (currSquare.getWordMultiplier() == 2) {
					stringBoard.at(i).at(j) = "2W ";
				}
				else {
					stringBoard.at(i).at(j) = "3W ";
				}
			}
			else {
				char letter = currSquare.getTileChar();
				if (currSquare.getTilePoints() == 10) {
					string cuString;
					cuString += letter;
					cuString += "10";
					stringBoard.at(i).at(j) = cuString;
				}
				else {
					char pts = currSquare.getTilePoints() + '0';
					string currString;
					currString += letter;
					currString += pts;
					currString += ' ';
					stringBoard.at(i).at(j) = currString;
				}
			}
		}
	}
	return stringBoard;
}

void Board::evaluate(const vector < vector <Square> > &tempSquareMatrix, bool up, bool left, bool vertical, int y, int x, int &si) {
	if (up && left) {
		throw invalid_argument("Bool up and bool left asserted in Board::evaluate()");
	}
	if ((up && !vertical) || (left && vertical)) {
		throw invalid_argument("up && !vertical || left && vertical passed in Board::evaluate()");
	}

	string word;
	int wordscore = 0;
	int wordmultp = 1;

	if (up) {
		while (!tempSquareMatrix.at(y).at(x).is_empty()) {
			--y;
			if (y < 0) {
				break;
			}
		}
		++y;
	}
	else if (left) {
		while (!tempSquareMatrix.at(y).at(x).is_empty()) {
			--x;
			if (x < 0) {
				break;
			}
		}
		++x;
	}
	if (vertical) {
		while (!tempSquareMatrix.at(y).at(x).is_empty()) {
			word += tolower(tempSquareMatrix.at(y).at(x).getTileChar());
			wordscore += tempSquareMatrix.at(y).at(x).getTilePoints() * tempSquareMatrix.at(y).at(x).getLetterMultiplier();
			wordmultp *= tempSquareMatrix.at(y).at(x).getWordMultiplier();
			++y;
			if (y + 1 > _y) {
				break;
			}
		}
		--y;
	}
	else {
		while (!tempSquareMatrix.at(y).at(x).is_empty()) {
			word += tolower(tempSquareMatrix.at(y).at(x).getTileChar());
			wordscore += tempSquareMatrix.at(y).at(x).getTilePoints() * tempSquareMatrix.at(y).at(x).getLetterMultiplier();
			wordmultp *= tempSquareMatrix.at(y).at(x).getWordMultiplier();
			++x;
			if (x + 1 > _x) {
				break;
			}
		}
		--x;
	}
	if (word.size() <= 1) {
		return;
	}

	if (!dict->is_valid(word)) {
		throw invalid_argument("That is not a valid word");
	}

	si += wordscore * wordmultp;
}

//Places tiles on the board. If the move is illegal it throws an invalid argument
void Board::placeTiles(string instructions, Player *player, unsigned numTiles) {

	stringstream command(instructions);				//Initializes all of the varables
	char orientation;
	int ycoord;
	int xcoord;
	int ytrav;
	int xtrav;
	vector<int> locTiles;
	string tilestr;
	bool vertical;
	vector<bool> neartiles; // up, left, down, right
	vector <vector <Square> > tempSquareMatrix;
	vector<Tile*> tilesToPlace;
	string word;
	int scoreincrementer = 0;
	bool isnearby = false;

	command >> orientation >> ycoord >> xcoord >> tilestr;	//Interprates instructions
	--ycoord;												//Remember offset. use ++ to increment
	--xcoord;
	ytrav = ycoord;
	xtrav = xcoord;

	//recognizes any starting errors
	if (!(orientation == '|' || orientation == '-')) {	//throws invalid argument if the orientation is not right
		throw invalid_argument("Incorrect command");
	}
	if (ycoord > _y || xcoord > _x) {					//throws invalid argument if the location is off of the board
		throw invalid_argument("The location not on the board");
	}
	if (ycoord < 0 || xcoord < 0) {
		throw invalid_argument("The location not on the board");
	}
	if (empty && (ycoord != _starty || xcoord != _startx)) {
		throw invalid_argument("The first move is not on the starting location");
	}
	if (!squareMatrix.at(ycoord).at(xcoord).is_empty()) {				//if its blocked throw error
		throw invalid_argument("You cannot place your first tile over another tile");
	}
	if (orientation == '|') {							//converts orientation to a bool
		vertical = true;
	}
	else {
		vertical = false;
	}

	Player tempPlayer = *player;						//FIXME check for memory leaks!!

	unsigned j = 0;
	for (unsigned i = 0; i < tilestr.size(); ++i) {

		tilesToPlace.push_back(tempPlayer.findTile(tilestr.at(i)));	//Will give an invalid argument if it dosent find the tile
		tempPlayer.popTile(tilesToPlace.at(tilesToPlace.size() - 1));
		if (tilestr.at(i) == '?') {
			++i;
			if (i > tilestr.size()) {
				throw invalid_argument("Invalid command");
			}
			tilesToPlace.at(j)->useAs(tilestr.at(i));
		}
		++j;
	}

	tempSquareMatrix = squareMatrix;					//creates a dummy matrix that wont actually effect the real matrix
	
	if (!squareMatrix.at(ycoord).at(xcoord).is_empty()) {
		throw invalid_argument("Not a valid move");
	}

	for (unsigned i = 0; i < tilesToPlace.size(); ++i) {						//Places tiles in temp matrix

		if (xtrav < 0 || xtrav > _x - 1 || ytrav < 0 || ytrav > _y - 1) {
			throw invalid_argument("Entire word does not fit on board");
		}
		else if (!tempSquareMatrix.at(ytrav).at(xtrav).is_empty()) {
			--i;
		}
		else {
			tempSquareMatrix.at(ytrav).at(xtrav).placeTile(tilesToPlace.at(i)); //places a tile in the temp matrix
			if (vertical) {
				locTiles.push_back(ytrav);
			}
			else {
				locTiles.push_back(xtrav);
			}
		}

		if (vertical) {
			++ytrav;
		}
		else {
			++xtrav;
		}

		if (ytrav > _y || xtrav > _x) {
			throw invalid_argument("Word streached out of bounds");
		}
	}

	//evaluate paramaters:  tempSquareMatrix, bool up, bool left, bool vertical, int y, int x, int scoreincrementor
	// checkNearby: up, left, down, right and bool isnearby;

	ytrav = ycoord;
	xtrav = xcoord;
	
	neartiles = checkNearby(ytrav, xtrav, isnearby);
	if (vertical) {
		evaluate(tempSquareMatrix, neartiles.at(0), false, vertical, ytrav, xtrav, scoreincrementer);
		vertical = false;
		for (unsigned i = 0; i < locTiles.size(); ++i) {
			ytrav = locTiles.at(i);
			neartiles = checkNearby(ytrav, xtrav, isnearby);
			evaluate(tempSquareMatrix, false, neartiles.at(1), vertical, ytrav, xtrav, scoreincrementer);
			if (ytrav > _y) {
				break;
			}
		}
		vertical = true;
	}
	else {
		evaluate(tempSquareMatrix, false, neartiles.at(1), vertical, ytrav, xtrav, scoreincrementer);
		vertical = true;
		for (unsigned i = 0; i < locTiles.size(); ++i) {
			xtrav = locTiles.at(i);
			neartiles = checkNearby(ytrav, xtrav, isnearby);
			evaluate(tempSquareMatrix, neartiles.at(0), false , vertical, ytrav, xtrav, scoreincrementer);
			if (xtrav > _x) {
				break;
			}
		}
		vertical = false;
	}

	if (empty) {
		empty = false;									//changes empty value when the game starts
	}
	else {
		if (!isnearby) {
			throw invalid_argument("Invalid valid tile placement");
		}
	}

	if (tilesToPlace.size() == numTiles) {
		scoreincrementer += 50;
	}
	cout << player->getname() << " scored " << scoreincrementer << " points!" << endl;

	player->increseScore(scoreincrementer);
	this->insertTiles(tilesToPlace, vertical, ycoord, xcoord, player);
}

//Inserts tiles starting at x and y. Also pops the tiles from the player hand. WILL NEVER THROW AN ERROR
void Board::insertTiles(vector<Tile*> tilesToInsert, bool vertical, int y, int x, Player* player) {

	int j = 0;
	if (vertical) {
		for (unsigned i = 0; i < tilesToInsert.size(); ++i) {	//inserts tiles vertically going down
			if (squareMatrix.at(y + j).at(x).is_empty()) {
				squareMatrix.at(y + j).at(x).placeTile(tilesToInsert.at(i));
				player->popTile(tilesToInsert.at(i));
			}
			else {
				--i;
			}
			++j;
		}
	}
	else {
		for (unsigned i = 0; i < tilesToInsert.size(); ++i) {	//inserts tiles horizontally
			if (squareMatrix.at(y).at(x + j).is_empty()) {
				squareMatrix.at(y).at(x + j).placeTile(tilesToInsert.at(i));
				player->popTile(tilesToInsert.at(i));
			}
			else {
				--i;
			}
			++j;
		}
	}
}

//Throws an invalid argument if there are no tiles nearby
vector<bool> Board::checkNearby(int y, int x, bool &isnearby) const {
	vector<bool> nearby(4, false); // up, left, down, right

	if (empty) {
		return nearby;
	}
	bool ncxu = false;		//dont check x up ect...
	bool ncxd = false;
	bool ncyu = false;
	bool ncyd = false;

	if (x == 0) {
		ncxu = true;
	}
	if (y == 0) {
		ncyu = true;
	}
	if (x + 1 == _x) {
		ncxd = true;
	}
	if (y + 1 == _y) {
		ncyd = true;
	}

	if (!ncxu) {
		if (!squareMatrix.at(y).at(x - 1).is_empty()) {
			isnearby = true;
			nearby.at(1) = true;
		}
	}
	if (!ncyu) {
		if (!squareMatrix.at(y - 1).at(x).is_empty()) {
			isnearby = true;
			nearby.at(0) = true;
		}
	}
	if (!ncyd) {
		if (!squareMatrix.at(y + 1).at(x).is_empty()) {
			isnearby = true;
			nearby.at(2) = true;
		}
	}
	if (!ncxd) {
		if (!squareMatrix.at(y).at(x + 1).is_empty()) {
			isnearby = true;
			nearby.at(3) = true;

		}
	}
	return nearby;
}
