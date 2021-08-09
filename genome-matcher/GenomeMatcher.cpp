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
    
    // Stores index of genome to iterate matches vector in findGenomesWithThisDNA(...)
    struct seqAndPos {
        string name;
        int index;
        int pos;
        int length;
    };
    Trie<seqAndPos> trie;
    
};


GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearchLength = minSearchLength;
}


// 1. Adds a new genome to the library of genomes maintained by GenomeMatcher object.
// 2. Index the genome sequence and add every substring of length minSearchLength of
//    the genome into a Trie structure
void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    // Add genome to the genome Library
    genomeLibrary.push_back(genome);
    
    string test;
    genome.extract(0, genome.length(), test);

    for(int position=0; position<genome.length(); position++){
        
        if(position+minimumSearchLength() > genome.length())
            break;
        
        string subStr;
        if(genome.extract(position, minimumSearchLength(), subStr)){
        
            // Get index as genome Library grows and position as we iterate through genome
            seqAndPos* s = new seqAndPos();
            s->name = genome.name();
            s->pos = position;
            s->index = genomeLibrary.size()-1;
            s->length = subStr.length();

            trie.insert(subStr, *s);
        }
    }
}


int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;
}


// This method returns true if there is at lease one match between fragment and any segment of any genome.
// Returns false if no match exists, minimumLength is less than minSearchLength, or length of passed in fragment
// is less than minimumLength.
// If returns true, it sets the vector matches to contain exactly one DNAMatch struct for each and only
// the genomes containing a match.
bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    // index genomes
    matches.resize(genomeLibrary.size());
    
    if (fragment.length() < minimumLength || minimumLength < minimumSearchLength())
        return false;
    
    string fragPrefix = fragment.substr(0, minimumSearchLength());

    // get potential matches in trie of minimunSearchLength
    vector<seqAndPos> potentialMatches = trie.find(fragPrefix, exactMatchOnly);

    if(!potentialMatches.empty()){

        // extract more bases from Genome
        for (int i=0; i<potentialMatches.size(); i++){
            
            int mismatch = 0;
            string segmentInGenome;
            
            // extract segment in Genome
            genomeLibrary[potentialMatches[i].index].extract(potentialMatches[i].pos, fragment.length(), segmentInGenome);

            // verify that we can match minimumLength or more characters
            int addLengthToDNA = 0;
            for (int j=0; j<segmentInGenome.length(); j++){
                if (segmentInGenome[j] == fragment[j])
                    addLengthToDNA++;
                else {
                    mismatch++;
                    
                    // found the first N bases that match
                    if (exactMatchOnly && mismatch == 1)
                        break;
                    
                    // encountered more than one mismatch
                    if (mismatch > 1)
                        break;
                    addLengthToDNA++;
                }
                
            }

            if (addLengthToDNA >= minimumLength){
                
                DNAMatch* dna = new DNAMatch();
                dna->genomeName = potentialMatches[i].name;
                dna->position = potentialMatches[i].pos;
                dna->length = addLengthToDNA;
                
                // if segment length is greater than existing segment, add to matches vector
                if (dna->length > matches[potentialMatches[i].index].length){
                    matches[potentialMatches[i].index] = *dna;
                }

                // If length equal to already existing segment, add segment found
                // earlier in genome
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

        return !matches.empty();
    }
    
    // no matches found
    matches.resize(0);
    return false;
}


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
    
    // compute percent of seq from query genome that were found in genome(s) from library.
    unordered_map<string, double>::iterator it = genomeCount.begin();
    for (; it != genomeCount.end(); it++){
        if (it->second != 0){
            double p = (it->second/numOfSeq)*100;
            
            // add genome and percentage as GenomeMatch struct to results vector
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
