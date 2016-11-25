#include "NimbAi.h"

using namespace std;

nimbAi::nimbAi(bool p1) {
	cout << "Building AI" << endl;
	Board b;
	gtRoot = new gNode(b, p1);
	cerr << "About to find moves" << endl;
	findMoves(gtRoot);
	gtCurr = gtRoot;
}

void nimbAi::findMoves(gNode* n) {
	cerr << "Entering FindMoves" << endl;
	if (n->board.full()) {
		if (n->turn) {
			n->score = 0;
		}
		else {
			n->score = 1;
		}
		return;
	}

	for (char i = 0; i < 9; ++i) {
		if (!(n->board.at(i))) {
			findMoveHelper(n, i, 1);	//bug
		}
		if (!(n->board.at(i)) && (i == 1 || i == 2 || (i > 3 && i < 8))) {
			findMoveHelper(n, i, 2);
		}
		if (!(n->board.at(i)) && (i == 1 || (i > 3 && i < 7))) {
			findMoveHelper(n, i, 3);
		}
	}
	return;
}

void nimbAi::findMoveHelper(gNode* parent, char i, char l) {
	cerr << "Entering Find Move Helper" << endl;
	Board nboard = parent->board;
	try {
		nboard.makeMove(i, l);
		gNode* child = new gNode(nboard, !(parent->turn));
		parent->children.push_back(child);
		
		findMoves(child);
		
		unsigned scoreSum = 0;
		for (int j = 0; j < parent->children.size(); ++j) {
			scoreSum += parent->children.at(i)->score;
		}
		parent->score = scoreSum;
	}
	catch (invalid_argument &a) {}
}

void nimbAi::getMove(Board board, char& pos, char& length) {
	for (unsigned i = 0; i < gtCurr->children.size(); ++i) {
		if (board == gtCurr->children.at(i)->board) {
			gtCurr = gtCurr->children.at(i);
			break;
		}
	}

	unsigned max = 0;
	gNode* bestMove = gtCurr;
	Board bestBoard;

	for (unsigned i = 0; i < gtCurr->children.size(); ++i) {
		if (gtCurr->children.at(i)->score > max) {
			max = gtCurr->children.at(i)->score;
			bestMove = gtCurr->children.at(i);
			bestBoard = bestMove->board;
		}
	}

	for (char i = 0; i < 9; ++i) {
		if (bestBoard.at(i) != board.at(i)) {
			pos = i;
			break;
		}
	}
	length = 1;
	for (char i = 1; i < 3; ++i) {
		if (i + pos < 9) {
			if (bestBoard.at(i + pos) != board.at(i + pos)) {
				length = i + 1;
			}
			else {
				break;
			}
		}
	}
	gtCurr = bestMove;
}