#include <vector>
#include <iostream>
#include <string>
#include <ctype.h>

#include "trie.h"

using namespace std;

/*******************************************************************************
*                       Impelmentation for a Trie in C++
*
* Created by: SourceTricks
* Modified by: Ross Kwong
* Website: http://www.sourcetricks.com/2011/06/c-tries.html
*
*******************************************************************************/

Node::Node()      	                    { mContent = ' '; 
										  mWordMarker = false; 
										  mTravelledFlag = false; }
Node::~Node()                       	{}

char Node::Content()                	{ return mContent; }
void Node::SetContent(char c) 			{ mContent = c; }

bool Node::IsPathTravelled(Node* child)	{ return mTravelledFlag; }
void Node::ResetPathFlag(bool f)		{ mTravelledFlag = false; }

bool Node::WordMarker()             	{ return mWordMarker; }
void Node::SetWordMarker()          	{ mWordMarker = true; }
void Node::AppendChild(Node* child) 	{ mChildren.push_back(child); }

Trie::Trie()    						{ root = new Node(); }
Trie::~Trie()   						{}

/*
===============================================================================
ToUpperCase()

	Converts a string to all upper case
===============================================================================
*/
std::string Trie::ToUpperCase(std::string str) {
	if (str.length() != 0) {
		for (std::string::size_type i = 0; i<str.length(); i++ ) {
			str[i] = std::toupper(str[i]);
		}
		return str;
	}
	return NULL;
}

/*
===============================================================================
FindChild()

    Finds the Node that contains the specific character and returns it
===============================================================================
*/
Node* Node::FindChild(char c) {

    for ( int i = 0; i < mChildren.size(); i++ ) {
        Node* tmp = mChildren.at(i);
        if ( tmp->Content() == c ) {
            return tmp;
        }
    }
    return NULL;
}

/*
===============================================================================
AddWord()

    Adds the word into the trie by breaking up the characters into nodes
===============================================================================
*/
void Trie::AddWord(std::string str) {
	Node* current = root;
	int strLength = str.length();
	str = ToUpperCase(str);

    if ( strLength == 0 ) {
        current->SetWordMarker(); // an empty word
        return;
    }

	if ( SearchWord(str) ) {
		return;
	}

    for ( int i = 0; i < strLength; i++ ) {
		Node* child = current->FindChild(str[i]);
		if ( child != NULL ) {
			current = child;
		} else {
			Node* tmp = new Node();
			tmp->SetContent(str[i]);

			current->AppendChild(tmp);
			current = tmp;
		}

		if ( i == strLength - 1) {
			current->SetWordMarker();
		}
	}
}

/*
===============================================================================
SearchWord()

    Searches for the word in the trie and returns a boolean value if found
===============================================================================
*/
bool Trie::SearchWord(std::string str) {
	if (str.length() > 0) {
		Node* current = root;
		str = ToUpperCase(str);

		while ( current != NULL ) {

			for ( int i = 0; i < str.length(); i++ ) {
				Node* tmp = current->FindChild(str[i]);
				if ( tmp == NULL ) {
					return false;
				}
				current = tmp;
			}

			if ( current->WordMarker() ) {
				return true;
			} else {
				return false;
			}
		}
    }
    return false;
}
