#include <iostream>
#include <vector>
#include <iomanip>
#include "pathfinder.h"

/*******************************************************************************
*                       Impelmentation for a Trie in C++
*
* Created by: SourceTricks
* Modified by: Ross Kwong
* Website: http://www.sourcetricks.com/2011/06/c-tries.html
*
*******************************************************************************/

Element::Element()						{ content = ' '; visitedFlag = false; }
Element::~Element()						{}
void Element::SetVisitedFlagTrue()		{ visitedFlag = true; }
void Element::SetVisitedFlagFalse()		{ visitedFlag = false; }
void Element::SetContent(char c)		{ content = c; }
char Element::GetContent()				{ return content; }
bool Element::IsVisited()				{ return visitedFlag; }

PathFinder::PathFinder()				{ Element matrixPath[4][4]; matrixLimit = 4; }
PathFinder::~PathFinder()				{}
int PathFinder::GetMatrixSizeLimit() 	{ return matrixLimit; }
int PathFinder::GetWordStrLength()		{ return wordStrVector.size(); }
void PathFinder::AppendChar( char c)	{ wordStrVector.push_back(c); }


PathFinder::PathFinder( char matrix[4][4], Trie* trie ) {
	Element matrixPath[4][4];
	dicTrie = trie;
	matrixLimit = 4;
	int wordsFound = 0;
	if (matrix != NULL) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				matrixPath[i][j].SetContent( matrix[i][j] );
			}
		}
	}
	DisplayContents( matrixPath );
	DisplayPaths( matrixPath );
	BeginPathFind( matrixPath );
	DisplayWordsFound();
}

void PathFinder::BeginPathFind( Element matrixPath[4][4] ) {
	if (matrixPath != NULL) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				// cout << "BeginPath passing i=" << i << " j=" << j <<"\n";
				wordStrVector.clear();
				ResetPaths( matrixPath );
				SearchFrom(matrixPath, i,j);
			}
		}
	}
}

std::string PathFinder::GetStrFromVector() {
	std::string word;
	for ( int i=0; i<wordStrVector.size(); i++ ) {
		word += wordStrVector.at(i);
	}
	return word;
}

int PathFinder::WordCheck() {
	std::string word = GetStrFromVector();
	switch ( dicTrie->SearchWord(word) ) {
		case 1:
			// cout << word << " IS FOUND IN TRIE!!!!!!!\n";
			wordsFound++;
			return 1;
		case 2:
			// cout << word << " is not a word yet.\n";
			return 2;
		default:
			// cout << word << " is NOT a word or begins with those letters.\n";
			return 0;
	}
}

/*
===============================================================================
SearchFrom()

    Marks element as travelled and finds next element to search
===============================================================================
*/

void PathFinder::SearchFrom( Element matrixPath[4][4], int i, int j) {
	AppendChar( matrixPath[i][j].GetContent() );
	matrixPath[i][j].SetVisitedFlagTrue();

	// cout << "\n------------------------------------\n";
	// cout << "Letters in Vector: " << GetStrFromVector() << "\n";
	// cout << "i=" << i << " j=" << j << "\n";
	// cout << "GetWordStrLength is " << GetWordStrLength() << "\n";
	// DisplayPaths( matrixPath );
	// cout << "\n------------------------------------\n";

	if( GetWordStrLength()>=3 ) {
		int wordCheckState = WordCheck();
		if ( wordCheckState==0 ) {
			matrixPath[i][j].SetVisitedFlagFalse();
			wordStrVector.pop_back();
		} else {
			if ( wordCheckState==1 ) {
				wordList.push_back( GetStrFromVector() );
			}
			InitiateMoveList( matrixPath,i,j );
			matrixPath[i][j].SetVisitedFlagFalse();
			wordStrVector.pop_back();
		}
		// cout << "--POPPED " << matrixPath[i][j].GetContent() << "--\n";			
	} else {
		// cout << "--GetWordStrLength is 2 or less--\n";			
		InitiateMoveList( matrixPath,i,j );
		if ( GetWordStrLength()==2 ) {
			matrixPath[i][j].SetVisitedFlagFalse();
			wordStrVector.pop_back();
		}
	}
}

/*
===============================================================================
InitiateSearch()

    Checks if next path is visited or not
===============================================================================
*/

