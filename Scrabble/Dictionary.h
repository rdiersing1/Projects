/*
 * Dictionary.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe and Robert Diersing
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <string>
#include <set>

class Dictionary {
public:
	Dictionary (std::string dictionary_file_name);
	bool is_valid(std::string) const;

private:
	std::set<std::string> elements;
};


#endif /* DICTIONARY_H_ */
