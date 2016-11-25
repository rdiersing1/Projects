#include "Board.h"

using namespace std;

Board::Board() {
	boardData = new bool[9];
	for (unsigned i = 0; i < 9; ++i) {
		boardData[i] = false;
	}
}

void Board::makeMove(string move) {
	stringstream ss(move);
	string coord;
	int num;
	ss >> coord >> num;

	if (num > 3 || num < 0 || coord.size() != 2) {
		throw invalid_argument("Invalid Move Syntax");
	}

	coord.at(0) = toupper(coord.at(0));

	if (!(coord.at(0) > 'A' || coord.at(0) < 'E')) {
		throw invalid_argument("Invalid Move Syntax");
	}

	int i = 0;
	switch (coord.at(1)) {

	case '1': 
		if (coord.at(0) != 'C') {
			throw invalid_argument("Move out of bounds");
		}
		if (boardData[0]) {
			throw invalid_argument("Move intersects another move");
		}
		else {
			boardData[0] = true;
			return;
		}
		break;

	case '2':
		if (coord.at(0) == 'A' || coord.at(0) == 'E') {
			throw invalid_argument("Move out of bounds");
		}

		i = coord.at(0) - 'A';
		for (int j = 0; j < num; ++j) {
			if (i + j > 3) {
				throw invalid_argument("Move goes out of bounds");
			}
			if (boardData[i + j]) {
				throw invalid_argument("Move intersects another move");
			}
		}
		for (int j = 0; j < num; ++j) {
			boardData[i + j] = true;
		}
		break;

	case '3':
		i = coord.at(0) - 'A';
		for (int j = 0; j < num; ++j) {
			if (i + j + 4 >= 9) {
				throw invalid_argument("Move goes out of bounds");
			}
			if (boardData[i + j + 4]) {
				throw invalid_argument("Move intersects another move");
			}
		}
		for (int j = 0; j < num; ++j) {
			boardData[i + j + 4] = true;
		}
		break;
	}
}

void Board::makeMove(char pos, char length) {
	if (pos > 9 || pos < 0) {
		throw logic_error("Invalid pos");
	}
	if (length > 3 || length < 0) {
		throw logic_error("Invalid length");
	}

	if (pos == 1 && length != 1) {
		throw logic_error("Length contradiction");
	}
	if ((pos > 0) && (pos < 4)) {
		for (char i = 1; i < length; ++i) {
			if (i > 3) {
				throw logic_error("Length contradiction");
			}
			if (boardData[i]) {
				throw invalid_argument("Move intersection");
			}
		}
		for (char i = 1; i < length + 1; ++i) {
			boardData[i] = true;
		}
	}
	if ((pos > 3) && (pos < 9)) {
		for (char i = 4; i < length + 3; ++i) {
			if (i > 8) {
				throw logic_error("Length contradiction");
			}
			if (boardData[i]) {
				throw invalid_argument("Move intersection");
			}
		}
		for (char i = 4; i < length + 3; ++i) {
			boardData[i] = true;
		}
	}
}

void Board::print() const  {
	cout << endl;
	cout << "  A B C D E " << endl
		<< "1     ";
	if (!boardData[0]) {
		cout << '|' << endl;
	}
	else {
		cout << static_cast<char>(197) << endl;
	}

	cout << "2   ";
	for (int i = 0; i < 3; ++i) {
		if (!boardData[i + 1]) {
			cout << "| ";
		}
		else {
			cout << static_cast<char>(197) << ' ';
		}
	}
	cout << endl;

	cout << "3 ";
	for (int i = 0; i < 5; ++i) {
		if (!boardData[i + 4]) {
			cout << "| ";
		}
		else {
			cout << static_cast<char>(197) << ' ';
		}
	}
	cout << endl;
}

bool Board::full() const  {
	for (int i = 0; i < 9; ++i) {
		if (!boardData[i]) {
			return false;
		}
	}
	return true;
}

bool Board::at(char i) const {
	if (i < 0 || i > 8) {
		throw logic_error("Board .at() is out of range");
	}
	return boardData[i];
}

bool Board::operator==(const Board& rhs) const {
	for (char i = 0; i < 9; ++i) {
		if (boardData[i] != rhs.boardData[i]) {
			return false;
		}
	}
	return true;
}