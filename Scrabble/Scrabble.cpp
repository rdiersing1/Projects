/*
* Scrabble.cpp
*
*  Created on: Sep 18, 2016
*      Author: kempe and Robert Diersing
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

#include "Tile.h"
#include "Dictionary.h"
#include "Bag.h"
#include "Board.h"
#include "Player.h"
#include "UserInterface.h"

using namespace std;

void readConfigFile(string config_file_name,
	string & dictionary_file_name,
	string & board_file_name,
	string & bag_file_name,
	unsigned int & hand_size)
{
	ifstream configFile(config_file_name.c_str());
	string line;
	bool number = false, board = false, tiles = false, dictionary = false;

	if (!configFile.is_open())
		throw invalid_argument("Cannot open file: " + config_file_name);
	while (getline(configFile, line))
	{
		stringstream ss(line);
		string parameter;
		ss >> parameter;
		if (parameter == "NUMBER:")
		{
			ss >> hand_size; number = true;
		}
		else if (parameter == "BOARD:")
		{
			ss >> board_file_name; board = true;
		}
		else if (parameter == "TILES:")
		{
			ss >> bag_file_name; tiles = true;
		}
		else if (parameter == "DICTIONARY:")
		{
			ss >> dictionary_file_name; dictionary = true;
		}
	}
	if (!number)
		throw invalid_argument("Hand size not specified in config file");
	if (!board)
		throw invalid_argument("Board file name not specified in config file");
	if (!tiles)
		throw invalid_argument("Bag file name not specified in config file");
	if (!dictionary)
		throw invalid_argument("Dictionary file name not specified in config file");
}

int main(int nargs, char **args)
{
	cerr << "Loading Scrabble...." << endl;
	if (nargs < 2 || nargs > 2)
		cout << "Usage: Scrabble <config-filename>\n";
	try {
		string dictionaryFileName, boardFileName, bagFileName;
		unsigned int numTiles;
		cerr << "Reading the config file" << endl;
		readConfigFile(args[1],
			dictionaryFileName, boardFileName, bagFileName,
			numTiles);
		cerr << "Read the config file" << endl;
		cerr << "Creating dictionary" << endl;
		Dictionary dict(dictionaryFileName);
		Dictionary* dictPtr = &dict;
		cerr << "Creating Board" << endl;
		Board board(boardFileName, dictPtr);
		cerr << "Creating bag" << endl;
		Bag bag(bagFileName, 10); // second argument is random seed
		cerr << "Creating vector of players" << endl;
		vector<Player*> players;
		cerr << "Creating io" << endl;
		UserInterface io;

		unsigned numPassed = 0;
		string move;
		bool eog = false;
		int maxScore = 0;

		io.printIntro(players, &bag, numTiles);

		while (!eog) {
			for (unsigned i = 0; i < players.size(); ++i) {
				try {
					io.makeMove(players, i, &board, &bag, numPassed, numTiles);
					if (numPassed >= players.size()) {
						eog = true;
						break;
					}
				}
				catch (invalid_argument &err) {
					cout << "Invalid move: " << err.what() << endl;
					cout << "Try again" << endl << endl << endl;
					--i;
				}
			}
		}

		cout << "The game is over!" << endl;
		cout << "Final Scores: " << endl;
		io.printScores(players);
		cout << "Winner(s): ";
		for (unsigned i = 0; i < players.size(); ++i) {
			if (players.at(i)->getScore() > maxScore) {
				maxScore = players.at(i)->getScore();
			}
		}
		for (unsigned i = 0; i < players.size(); ++i) {
			if (players.at(i)->getScore() == maxScore) {
				cout << players.at(i)->getname() << ' ';
			}
		}
		cout << endl << "Thanks for playing!" << endl << endl;

		io.deletePlayers(players);

		return 0;
	}
	catch (invalid_argument & e)
	{
		cout << "Fatal Error! " << e.what() << endl;
		cerr << "Program Terminated" << endl;
		while (1) {}
	}

	return 1;
}
