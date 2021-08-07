//
//  GenomeMatcher.cpp
//  Genome Matcher
//
//  Created by Usman Naz on 3/14/19.
//  Copyright © 2020 Usman Naz. All rights reserved.
//

#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include <algorithm>
#include "Trie.h"
using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_minSearchLength;
    vector<Genome> genomeLibrary;
    
    // Gets name, position, length, of genome fragment from trie.
    // Also stores index of genome to index 'matches' vector in findGenomesWithThisDNA(...)
    struct seqAndPos {
        string name;
        int index;
        int pos;
        int length;
    };
    Trie<seqAndPos> trie;
    
};

// Single argument which specifies the minimum length of a DNA sequence that the
// user can later search for within the genome library.
GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearchLength = minSearchLength;
}


// This method is used to add a new genome to the library of genomes
// maintained by GenomeMatcher object
void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    // Add genome to the genome Library held by genomeMatcher object
    genomeLibrary.push_back(genome);
    
    string test;
    genome.extract(0, genome.length(), test);

    // Index the genome sequence and add every substring of length minSearchLength of
    // the genome into a Trie structure maintained by the genomeMatcher
    for(int position=0; position<genome.length(); position++){
        // If the length of the substring at a particular position goes past the
        // end of the genome, don't add this to the Trie
        if(position+minimumSearchLength() > genome.length())
            break;
        
        // Create new value to store in Trie for new substring
        seqAndPos* s = new seqAndPos();
        
        
        // Use extract method from Genome class to get the substring and
        // insert into Trie using Trie class
        string subStr;
        
        if(genome.extract(position, minimumSearchLength(), subStr)){
        
            // Get index as genome Library grows and position as we iterate thru genome
            s->name = genome.name();
            s->pos = position;
            s->index = genomeLibrary.size()-1;
            s->length = subStr.length();

            trie.insert(subStr, *s);
        }
    }
}


// This method must return the minimum search length passed to the constructor so the user
// of the class can determine the minimum length of strings that can be searched for
int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;
}


// This method returns true if there is at lease one match between fragment and any segment of any genome.
// Returns false if no match exists, minimumLength is less than minSearchLength, or length of passed in fragment
// is less than minimumLength.
// If returns true, it sets the vector matches to contain exactly one DNAMatch struct for each and only
// the genomes containing a match (DNAMatch holds genome name, length, and position of matched segment).
bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    // keep track of indexing and checking if matches already exist in vector
    matches.resize(genomeLibrary.size());
    
    if (fragment.length() < minimumLength || minimumLength < minimumSearchLength())
        return false;
    
    // get fragment prefix that could possibly be in trie
    string fragPrefix = fragment.substr(0, minimumSearchLength());

    // locate potential matches in trie of minimunSearchLength
    vector<seqAndPos> potentialMatches = trie.find(fragPrefix, exactMatchOnly);

    if(!potentialMatches.empty()){

        // extract more bases from Genome
        for (int i=0; i<potentialMatches.size(); i++){
            // keeps track of the number of mismatches
            int mismatch = 0;
            string segmentInGenome;
            
            // extract segment in Genome
            genomeLibrary[potentialMatches[i].index].extract(potentialMatches[i].pos, fragment.length(), segmentInGenome);

            int addLengthToDNA = 0;
            // Check if chars are equal between extracted bases and
            // bases from fragment and increment length.
            for (int j=0; j<segmentInGenome.length(); j++){
                if (segmentInGenome[j] == fragment[j])
                    addLengthToDNA++;
                else {
                    mismatch++;
                    
                    // when exactMatchOnly is true, and encounter a mismatch when comparing
                    // fragment and extracted segment, break out of loop since we found
                    // the first N bases that match
                    if (exactMatchOnly && mismatch == 1)
                        break;
                    
                    // encountered more than one mismatch so dont increment length
                    // and break out of loop to check if length > minimumLength
                    if (mismatch > 1)
                        break;
                    addLengthToDNA++;
                }
                
            }

            // check that segment is longer or equal to minimumlength
            if (addLengthToDNA >= minimumLength){
                
                // initialize struct
                DNAMatch* dna = new DNAMatch();
                dna->genomeName = potentialMatches[i].name;
                dna->position = potentialMatches[i].pos;
                dna->length = addLengthToDNA;
                
                // if segment length is greater than possible existing length, add to matches vector
                if (dna->length > matches[potentialMatches[i].index].length){
                    matches[potentialMatches[i].index] = *dna;
                }

                // If equal to already existing length, then check
                // which segment is found earlier in the genome
                if (dna->length == matches[potentialMatches[i].index].length){
                    if (dna->position < matches[potentialMatches[i].index].position){
                        matches[potentialMatches[i].index] = *dna;
                    }
                }
            }
            
        } // end of outer for loop

        // remove any empty structs in vector
        vector<DNAMatch>::iterator it = matches.begin();
        for (; it != matches.end();) {
            if ((*it).length == 0)
                it = matches.erase(it);
            else
                it++;
        }

        // if at least one match, return true
        return !matches.empty();

    }
    
    // no matches found
    matches.resize(0);
    return false;
}


