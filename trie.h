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
    	void  SetContent(char c);              // Set content to in uppercase
    	void  SetWordMarker();                 // Sets Word marker in Node
    	void  AppendChild( Node* child );      // Appends an element into array

        char  Content();                       // Returns mContent
        bool  HasWordMarker();                 // A flag if a word has formed

        Node* FindChild( char c );             // Locate character & returns it
        std::vector<Node*> children();         // Returns mChildren

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
	    void ResetTriePaths();                 // Resets all node paths in Trie
    	int SearchWord(std::string s);         // Finds word in trie
	
    private:
    	Node* root;
    	std::string ToUpperCase(std::string str);
};




#endif /* TRIE_H_ */
