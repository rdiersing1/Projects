
//Author: Robert Diersing

#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>
#include <vector>
#include "Bag.h"

class Player {
public:
	Player(std::string name, Bag*, unsigned);
	void drawTiles();
	bool bagTiles(std::string, Bag*);
	std::vector<int> tilePoints() const;
	std::vector<char> tileLetters() const;
	std::string getname() const;
	Tile* findTile(char tilechar);
	void popTile(Tile*);
	void clearUses();
	std::vector<Tile*> trashTiles(std::string);
	void increseScore(int);
	int getScore() const;
	unsigned handSize() const;

private:
	std::string name;
	std::vector<Tile*> hand;
	int score;
	Bag* mainBag;
	int maxNumTiles;
};

#endif