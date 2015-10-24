#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <sstream>
#include <set>
#include <thread>

#include "trie.h"
#include "trie.cpp"
#include "pathfinder.h"
#include "pathfinder.cpp"

/*******************************************************************************
*							Word (Boggle) Puzzle Solver v0.1
*									  by Ross Kwong
* Notes to self:
*	- Paths are dependent on starting location:
*		+ Starting @ Corner: 2 paths
*		+ Starting @ Sides: 3 paths
*		+ Starting @ Middle: 4 paths
*		+ Else: -1 paths
*	- Keep track of path (no loops!)
*	- Words are a minimum 2-16 character length (Min: 2, Max: 16)
*	- Reference table of letters can have up to 16 unique characters
*	- Three-parter:
*			1) Loading a relevant dictionary
*			2) Searching for words
*			3) Organize words to highest points first & give start point
*	- Possible to have up to 16 unique trees
*	- There are approximately 470,000 words in the English language
*	- Depth First Search for highest point (longer word = more points)
*
*
*******************************************************************************/

bool IsAlphaNumeric (char c) 	{ return isalnum(c); }
int StrLength(std::string str)	{ return str.length(); }
void DisplayMatrix 				( char arr[4][4], const int n );
bool IsWordInCharSet 			( std::set <char> CharSet, std::string word );

std::string DictFileName		() { return "enable1.txt"; }
std::string ReduceStrSizeByOne	(std::string str);


/*
===============================================================================
UniqueCharSet()

	Gathers the chars in to a set and returns it
===============================================================================
*/

std::set <char> GetCharSet ( char oldArr[4][4], const int n ) {
	std::set <char> uniqueCharSet;
	for( int i = 0; i < n; i++ ) {
		for ( int j = 0; j < n; j++ ) {
			uniqueCharSet.insert( oldArr[i][j] );
		}
	}
	return uniqueCharSet;
}

/*
===============================================================================
ReduceStrSizeByOne()

	Shortens the string length by one to remove null terminator char
===============================================================================
*/
std::string ReduceStrSizeByOne(std::string str) {
	if (str.length() != 0) {
		str.resize( str.length()-1 );
		return str;
	}
	return NULL;
}

/*
===============================================================================
IsWordInCharSet()

	Checks word if it belongs to set of CharSet. Returns true if so else false.
===============================================================================
*/

bool IsWordInCharSet ( std::set <char> charSet, std::string word ) {
	std::set <char>::iterator it;
	for ( int i = 0; i < word.length(); i++ ) {
		it = charSet.find( word[i] );
		if ( it != charSet.end() ) {
			return true;
		}
	}
	return false;
}

/*
===============================================================================
PrintCharSet()

	Prints the list passed into the function
===============================================================================
*/
void PrintCharSet( std::set <char> charSet ) {
	std::set<char>::iterator it;
	std::cout << "Unique char set in the matrix: ";
	for ( it = charSet.begin(); it != charSet.end(); it++ ) {
		std::cout << ' ' << *it;
	}
	std::cout << "\n\n";
}

/*
===============================================================================
RemoveStrDelimiter()

	Removes delimiter between strings
===============================================================================
*/
std::string RemoveStrDelimiter( std::string str ) {
	int strLength = str.length();
	if ( strLength > 0 && !IsAlphaNumeric(strLength-1) ) {
		str.resize(strLength-1);
	}
	return str;
}

/*
===============================================================================
numOfElementsInMatrix()

	Returns the number of elements in a matrix
===============================================================================
*/
int getNumberOfElementsInMatrix() {
	return 16;
}

/*
===============================================================================
isStrLengthInBounds()

	Checks to see if str is no bigger than matrix size
===============================================================================
*/
bool isStrLengthInUpperBounds( std::string str ) {
	if ( str.length() <= getNumberOfElementsInMatrix() ) {
		return true;
	}
	return false;
}

/*
===============================================================================
LoadTrie()

	Loads dictionary based on charSet and matrixSize 
===============================================================================
*/
Trie* LoadTrie( std::set <char> charSet ) {
	Trie *trie = new Trie();

	std::string word;
	std::string filename = "enable1.txt";
	std::ifstream dict1;

	dict1.open( filename, std::ios::binary );
	if( dict1.is_open() ) {
		while( !dict1.eof() ) {
			getline( dict1, word );
			std::string formattedWord = RemoveStrDelimiter(word);

			bool strInCharSet = IsWordInCharSet( charSet, formattedWord);
			bool strLengthInBounds = isStrLengthInUpperBounds( formattedWord );


			if ( strLengthInBounds && strInCharSet ) {
				trie->AddWord( formattedWord );
			}
		}
	}

	dict1.close();
	if ( trie != NULL ) {
		std::cout << "\nLoading Complete.\n\n";
	} else {
		std::cout << "\nLoading Failed.\n\n";
	}
	return trie;
}




/*
===============================================================================
DisplayMatrix()

	Displays the matrix in a 2-D NxN matrix
===============================================================================
*/
void DisplayMatrix( char arr[4][4], int n ) {
 	std::cout << "\n";
    for ( int i = 0; i < n; i++ ) {
    	for ( int j = 0; j < n; j++ ) {
              std::cout << arr[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


/*
===============================================================================
Test Functions

===============================================================================
*/
void TestIfWordExists ( Trie* dicTrie, std::string testWord ) {

	if ( dicTrie != NULL ) {
		std::cout << "Searching for " << testWord << "\n";
		std::cout << "Test word Length: " << testWord.length() << "\n";

		if (dicTrie->SearchWord( testWord ) ) {
			std::cout << "Found " << testWord << "!\n";
			std::cout << "Shit works!\n";
		} else {
			std::cout << "NOT FOUND " << testWord << "\n";
		}
	} else {
		std::cout << "Fuck! Trie is empty. =(\n";
	}
}

/*
===============================================================================
Main()

===============================================================================
*/
int main() {
	char matrixArr[4][4];

	std::string userInput;
	std::cout << "Welcome to The Boggle Word-Puzzle Solver." 
	"Please enter in the 4x4 matrix of letters\n";

	for( int i=0; i<4; i++ ) {
		std::cout << "Please enter the 4 letters in the ";
		switch (i) {
			case 1:
				std::cout << "2nd row.\n";
				break;
			case 2:
				std::cout << "3rd row.\n";
				break;
			case 3:
				std::cout << "4th row.\n";
				break;
			default:
				std::cout << "1st row.\n";
				break;
		}
		cin >> userInput;
		for( int j=0; j<4; j++ ) {
			matrixArr[i][j] = userInput.at(j);
		}
	}

	std::set<char> charSet = GetCharSet ( matrixArr, 4 );
	Trie *dicTrie = LoadTrie( charSet );

	std::cout << "The matrix is: \n";
	PathFinder PathFinder( matrixArr, dicTrie );


	return 0;
}


