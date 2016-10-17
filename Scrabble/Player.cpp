
//Author: Robert Diersing

#include "Player.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;

Player::Player(string name, Bag* bag, unsigned k) : name(name) , score(0), mainBag(bag), maxNumTiles(k) {}

//automatically draw tiles untill either the bag is empty or the player has k tiles
void Player::drawTiles() {
	int currNumTiles = hand.size();
	set<Tile*> drawnTiles = mainBag->drawTiles(maxNumTiles - currNumTiles);
	for (set<Tile*>::iterator it = drawnTiles.begin(); it != drawnTiles.end(); ++it) {
		hand.push_back(*it);
	}
}

//return a vector of integers that correspond to the players hand
vector<int> Player::tilePoints() const {
	vector<int> pts;
	for (unsigned i = 0; i < hand.size(); ++i) {
		pts.push_back((hand.at(i))->getPoints());
	}
	return pts;
}

//returns a vector of characters that correspond to the players hand
vector<char> Player::tileLetters() const {
	vector<char> letters;
	for (unsigned i = 0; i < hand.size(); ++i) {
		letters.push_back((hand.at(i))->getLetter());
	}
	return letters;
}

//Prints the players name
string Player::getname() const {
	return name;
}

//Removes some string of tiles from the players hand, and puts them in the bag. Returns false if illegal
bool Player::bagTiles(string tilestr, Bag *bag) {
	vector<Tile*> trashTiles;							//Creates a vector of tiles to put back in the bag
	try {
		trashTiles = this->trashTiles(tilestr);
	}
	catch (invalid_argument a) {
		return false;
	}
	
	bag->addTiles(trashTiles);
	return true;
}

//Removes string of tiles from the players hand, and returns a vector of the returned tiles.
//If it cannot find the files it throws a invalid argument without altering anything.
vector<Tile*> Player::trashTiles(string tilestr) {		//Throws exception if cant find tiles
	vector<Tile*> trashTiles;
	vector<Tile*> tempHand;
	tempHand = hand;

	for (unsigned i = 0; i < tilestr.size(); ++i) {		//loops through input string
		char remv = toupper(tilestr.at(i));
		bool tfound = false;

		if (!isspace(remv)) {							//checks if string has whitespace
			for (vector<Tile*>::iterator it = tempHand.begin(); it != tempHand.end() && !tfound; ++it) {	//loops through vector for every input string
				char tileLetter = (*it)->getLetter();
				if (tileLetter == '?') {				//if the tile is blank set the tileLetter to the use
					tileLetter = (*it)->getUse();
				}

				if (tileLetter == remv) {
					tfound = true;
					trashTiles.push_back(*it);
					it = tempHand.erase(it);
					break;
				}
			}
			if (!tfound) {
				throw invalid_argument("Trying to use a nonexisting tile");
			}
		}
	}

	hand = tempHand;
	return trashTiles;
}

//Returns a pointer to the tile it found. If it cannot find a tile, it gives an error.
Tile* Player::findTile(char tilechar) {
	tilechar = toupper(tilechar);						//what dose this do to '?'
	for (unsigned i = 0; i < hand.size(); ++i) {		//finding the tile
		if (tilechar == hand.at(i)->getLetter()) {
			return hand.at(i);							//If you find the tile..
		}
	}

	throw invalid_argument("Trying to use nonexising tile: " + tilechar);
	return NULL; //to appease compiler
}

//Removes the tile from the hand
void Player::popTile(Tile* tiletopop) {
	for (vector<Tile*>::iterator it = hand.begin(); it != hand.end(); ++it) {
		if ((*it) == tiletopop) {
			hand.erase(it);
			return;
		}
	}
	throw invalid_argument("Trying to pop a tile that is not in the hand");
}

//Sets all of the uses back to question marks
void Player::clearUses() {
	for (unsigned i = 0; i < hand.size(); ++i) {
		if (hand.at(i)->isBlank()) {
			hand.at(i)->useAs('?');
		}
	}
}

//increses score by integer ammount
void Player::increseScore(int i) {
	score += i;
}

//gets the score
int Player::getScore() const {
	return score;
}

unsigned Player::handSize() const {
	return hand.size();
}
