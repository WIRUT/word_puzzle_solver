#ifndef TRIE_H_
#define TRIE_H_

#pragma once
#include <vector>
#include <string>

/*******************************************************************************
* 						Header for a Trie in C++
* Filename: trie.h
* Created by: Ross Kwong
*
*******************************************************************************/



class Node {
	public:
    	Node();
        ~Node();
        char  Content();                       // Returns mContent
    	void  SetContent(char c);              // Set content to in uppercase
    	bool  WordMarker();                    // A flag if a word has formed
    	void  SetWordMarker();                 // Sets Word marker in Node
    	void  AppendChild( Node* child );      // Appends an element into array
        Node* FindChild(char c);               // Locate character & returns it

        bool  IsPathTravelled( Node* child);   // A flag to track path travlled    
        void  ResetPathFlag( bool f );                 // Resets the path to false 

//    	std::vector<Node*> children() { return mChildren; };
		//Node *children() { return mChildren

	private:
    	char mContent;
    	bool mWordMarker;
        bool mTravelledFlag;

    	std::vector<Node*> mChildren;
};

class Trie {
	public:
		Trie();
		~Trie();
		void AddWord(std::string s);           // Adds string to the trie
		bool SearchWord(std::string s);        // Finds word in trie
	private:
    	Node* root;
    	std::string ToUpperCase(std::string str);
};




#endif /* TRIE_H_ */
