#ifndef NIMBAI_H_
#define NIMBAI_H_

#include <string>
#include <iostream>
#include <vector>

#include "Board.h"

struct gNode {
	gNode(Board b, bool t) : board(b), score(0), turn(t) {}
	Board board;
	unsigned score;
	bool turn;
	std::vector<gNode*> children;
};

class nimbAi {

public:
	nimbAi(bool);
	//~nimbAi();
	void findMoves(gNode*);
	void findMoveHelper(gNode*, char, char);
	void getMove(Board, char&, char&);

private:
	gNode* gtRoot;
	gNode* gtCurr;

	//void deleteAll();

};

#endif // !NIMBAI_H_
