
//Author: Robert Diersing

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "Player.h"
#include "Bag.h"
#include "Board.h"
#include <vector>

class UserInterface {
public:
	void printIntro(std::vector<Player*> &, Bag*, unsigned) const;
	void printHand(const Player &);
	void printBoard(const Board &);
	void printInstr();
	void printScores(const std::vector<Player*> &);
	void makeMove(std::vector<Player*>, unsigned, Board*, Bag*, unsigned&, unsigned);
	void deletePlayers(std::vector<Player*>);
private:
	void clearScreen() const;

};

#endif // !USERINTERFACE_H_