void PathFinder::InitiateMoveList( Element matrixPath[4][4], int i, int j) {
		if ( CanMoveUp(matrixPath, i, j) ) {
			SearchFrom( matrixPath, i-1, j );
		}
		if ( CanMoveTopRight(matrixPath, i, j) ) {
			SearchFrom( matrixPath, i-1, j+1 );
		}
		if ( CanMoveRight(matrixPath, i, j) ) {
			SearchFrom( matrixPath, i, j+1 );
		}
		if ( CanMoveBottomRight(matrixPath, i, j) ) {
			SearchFrom( matrixPath, i+1, j+1 );
		}
		if ( CanMoveDown(matrixPath, i, j) ) {
			SearchFrom( matrixPath, i+1, j );
		}
		if ( CanMoveBottomLeft(matrixPath, i, j) ) {
			SearchFrom( matrixPath, i+1, j-1 );
		}
		if ( CanMoveLeft(matrixPath, i, j) ) {
			SearchFrom( matrixPath, i, j-1 );
		}
		if ( CanMoveTopLeft(matrixPath, i, j) ) {
			SearchFrom( matrixPath, i-1, j-1 );
		}
}

bool PathFinder::CanMoveUp( Element matrixPath[4][4], int i, int j) {
	if( i==0 || matrixPath[i-1][j].IsVisited() ) {
	// std::cout << "MatrixPath[" << i-1 << "]["<< j <<"] is visited\n "; 
		return false;
	} else {
		// std::cout << "MatrixPath[" << i-1 << "]["<< j <<"] is NOT visited\n"; 
		return true;
	}
}

bool PathFinder::CanMoveDown( Element matrixPath[4][4], int i, int j) {
	if( i==(GetMatrixSizeLimit()-1 ) || matrixPath[i+1][j].IsVisited() ) {
		return false;
	} else {
		return true;
	}
}

bool PathFinder::CanMoveLeft( Element matrixPath[4][4], int i, int j) {
	if( j==0 || matrixPath[i][j-1].IsVisited() ) {
		return false;
	} else {
		return true;
	}
}

bool PathFinder::CanMoveRight( Element matrixPath[4][4], int i, int j) {
	if( j==( GetMatrixSizeLimit()-1 ) || matrixPath[i][j+1].IsVisited() ) {
		return false;
	} else {
		return true;
	}
}

bool PathFinder::CanMoveTopRight( Element matrixPath[4][4], int i, int j) {
	if( i==0 
		|| j==( GetMatrixSizeLimit()-1) 
		|| matrixPath[i-1][j+1].IsVisited() ) {
		return false;
	} else {
		return true;
	}
}
bool PathFinder::CanMoveBottomRight( Element matrixPath[4][4], int i, int j) {
	if( i==( GetMatrixSizeLimit()-1 ) 
		|| j==(GetMatrixSizeLimit())-1 
		|| matrixPath[i+1][j+1].IsVisited() ) {
		return false;
	} else {
		return true;
	}
}
bool PathFinder::CanMoveBottomLeft( Element matrixPath[4][4], int i, int j) {
	if( i==( GetMatrixSizeLimit()-1 ) 
		|| j==0 
		|| matrixPath[i+1][j-1].IsVisited() ) {
		return false;
	} else {
		return true;
	}
}
bool PathFinder::CanMoveTopLeft( Element matrixPath[4][4], int i, int j) {
	if( i==0 
		|| j==0 
		|| matrixPath[i-1][j-1].IsVisited() ) {
		return false;
	} else {
		return true;
	}	
}
//---------------------------------------------------------------------------//

void PathFinder::ResetPaths( Element matrixPath[4][4] ) {
	if (matrixPath != NULL) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				matrixPath[i][j].SetVisitedFlagFalse();
			}
		}
	}
}


void PathFinder::DisplayContents( Element matrixPath[4][4] ) {
	std::cout << "\n";
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			Element el = matrixPath[i][j];
			std::cout << el.GetContent() << " ";
		}
		std::cout << "\n";
	}
		std::cout << "\n";
}


void PathFinder::DisplayPaths( Element matrixPath[4][4] ) {
	std::cout << "\n";
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			Element el = matrixPath[i][j];
			std::cout << el.IsVisited() << " ";
		}
		std::cout << "\n";
	}
		std::cout << "\n";
}

void PathFinder::DisplayWordsFound() {
	std::cout << "Words list include: \n";
	for (int i=0; i < wordList.size(); i++ ) {
		if ( i%4 == 0) {
			cout << "\n";
		}
		cout << left << setw(20) << wordList.at(i);
	}
	std::cout << "\n\n" << wordsFound << " words found.\n";
}


