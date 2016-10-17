/*
 * Dictionary.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe and Robert Diersing
 */
 
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <set>
#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary (string dictionary_file_name)
{
	ifstream dictFile (dictionary_file_name.c_str());
	string word;

	if (dictFile.is_open())
	{
		while (getline (dictFile, word))
		{
			//word.erase(word.length()-1); only do that for windows application
			
			elements.insert(word);		 // inserts element into the set
		
		}
		dictFile.close ();
	}
	else throw invalid_argument("Cannot open file: " + dictionary_file_name);
}

bool Dictionary::is_valid(string word) const {
	if (elements.count(word) != 0) {
		return true;
	}
	return false;
}