// Binary function that accepts two elements in the range as arguments, and
// returns a value convertible to bool.
// The value returned indicates whether the element passed as first argument
// is considered to go before the second in the specific ordering it defines.
struct compare
{
    inline bool operator() (const GenomeMatch& struct1, const GenomeMatch& struct2)
    {
        if (struct1.percentMatch == struct2.percentMatch)
            return (struct1.genomeName < struct2.genomeName);
        return (struct1.percentMatch > struct2.percentMatch);
    }
};


// This method compares a passed-in query genome for a new organism
// against all genomes currently held in a GenomeMatcher object’s library and
// passes back a vector of all genomes that contain more than matchPercentThreshold
// of the base sequences of length fragmentMatchLength from the query genome.
//
// It returns true if one or more genomes in the library were close enough matches, and
// false if no close matches were located.
// The method also must return false if the value fragmentMatchLength is less than
// the value of minSearchLength passed into the GenomeMatcher constructor.
bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    if (fragmentMatchLength < minimumSearchLength() || query.length() < fragmentMatchLength)
        return false;
    
    int numOfSeq = query.length()/fragmentMatchLength;
    
    // keeps track of count of matches for each genome in library
    unordered_map<string, double> genomeCount;
    for (int i=0; i<genomeLibrary.size(); i++){
        genomeCount[genomeLibrary[i].name()] = 0;
    }
    
    // for each sequence of length fragMatchLen:
    // 1. extract sequence from query
    // 2. search extracted seq in genome library
    // 3. if match found, increment count of genome it was found in
    for (int position=0; position<query.length(); position = (position + 1)*fragmentMatchLength){
        string fragment;
        query.extract(position, fragmentMatchLength, fragment);
        
        vector<DNAMatch> matches;
        findGenomesWithThisDNA(fragment, fragmentMatchLength, exactMatchOnly, matches);
        
        if (!matches.empty()){
            for (int i=0; i<matches.size(); i++)
                genomeCount[matches[i].genomeName]++;
        }
    }
    
    // Loop thru map that keeps track of genomes with at least one matching seq from query
    // and compute percent of seq from query genome that were found in genome(s) from library.
    unordered_map<string, double>::iterator it = genomeCount.begin();
    for (; it != genomeCount.end(); it++){
        if (it->second != 0){
            double p = (it->second/numOfSeq)*100;
            
            // If percentage is greater than or equal to threshold, then add
            // genome and percentage as GenomeMatch struct to results vector
            if (p >= matchPercentThreshold){
                GenomeMatch* gm = new GenomeMatch();
                gm->genomeName = it->first;
                gm->percentMatch = p;
                
                results.push_back(*gm);
            }
        }
    }
    
    // Ordered in descending order by the match proportion p.
    // Breaking ties by genome name in ascending alphabetic order
    stable_sort(results.begin(), results.end(), compare());
    
    return !results.empty();

}



//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
