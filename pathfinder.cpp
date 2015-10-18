#include <iostream>
#include "pathfinder.h"



/*******************************************************************************
*                       Impelmentation for a Trie in C++
*
* Created by: SourceTricks
* Modified by: Ross Kwong
* Website: http://www.sourcetricks.com/2011/06/c-tries.html
*
*******************************************************************************/

// PathFinder::PathFinder () 	{}
// PathFinder::~PathFinder()	{}

void PathFinder::BeginSearch( Trie* dicTrie ) {
	if (dicTrie != NULL) {
		std::string testWord = "aah";
		std::cout << "Searching for " << testWord << "\n";
		std::cout << "Test word Length: " << testWord.length() << "\n";
		if (dicTrie->SearchWord( testWord ) ) {
			std::cout << "Found " << testWord << " \n";
		} else {
			std::cout << "NOT FOUND " << testWord << "\n";
		}
		std::cout << "Shit works!\n";

	}
}