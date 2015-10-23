#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include <vector>

#pragma once

/*******************************************************************************
* 						Header for pathfinder in C++
* Filename: trie.h
* Created by: Ross Kwong
*
*******************************************************************************/

class Element {
	public:
		Element();
		~Element();
		void SetVisitedFlagTrue();
		void SetVisitedFlagFalse();
		void SetContent( char c );
		char GetContent();
		bool IsVisited();

	private:
		char content;
		bool visitedFlag;
};

class PathFinder {
	public:
		PathFinder();
		~PathFinder();
		PathFinder( char matrix[4][4], Trie* trie);
		void LoadPathMatrix ( char matrix[4][4] );
		void BeginPathFind( Element matrixPath[4][4] );
		void SearchFrom( Element matrixPath[4][4], int i, int j );
		void DisplayContents( Element matrixPath[4][4] );
		void DisplayPaths( Element matrixPath[4][4] );
		void AppendChar( char c);
		void ResetPaths( Element matrixPath[4][4] );
		void InitiateMoveList( Element matrixPath[4][4],int i,  int j);
		void DisplayWordsFound();



		int GetMatrixSizeLimit();
		int GetWordStrLength();
		int WordCheck();
		
		bool CanMoveUp( Element matrixPath[4][4], int i, int j);
		bool CanMoveTopRight( Element matrixPath[4][4], int i, int j);
		bool CanMoveDown( Element matrixPath[4][4], int i, int j);
		bool CanMoveBottomRight( Element matrixPath[4][4], int i, int j);
		bool CanMoveRight( Element matrixPath[4][4], int i, int j);
		bool CanMoveBottomLeft( Element matrixPath[4][4], int i, int j);
		bool CanMoveLeft( Element matrixPath[4][4], int i, int j);
		bool CanMoveTopLeft( Element matrixPath[4][4], int i, int j);

		std::string GetStrFromVector ();

	private:
		int matrixLimit;
		Element matrixPath[4][4];
		std::vector<char> wordStrVector;
		std::vector<std::string> wordList;
		Trie* dicTrie;
		int wordsFound;

};

#endif /* PATHFINDER_H_ */