//
//  Genome.cpp
//  Genome Matcher
//
//  Created by Usman Naz on 3/14/19.
//  Copyright © 2020 Usman Naz. All rights reserved.
//

#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>

#include <fstream>
#include <sstream>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_sequence;
    int m_length;
};

//Initializes a new Genome object with its name, sequence, and length
GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_sequence = sequence;
    m_length = sequence.length();
}

// Pass in 2 parameters: istream object genomeSource and a vector. This function
// fills in the vector with Genome objects that were created for each genome in the
// genetic data files
bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    // s represents a line in the genome file
    string s = "";
    string name = "";
    string sequence = "";
    int lineNumber = 0;
    bool containsBases = false;
    Genome* n = nullptr;
    while (getline(genomeSource, s)){

        // if the first line of the file is not a name, return false
        if (lineNumber==0 && s[0]!='>'){
            return false;
        }
        
        // if the line contains no characters, return false
        if(s.size() == 0)
            return false;
        
        // the line is a genome name
        if(s[0] == '>' && s.length() != 1){
            // Verify that bases are on lines after name and up to
            // but not including the next line with a name.
            // Once we have a genome's name and sequence,
            // add it to the vector of Genome objects
            if(containsBases == true){
                n = new Genome(name, sequence);
                genomes.push_back(*n);
            }
            
            // create name and new sequence for new Genome
            name = s.substr(1);
            sequence = "";
            getline(genomeSource, s);
            containsBases = true;
            lineNumber++;
        }
        
        // Check if line with bases is properly formatted
        for(int i=0; i<s.size(); i++){
            // Make sure in concatenated sequence that all bases are uppercase
            s[i] = toupper(s[i]);
            if( !(s[i]=='A' || s[i]=='C' || s[i]=='T' || s[i]=='G' || s[i]=='N'))
                return false;
        }
        
        // concatenate lines of bases
        sequence += s;
        lineNumber++;
    }
    
    // if the first line of the file is not a name, return false
    if (lineNumber==0 && s[0]!='>'){
        return false;
    }
    
    // create new Genome object for last genome in file and add to vector
    n = new Genome(name, sequence);
    genomes.push_back(*n);
    return true;
}

// Returns length of the DNA sequence (i.e. the total As, Gs, Ts and Ns
// stored in the genome object).
int GenomeImpl::length() const
{
    return m_length;
}

// Returns name of Genome
string GenomeImpl::name() const
{
    return m_name;
}

// Sets fragment to a copy of a portion of the Genome's DNA sequence: the substring length
// characters long starting at 'position' (where the first character of the sequence is at
// position 0).
// Returns true if successfully extracts fragment and false otherwise (i.e. try to extract
// string that goes past end of genome)
bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (length == 0)
        return false;
    
    // return false if length of fragment is greater than length of genome sequence
    if(position+length > m_length ){
        return false;
    }
    // add bases from sequence to fragment for the given length from the given position
    for(int i=position; i<(position+length); i++){
        fragment += m_sequence[i];
    }
    return true;
}


//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
