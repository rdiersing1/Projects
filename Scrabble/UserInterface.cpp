
//Author: Robert Diersing

#include "UserInterface.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

const bool CLEAR_SCREEN = true;

void UserInterface::clearScreen() const {
	//cout << endl;

	//if (CLEAR_SCREEN)
	//{
	//	cout << "\033c";
	//}

	//cout << endl;

	//return;
}

void UserInterface::printIntro(vector<Player*> &players, Bag* bagPtr, unsigned Ktiles) const {
	bool invalidInput = false;
	int numPlayers = 0;

	cout << "Wellcome to Scrabble!" << endl;

	do {
		clearScreen();					//Will be implemented if I can get the clearScreen function working
		if (invalidInput) {				//Loops to get a valid number of players
			cout << "That was an invalid input, you must enter a number between 1 and 8" << endl;
		}
		string input;
		cout << "Enter number of players (1-8): ";
		getline(cin, input);
		cout << endl;
		stringstream ssinput(input);	//use stringstream in order to avoid error with <<
		ssinput >> numPlayers;

		if (numPlayers > 8 || numPlayers < 1) {
			invalidInput = true;
		}
		else {
			invalidInput = false;
		}
	} 
	while (invalidInput);

	for (int i = 0; i < numPlayers; ++i) {	//Loops to get the names of all the players
		string playername;
		cout << "Enter Player" << i + 1 << "'s name: ";
		getline(cin, playername);
		Player* currPlayer = new Player(playername, bagPtr, Ktiles);	//Players are actually constructed in this function
		currPlayer->drawTiles();
		players.push_back(currPlayer);
	}
}

void UserInterface::printHand(const Player &currplayer) {
	vector<char> handChars = currplayer.tileLetters();
	vector<int> handPts = currplayer.tilePoints();

	if (handChars.size() != handPts.size()) {			//Makes sure i didnt mess up in other things
		throw logic_error("handChars != handPts, error most likley in tileLetters or tilePoitns");
	}
	cout << "Your current tiles: ";						//Outputs the tiles
	for (unsigned i = 0; i < handChars.size(); ++i) {
		cout << '[' << handChars.at(i) << ", " << handPts.at(i) << "] ";
	}
	cout << endl;
}

void UserInterface::printBoard(const Board &currBoard) {
	vector < vector<string> > strBoard = currBoard.readBoard();

	cout << "   ";
	for (unsigned i = 0; i < strBoard.at(0).size(); ++i) {		//Prints columb numbers
		if (i < 10) {
			cout << i + 1 << "   ";
		}
		else {
			cout << i + 1 << "  ";
		}
	}
	cout << endl;

	for (unsigned i = 0; i < strBoard.size(); ++i) {		

		if (i < 9) {				//Prints row numbers
			cout << i + 1 << "  ";
		}
		else {
			cout << i + 1 << " ";
		}

		for (unsigned j = 0; j < strBoard.at(i).size(); ++j) {		//Print rows
			cout << strBoard.at(i).at(j) << ' ';
		}
		cout << endl; 
	}
}

void UserInterface::printInstr() {
	cout << "To pass your turn, type PASS." << endl
		<< "To discard tiles, type EXCHANGE, followed by a string of those tiles." << endl
		<< "To place a word, type PLACE, followed by the following :" << endl
		<< "	first, either a | or -for vertical / horizontal placement;" << endl
		<< "	second, the row(from the top), the column(from the left)," << endl
		<< "	third, a sequence of letters to place;" << endl
		<< "	to use a blank tile, type ? followed by the letter you want to use it for." << endl;
}

void UserInterface::printScores(const vector<Player*> &players) {
	for (unsigned i = 0; i < players.size(); ++i) {
		cout << players.at(i)->getname() << ": " << players.at(i)->getScore() << endl;
	}
}

string toupper(string s) {
	for (unsigned i = 0; i < s.size(); ++i) {
		if (isalpha(s.at(i))) {
			s.at(i) = toupper(s.at(i));
		}
	}
	return s;
}

void UserInterface::makeMove(vector<Player*> players, unsigned playerIndex, Board *board, Bag *bag, unsigned &passCtr, unsigned k) {

	Player* currPlayer;
	currPlayer = players.at(playerIndex);
	string play;
	string instrPlay;
	string instructions;

	cout << "Current Scores: " << endl;
	this->printScores(players);
	cout << currPlayer->getname() << "'s turn" << endl;
	this->printBoard(*board);
	this->printInstr();
	this->printHand(*currPlayer);
	//cerr << "Tiles remaining in the bag: " << bag->tilesRemaining() << endl;

	getline(cin, instructions);
	stringstream commands(instructions);

	commands >> play;
	getline(commands, instrPlay);
	play = toupper(play);
	instrPlay = toupper(instrPlay);

	if (play == "PASS") {
		++passCtr;
	}
	else if (play == "EXCHANGE") {
		currPlayer->bagTiles(instrPlay, bag);
		currPlayer->drawTiles();
		passCtr = 0;
		printHand(*currPlayer);
	}
	else if (play == "PLACE") {
		board->placeTiles(instrPlay, currPlayer, k);					
		currPlayer->drawTiles();
		printHand(*currPlayer);
		passCtr = 0;
		if (bag->tilesRemaining() == 0 && currPlayer->handSize() == 0) {
			int winningSum = 0;
			for (unsigned i = 0; i < players.size(); ++i) {
				if (i != playerIndex) {
					int d = players.at(i)->handSize();
					players.at(i)->increseScore(d * -1);
					winningSum += d;
				}
			}
			currPlayer->increseScore(winningSum);
			passCtr = players.size() + 10;
		}
	}
	else {
		throw invalid_argument("That is not a valid command");
	}
	cout << "That ends your move." << endl;
	cout << endl << endl;
}

void UserInterface::deletePlayers(vector<Player*> players) {
	for (unsigned i = 0; i < players.size(); ++i) {
		delete players.at(i);
	}
}
