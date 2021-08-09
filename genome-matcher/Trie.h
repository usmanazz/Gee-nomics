//
//  Trie.h
//  Genome Matcher
//
//  Created by Usman Naz on 3/14/19.
//  Copyright © 2020 Usman Naz. All rights reserved.
//

#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
    
private:
    struct Node {
        std::vector<ValueType> values;
        std::vector<char> labels;
        std::vector<Node*> children;
        
    };
    
    Node* root;
    void freeAllNodes(Node* n);
    Node* getChild(Node* n, const char& ch) const;
    void findMatch(Node* n, const std::string& key, std::vector<ValueType>& searchResult) const;
    
}; 



///////////////////////////////////// IMPLEMENTATION /////////////////////////////////////////

// Trie class constructor that creates a root node with no children and no values
template<typename ValueType>
Trie<ValueType>::Trie(){
    root = new Node;
}


// Trie class destructor that deletes the entire tree
template<typename ValueType>
Trie<ValueType>::~Trie(){
    freeAllNodes(root);
}


// Method to delete the entire trie structure and allocate a new empty
// trie with a root node
template<typename ValueType>
void Trie<ValueType>::reset(){
    freeAllNodes(root);
    root = new Node;
}


// Helper Function for Trie class destructor that recursively deletes each node
// in the trie structure
template<typename ValueType>
void Trie<ValueType>::freeAllNodes(Node* n){
    if (n == nullptr)
        return;
    for (int i=0; i<n->children.size(); i++){
        freeAllNodes(n->children[i]); //recursive call to reach leaf node
    }
    
    // if reached a leaf node, delete the node
    if (n != nullptr){
        delete n;
    }
        
}


// insert function associates the specific key passed in with the value in the
// trie structure by adding necessary nodes and then adding the specific value
// to the list of values in the appropriate node
template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value){
    Node* n = root;
    for(int i=0; i<key.size(); i++){
        char ch = key[i];
        bool foundChar = false;
        
        for(int j=0; j<n->children.size(); j++){
            if(ch == n->labels[j]){
                foundChar = true;
                n = n->children[j];
                break;
            }
        }
        
        // didnt find current char so create new Node, add appropriate label
        // and point to the new child
        if(!foundChar){
            n->labels.push_back(ch);
            n->children.push_back(new Node);
            n = n->children.back();
        }
        
        // add value to the list of values at current node
        if(i == key.size()-1){
            n->values.push_back(value);
        }
    }
}

// Searches for the values associated with a given string.
// If exactMatchOnly is true, returns the values associated with the exact key specified.
// If false, returns values associated with exact key and any SNiPs.
template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const{
   
    std::vector<ValueType> searchResult;
   
    if(!exactMatchOnly){
        // for sNips, first char of string needs to match key[0]
       std::string replacedChar = key.substr(1);
       Node* n = getChild(root, key[0]);
        
        // outer loop keeps track of substr of key to iterate thru
        // to find possible SNips
       for(int i=1; i<key.size(); i++){
           if(n==nullptr) break;
           
           // replace single char in key and look for values in trie
           for(int j=0; j<n->children.size(); j++){
               replacedChar[0] = n->labels[j];
               if(replacedChar == key.substr(i)) continue;
               findMatch(n, replacedChar, searchResult);
           }
           n = getChild(n, key[i]);
           replacedChar = key.substr(1+i);
       }
   }
   findMatch(root, key, searchResult);
   return searchResult;
}


// helper function for find() that passes in key or substring of key past key[0] and
// returns values associated with specified key
template<typename ValueType>
void Trie<ValueType>::findMatch(Node* n, const std::string& key, std::vector<ValueType>& searchResult) const{
    for(int i=0; i<key.size(); i++){
        if(n == nullptr) return;
        Node* x = getChild(n, key[i]);
        if(x == nullptr) return;
        if(i == key.size()-1){
            for(int j=0; j<x->values.size(); j++){
                searchResult.push_back(x->values[j]);
            }
            return;
        }
        n = x;
    }
}

// Returns pointer to a child node associated with a char A,C,G,T, or N in the trie structure.
template<typename ValueType>
typename Trie<ValueType>::Node* Trie<ValueType>::getChild(Node* n, const char& ch) const{
    for(int i=0; i<n->children.size(); i++){
        if(ch == n->labels[i])
            return n->children[i]; 
    }
    return nullptr;
}


#endif // TRIE_INCLUDED



