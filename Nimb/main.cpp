#include <iostream>
#include <string>

#include "Board.h"
#include "NimbAi.h"

using namespace std;

int main() {
	Board board;
	bool p1 = false;
	string names[2];
	nimbAi* aip1;
	nimbAi* aip2;
	bool aipos[2];
	
	cout << "Enter Player1's Name: ";
	getline(cin, names[0]);
	cout << endl;

	if (names[0].at(0) == 'A' && names[0].at(1) == 'I') {
		aipos[0] = true;
		aip1 = new nimbAi(true);
	}
	else {
		aipos[0] = false;
	}

	cout << "Enter Player2's Name: ";
	getline(cin, names[1]);
	cout << endl;

	if (names[1].at(0) == 'A' && names[1].at(1) == 'I') {
		aipos[1] = true;
		aip2 = new nimbAi(true);
	}
	else {
		aipos[1] = false;
	}

	board.print();

	do {
		if (p1) {
			p1 = false;
		}
		else {
			p1 = true;
		}
		cout << "Player ";
		if (p1) {
			cout << names[0];
		}
		else {
			cout << names[1];
		}
		cout << "'s turn" << endl;

		bool next = false;
		do {
			if ((p1 && aipos[0]) || (!p1 && aipos[1])) {
				char pos;
				char length;
				if (p1) {
					aip1->getMove(board, pos, length);
				}
				else {
					aip2->getMove(board, pos, length);
				}
				board.makeMove(pos, length);
				next = true;
			}
			else {
				try {
					string m;
					getline(cin, m);
					board.makeMove(m);
					next = true;
				}
				catch (invalid_argument &ia) {
					cerr << ia.what() << endl;
					cerr << "Try again" << endl;
				}
			}

		} while (!next);
		board.print();

	} while (!board.full());
	
	if (p1) {
		cout << names[1] << " is the winner!" << endl;
	}
	else {
		cout << names[0] << "is the winner!" << endl;
	}

	return 0;
}