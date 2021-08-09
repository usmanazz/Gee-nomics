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

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_sequence = sequence;
    m_length = sequence.length();
}

// This method populates passed in vector with Genome objects from data files
bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    string line = "";
    string name = "";
    string sequence = "";
    int lineNumber = 0;
    bool containsBases = false;
    Genome* n = nullptr;
    while (getline(genomeSource, line)){

        // first line not a name
        if (lineNumber==0 && line[0]!='>'){
            return false;
        }
        
        // empty line
        if(line.size() == 0)
            return false;
        
        // line is a genome name
        if(line[0] == '>' && line.length() != 1){
            // Verify that bases are on lines after name and up to
            // but not including the next line with a name.
            if(containsBases == true){
                n = new Genome(name, sequence);
                genomes.push_back(*n);
            }
            
            // create name and new sequence for new Genome
            name = line.substr(1);
            sequence = "";
            getline(genomeSource, line);
            containsBases = true;
            lineNumber++;
        }
        
        // Check if line with bases is properly formatted
        for(int i=0; i<line.size(); i++){
            line[i] = toupper(line[i]);
            if( !(line[i]=='A' || line[i]=='C' || line[i]=='T' || line[i]=='G' || line[i]=='N'))
                return false;
        }
        
        // concatenate lines of bases
        sequence += line;
        lineNumber++;
    }
    
    if (lineNumber==0 && line[0]!='>'){
        return false;
    }
    
    n = new Genome(name, sequence);
    genomes.push_back(*n);
    return true;
}

int GenomeImpl::length() const
{
    return m_length;
}

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
    
    if(position+length > m_length ){
        return false;
    }
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
