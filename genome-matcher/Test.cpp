//
//  TestTrie.cpp
//  Genome Matcher
//
//  Created by Usman Naz on 3/14/19.
//  Copyright © 2020 Usman Naz. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <vector>
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "Trie.h"
#include "provided.h"

using namespace std;


// ===============================================================================
//                                                                              ||
//      Automated tests for classes: Trie, Genpme and GenomeMatcher utilizing   ||
//                              Google Test for C++                             ||
//                                                                              ||
// ===============================================================================


// ============================= Trie Class Tests =================================== //

class TrieClassTests : public ::testing::Test{
public:
    TrieClassTests(){
        trie.insert("hi", 9);
        trie.insert("hi", 17);
        trie.insert("hit", 1);
        trie.insert("hit", 2);
        trie.insert("hip", 10);
        trie.insert("hip", 20);
        trie.insert("hat", 7);
        trie.insert("hat", 8);
        trie.insert("hat", 9);
        trie.insert("a", 14);
        trie.insert("to", 22);
        trie.insert("to", 23);
        trie.insert("tap", 19);
        trie.insert("tap", 6);
        trie.insert("tap", 32);
    }

    void sortVectors(vector<int>& result, vector<int>& expected){
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
    }

protected:
    Trie<int> trie;

};

// 1
TEST_F(TrieClassTests, FindValuesAssocWithExactKeyWhenTrue){

    vector<int> result = trie.find("tap", true);
    vector<int> expected = {32, 6, 19};
    sortVectors(result, expected);

    ASSERT_EQ(result, expected);

}

TEST_F(TrieClassTests, FindReturnsEmptyVectorWhenNoValuesAssocWithKeyWhenTrue){
    vector<int> result = trie.find("ta", true);
    vector<int> expected = {};

    ASSERT_EQ(result, expected);

}

TEST_F(TrieClassTests, FindReturnsEmptyVectorWhenKeyNotInTrieWhenTrue){

    vector<int> result = trie.find("hop", true);
    vector<int> expected = {};

    ASSERT_EQ(result, expected);

}

TEST_F(TrieClassTests, FindValuesAssocWithExactKeyWhenFalse){

    vector<int> result = trie.find("hit", false);
    vector<int> expected = {1, 2, 7, 8, 9, 10, 20};
    sortVectors(result, expected);

    ASSERT_EQ(result, expected);

}

// 5
TEST_F(TrieClassTests, FindValuesWhenNoValuesAssocWithExactKeyWhenFalse){
    vector<int> result = trie.find("ha", false);
    vector<int> expected = {17, 9};
    sortVectors(result, expected);

    ASSERT_EQ(result, expected);

}

TEST_F(TrieClassTests, FindValuesWhenKeyNotInTrieWhenFalse){

    vector<int> result = trie.find("hop", false);
    vector<int> expected = {20, 10};
    sortVectors(result, expected);

    ASSERT_EQ(result, expected);

}

TEST_F(TrieClassTests, FindReturnsEmptyVectorWhenNoSnip){

    vector<int> result = trie.find("hum", false);
    vector<int> expected = {};

    ASSERT_EQ(result, expected);

}

TEST_F(TrieClassTests, FindReturnsEmptyVectorWhenFirstLetterOfKeyNotExactMatchWithStringInTrie){

    vector<int> result = trie.find("sip", false);
    vector<int> expected = {};

    ASSERT_EQ(result, expected);

}





// ============================ Genome Class Tests ================================= //

class GenomeClassTests : public ::testing::Test{
public:
    GenomeClassTests()
    : g("oryx", "GCTCGGNACACATCCGCCGCGGACGGGACGGGATTCGGGCTGTCGATTGTCTCACAGATCGTCGACGTACATGACTGGGA"), g2("hi", "A")
    {
    }

    string concatFileNameToPath(const string& filename){
        string path = "/Users/unnaz1/Documents/cs32/Gee-nomics/data/myTests/";
        return path + filename;
    }

protected:
    Genome g, g2;
    vector<Genome> genomesForFalseTests;
    vector<Genome> genomesForTrueTests;
};



// ----------------- LOAD FUNCTION True Tests ------------------ //

TEST_F(GenomeClassTests, FirstLineStartsWithGreaterSymbolAndValidName){
    string filename = "FirstLineStartsWithGreaterAndValidName.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForTrueTests);

    ASSERT_TRUE(result);
}

// 10
TEST_F(GenomeClassTests, BaseLinesContainOnlyUppercaseAs){
    string filename = "BaseLinesContainsOnlyUppercaseAs.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForTrueTests);

    ASSERT_TRUE(result);
}

TEST_F(GenomeClassTests, BaseLinesContainOnlyUppercaseCs){
    string filename = "BaseLinesContainsOnlyUppercaseCs.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForTrueTests);

    ASSERT_TRUE(result);
}

TEST_F(GenomeClassTests, BaseLinesContainOnlyUppercaseGs){
    string filename = "BaseLinesContainsOnlyUppercaseGs.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForTrueTests);

    ASSERT_TRUE(result);
}

TEST_F(GenomeClassTests, BaseLinesContainOnlyUppercaseTs){
    string filename = "BaseLinesContainsOnlyUppercaseTs.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForTrueTests);

    ASSERT_TRUE(result);
}

TEST_F(GenomeClassTests, BaseLinesContainOnlyUppercaseNs){
    string filename = "BaseLinesContainsOnlyUppercaseNs.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForTrueTests);

    ASSERT_TRUE(result);
}

// 15
TEST_F(GenomeClassTests, BaseLinesContainAllValidUppercaseChars){
    string filename = "BaseLinesContainsAllValidUppercaseChars.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForTrueTests);

    ASSERT_TRUE(result);
}

TEST_F(GenomeClassTests, BaseLinesContainAllValidLowercaseChars){
    string filename = "BaseLinesContainsAllValidLowercaseChars.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForTrueTests);

    ASSERT_TRUE(result);
}

TEST_F(GenomeClassTests, BaseLinesContainAllValidUpperAndLowerChars){
    string filename = "BaseLinesContainsAllValidUpperAndLowerChars.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForTrueTests);

    ASSERT_TRUE(result);
}

TEST_F(GenomeClassTests, LoadFuncCanExtractFirstGenomeNameFromFileTest){
    string filename = "test.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);
    string fragment;

    Genome::load(infile, genomesForTrueTests);
    string result = genomesForTrueTests[0].name();

    ASSERT_EQ(result, "NZ_NDWV01000100.1 Halorubrum chaoviator strain DSM 19316 NODE_100_length_1288_cov_24.6296, whole genome shotgun sequence");
}

TEST_F(GenomeClassTests, LoadFuncCanExtractSecondGenomeNameFromFileTest){
    string filename = "test.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);
    string fragment;

    Genome::load(infile, genomesForTrueTests);
    string result = genomesForTrueTests[1].name();

    ASSERT_EQ(result, "NZ_NDWV01000001.1 Halorubrum chaoviator strain DSM 19316 NODE_1_length_435375_cov_13.1556, whole genome shotgun sequence");
}

TEST_F(GenomeClassTests, LoadFuncCanExtractFirstGenomeSequenceFromFileTest){
    string filename = "test.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);
    string fragment;

    Genome::load(infile, genomesForTrueTests);
    genomesForTrueTests[0].extract(0, genomesForTrueTests[0].length(), fragment);

    ASSERT_EQ(fragment, "CATCCGGATCCTAATCCCG");
}

TEST_F(GenomeClassTests, LoadFuncCanExtractSecondGenomeSequenceFromFileTest){
    string filename = "test.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);
    string fragment;

    Genome::load(infile, genomesForTrueTests);
    genomesForTrueTests[1].extract(0, genomesForTrueTests[1].length(), fragment);

    ASSERT_EQ(fragment, "CGCGTAAGTCCGGCGGCGGAACGTGCCTCTGGTC");
}



// -------------- LOAD FUNCTION False Tests ----------------- //

TEST_F(GenomeClassTests, FileFormatIncorrectWhenFirstLineStartsWithBases){
    string filename = "NotStartingWithNameLine.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForFalseTests);

    ASSERT_FALSE(result);
}

TEST_F(GenomeClassTests, FileFormatIncorrectWhenFirstLineStartsWithGreaterThanAndNoOtherChars){
    string filename = "FirstLineStartsWithGreaterThanAndNoOtherChars.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForFalseTests);

    ASSERT_FALSE(result);
}

// 20
TEST_F(GenomeClassTests, FileFormatIncorrectWhenFirstLineEmpty){
    string filename = "FirstLineEmpty.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForFalseTests);

    ASSERT_FALSE(result);
}

TEST_F(GenomeClassTests, FileFormatIncorrectWhenNameLineStartsWithGreaterThanAndNoOtherChars){
    string filename = "NameLineWith>AndNoOtherChars.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForFalseTests);

    ASSERT_FALSE(result);
}



TEST_F(GenomeClassTests, FileFormatIncorrectWhenBaseLineHaveInvalidLowercaseChars){
    string filename = "BaseLinesHaveInvalidLowercaseChars.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForFalseTests);

    ASSERT_FALSE(result);
}

TEST_F(GenomeClassTests, FileFormatIncorrectWhenBaseLineHaveInvalidUppercaseChars){
    string filename = "BaseLinesHaveInvalidUppercaseChars.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForFalseTests);

    ASSERT_FALSE(result);
}

TEST_F(GenomeClassTests, FileFormatIncorrectWhenBaseLineHaveInvalidSymbolChars){
    string filename = "BaseLinesHaveInvalidSymbolChars.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForFalseTests);

    ASSERT_FALSE(result);
}

// 25
TEST_F(GenomeClassTests, FileFormatIncorrectWhenBaseLineHaveWhitespaceChars){
    string filename = "BaseLinesHaveInvalidWhitespaceChars.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForFalseTests);

    ASSERT_FALSE(result);
}

TEST_F(GenomeClassTests, FileFormatIncorrectWhenFileContainsEmptyLine){
    string filename = "EmptyLine.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForFalseTests);

    ASSERT_FALSE(result);
}

TEST_F(GenomeClassTests, FileFormatIncorrectWhenNoBaseLineAfterNameLine){
    string filename = "NoBaseLineAfterNameLine.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForFalseTests);

    ASSERT_FALSE(result);
}




// ----------------- EXTRACT FUNCTION True Tests ----------------- //

// EXAMPLE: "GCTCGGNACACATCCGCCGCGGACGGGACGGGATTCGGGCTGTCGATTGTCTCACAGATCGTCGACGTACATGACTGGGA"

TEST_F(GenomeClassTests, ExtractFragmentFromPositionZero){
    string fragment;
    g.extract(0, 3, fragment);
    ASSERT_EQ(fragment, "GCT");
}

TEST_F(GenomeClassTests, ExtractFragmentFromPositionOneBeforeEnd){
    string fragment;
    g.extract(79, 1, fragment);
    ASSERT_EQ(fragment, "A");
}

// 30
TEST_F(GenomeClassTests, ExtractFragmentFromMiddlePosition){
    string fragment;
    g.extract(50, 15, fragment);
    ASSERT_EQ(fragment, "CTCACAGATCGTCGA");
}

TEST_F(GenomeClassTests, ExtractEntireGenome){
    string fragment;
    g.extract(0, g.length(), fragment);
    ASSERT_EQ(fragment, "GCTCGGNACACATCCGCCGCGGACGGGACGGGATTCGGGCTGTCGATTGTCTCACAGATCGTCGACGTACATGACTGGGA");
}

TEST_F(GenomeClassTests, ExtractFragmentFromGenomeOfLengthOne){
    string fragment;
    g2.extract(0, 1, fragment);
    ASSERT_EQ(fragment, "A");
}



// ----------------- EXTRACT FUNCTION False Tests ----------------- //

TEST_F(GenomeClassTests, CantExtractFragmentOfLengthZero){
    string fragment;
    g2.extract(0, 0, fragment);
    ASSERT_EQ(fragment, "");
}

TEST_F(GenomeClassTests, CantExtractFragmentPastEndOfGenome){
    string fragment;
    g.extract(74, 7, fragment);
    ASSERT_EQ(fragment, "");
}





// ============================ GenomeMatcher Class Tests ================================= //

class GenomeMatcherClassTests : public ::testing::Test{
public:
    GenomeMatcherClassTests()
    : g(3),
    g1("Genome 1", "ACTG"), g2("Genome 2", "TCGACT"), g3("Genome 3", "TCTCG"),
    f(4),
    f1("Genome 1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"),
    f2("Genome 2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"),
    f3("Genome 3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA")
    {
        g.addGenome(g1);
        g.addGenome(g2);
        g.addGenome(g3);
        
        f.addGenome(f1);
        f.addGenome(f2);
        f.addGenome(f3);

        
         
    }

protected:
    GenomeMatcher g, f;
    Genome g1, g2, g3;
    Genome f1, f2, f3;
    std::vector<DNAMatch> matches;
    std::vector<GenomeMatch> results;
};




// --------------------- findGenomesWithThisDNA False Tests ------------------ //

TEST_F(GenomeMatcherClassTests, FragmentLengthLessThanMinLength){
    bool result = g.findGenomesWithThisDNA("A", 3, true, matches);
    
    ASSERT_FALSE(result);
}

TEST_F(GenomeMatcherClassTests, MinLengthParamLessThanMinSearchLength){
    bool result = g.findGenomesWithThisDNA("ACT", 2, false, matches);
    
    ASSERT_FALSE(result);
}

TEST_F(GenomeMatcherClassTests, FragmentLengthLessThanMinLengthForBigGenome){
    bool result = f.findGenomesWithThisDNA("GAAG", 3, true, matches);

    ASSERT_FALSE(result);
}

TEST_F(GenomeMatcherClassTests, MinLengthParamLessThanMinSearchLengthForBigGenome){
    bool result = f.findGenomesWithThisDNA("GAAG", 5, true, matches);

    ASSERT_FALSE(result);
}

TEST_F(GenomeMatcherClassTests, ReturnsFalseForGAATACGenomeWhenExactMatchTrue){
    bool result = f.findGenomesWithThisDNA("GAATAC", 6, true, matches);

    ASSERT_FALSE(result);
}




// --------------------- findGenomesWithThisDNA True Tests ------------------ //

TEST_F(GenomeMatcherClassTests, ReturnsTrueWhenMatchExistsWhenExactMatchOnlyIsTrue){
    bool result = g.findGenomesWithThisDNA("CGA", 3, true, matches);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, CorrectNumberOfMatchesExistWhenExactMatchOnlyIsTrue){
    g.findGenomesWithThisDNA("CGA", 3, true, matches);
    int size = matches.size();

    ASSERT_EQ(size, 1);
}

TEST_F(GenomeMatcherClassTests, CorrectDNANameWhenMatchesExistWhenExactMatchOnlyIsTrue){
    g.findGenomesWithThisDNA("CGA", 3, true, matches);
    string name = matches[0].genomeName;

    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, CorrectDNALengthWhenMatchesExistWhenExactMatchOnlyIsTrue){
    g.findGenomesWithThisDNA("CGA", 3, true, matches);
    int length = matches[0].length;

    ASSERT_EQ(length, 3);
}

TEST_F(GenomeMatcherClassTests, CorrectDNAPositionWhenMatchesExistWhenExactMatchOnlyIsTrue){
    g.findGenomesWithThisDNA("CGA", 3, true, matches);
    int position = matches[0].position;

    ASSERT_EQ(position, 1);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectGenomeWhenExactMatchTrue){
    g.findGenomesWithThisDNA("CGACT", 3, true, matches);
    string name = matches[0].genomeName;

    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionWhenExactMatchTrue){
    g.findGenomesWithThisDNA("CGACT", 3, true, matches);
    int position = matches[0].position;

    ASSERT_EQ(position, 1);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthWhenExactMatchTrue){
    g.findGenomesWithThisDNA("CGACT", 3, true, matches);
    int length = matches[0].length;

    ASSERT_EQ(length, 5);
}

TEST_F(GenomeMatcherClassTests, ReturnsTrueWhenFoundMatchWhenExactMatchTrue){
    bool result = g.findGenomesWithThisDNA("CGACT", 3, true, matches);

    ASSERT_TRUE(result);
}

// -----------------

TEST_F(GenomeMatcherClassTests, ReturnsTrueForGAAGGenomeWhenExactMatchTrue){
    bool result = f.findGenomesWithThisDNA("GAAG", 4, true, matches);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAAGGenome1WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAAG", 4, true, matches);
    string name = matches[0].genomeName;

    ASSERT_EQ(name, "Genome 1");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAAGGenome1WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAAG", 4, true, matches);
    int position = matches[0].position;

    ASSERT_EQ(position, 60);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAAGGenome1WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAAG", 4, true, matches);
    int length = matches[0].length;

    ASSERT_EQ(length, 4);
}

// ----------------

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAAGGenome2WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAAG", 4, true, matches);
    string name = matches[1].genomeName;

    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAAGGenome2WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAAG", 4, true, matches);
    int position = matches[1].position;

    ASSERT_EQ(position, 54);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAAGGenome2WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAAG", 4, true, matches);
    int length = matches[1].length;

    ASSERT_EQ(length, 4);
}

// ---------------

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAAGGenome3WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAAG", 4, true, matches);
    string name = matches[2].genomeName;

    ASSERT_EQ(name, "Genome 3");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAAGGenome3WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAAG", 4, true, matches);
    int position = matches[2].position;

    ASSERT_EQ(position, 29);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAAGGenome3WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAAG", 4, true, matches);
    int length = matches[2].length;

    ASSERT_EQ(length, 4);
}


// -----------------

TEST_F(GenomeMatcherClassTests, ReturnsTrueForGAATACGenomeWhenExactMatchTrue){
    bool result = f.findGenomesWithThisDNA("GAATAC", 4, true, matches);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAATACGenome1WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAATAC", 4, true, matches);
    string name = matches[0].genomeName;

    ASSERT_EQ(name, "Genome 1");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAATACGenome1WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAATAC", 4, true, matches);
    int position = matches[0].position;

    ASSERT_EQ(position, 22);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAATACGenome1WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAATAC", 4, true, matches);
    int length = matches[0].length;

    ASSERT_EQ(length, 5);
}

// ----------------

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAATACGenome2WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAATAC", 4, true, matches);
    string name = matches[1].genomeName;

    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAATACGenome2WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAATAC", 4, true, matches);
    int position = matches[1].position;

    ASSERT_EQ(position, 48);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAATACGenome2WhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAATAC", 4, true, matches);
    int length = matches[1].length;

    ASSERT_EQ(length, 5);
}

TEST_F(GenomeMatcherClassTests, CorrectNumberOfMatchesFoundForGAATACWhenExactMatchTrue){
    f.findGenomesWithThisDNA("GAATAC", 4, true, matches);
    int size = matches.size();

    ASSERT_EQ(size, 2);
}



// ------------- Testing with ExactMatchOnly == False

// -------------------------- fragment == GAATAC --------------------------------
TEST_F(GenomeMatcherClassTests, ReturnsTrueForGAATACGenomeWhenExactMatchFalse){
    bool result = f.findGenomesWithThisDNA("GAATAC", 6, false, matches);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAATACGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATAC", 6, false, matches);
    string name = matches[0].genomeName;

    ASSERT_EQ(name, "Genome 1");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAATACGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATAC", 6, false, matches);
    int position = matches[0].position;

    ASSERT_EQ(position, 22);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAATACGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATAC", 6, false, matches);
    int length = matches[0].length;

    ASSERT_EQ(length, 6);
}


TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAATACGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATAC", 6, false, matches);
    string name = matches[1].genomeName;

    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAATACGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATAC", 6, false, matches);
    int position = matches[1].position;

    ASSERT_EQ(position, 48);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAATACGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATAC", 6, false, matches);
    int length = matches[1].length;

    ASSERT_EQ(length, 6);
}

TEST_F(GenomeMatcherClassTests, CorrectNumOfMatchesForGAATACWithMinLen6WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATAC", 6, false, matches);
    int size = matches.size();

    ASSERT_EQ(size, 2);
}


// -------------------------- fragment == GTATAT --------------------------------
TEST_F(GenomeMatcherClassTests, ReturnsTrueForGTATATGenomeWhenExactMatchFalse){
    bool result = f.findGenomesWithThisDNA("GTATAT", 6, false, matches);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGTATATGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GTATAT", 6, false, matches);
    string name = matches[0].genomeName;

    ASSERT_EQ(name, "Genome 1");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGTATATGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GTATAT", 6, false, matches);
    int position = matches[0].position;

    ASSERT_EQ(position, 22);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGTATATGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GTATAT", 6, false, matches);
    int length = matches[0].length;

    ASSERT_EQ(length, 6);
}


TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGTATATGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GTATAT", 6, false, matches);
    string name = matches[1].genomeName;

    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGTATATGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GTATAT", 6, false, matches);
    int position = matches[1].position;

    ASSERT_EQ(position, 48);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGTATATGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GTATAT", 6, false, matches);
    int length = matches[1].length;

    ASSERT_EQ(length, 6);
}

TEST_F(GenomeMatcherClassTests, CorrectNumOfMatchesForGTATATWithMinLen6WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GTATAT", 6, false, matches);
    int size = matches.size();

    ASSERT_EQ(size, 2);
}



// -------------------------- fragment == GAATACG --------------------------------
TEST_F(GenomeMatcherClassTests, ReturnsTrueForGAATACGGenomeWhenExactMatchFalse){
    bool result = f.findGenomesWithThisDNA("GAATACG", 6, false, matches);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, CorrectNumOfMatchesForGAATACGWithMinLen6WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATACG", 6, false, matches);
    int size = matches.size();

    ASSERT_EQ(size, 2);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAATACGGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATACG", 6, false, matches);
    string name = matches[0].genomeName;

    ASSERT_EQ(name, "Genome 1");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAATACGGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATACG", 6, false, matches);
    int position = matches[0].position;

    ASSERT_EQ(position, 22);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAATACGGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATACG", 6, false, matches);
    int length = matches[0].length;

    ASSERT_EQ(length, 6);
}


TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAATACGGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATACG", 6, false, matches);
    string name = matches[1].genomeName;

    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAATACGGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATACG", 6, false, matches);
    int position = matches[1].position;

    ASSERT_EQ(position, 48);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAATACGGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAATACG", 6, false, matches);
    int length = matches[1].length;

    ASSERT_EQ(length, 7);
}



// -------------------------- fragment == GAAGGGTT --------------------------------
TEST_F(GenomeMatcherClassTests, ReturnsTrueForGAAGGGTTGenomeWhenExactMatchFalse){
    bool result = f.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, CorrectNumOfMatchesForGAAGGGTTWithMinLen5WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
    int size = matches.size();

    ASSERT_EQ(size, 3);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAAGGGTTGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
    string name = matches[0].genomeName;

    ASSERT_EQ(name, "Genome 1");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAAGGGTTGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
    int position = matches[0].position;

    ASSERT_EQ(position, 60);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAAGGGTTGenome1WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
    int length = matches[0].length;

    ASSERT_EQ(length, 8);
}


TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAAGGGTTGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
    string name = matches[1].genomeName;

    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAAGGGTTGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
    int position = matches[1].position;

    ASSERT_EQ(position, 54);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAAGGGTTGenome2WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
    int length = matches[1].length;

    ASSERT_EQ(length, 5);
}


TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAAGGGTTGenome3WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
    string name = matches[2].genomeName;

    ASSERT_EQ(name, "Genome 3");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAAGGGTTGenome3WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
    int position = matches[2].position;

    ASSERT_EQ(position, 35);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAAGGGTTGenome3WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
    int length = matches[2].length;

    ASSERT_EQ(length, 7);
}



// -------------------------- fragment == GAAGGGTT --------------------------------
TEST_F(GenomeMatcherClassTests, ReturnsTrueForGAAGGGTTGenomeWithMinLen6WhenExactMatchFalse){
    bool result = f.findGenomesWithThisDNA("GAAGGGTT", 6, false, matches);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, CorrectNumOfMatchesForGAAGGGTTWithMinLen6WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 6, false, matches);
    int size = matches.size();

    ASSERT_EQ(size, 2);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAAGGGTTGenome1WithMinLen6WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 6, false, matches);
    string name = matches[0].genomeName;

    ASSERT_EQ(name, "Genome 1");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAAGGGTTGenome1WithMinLen6WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 6, false, matches);
    int position = matches[0].position;

    ASSERT_EQ(position, 60);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAAGGGTTGenome1WithMinLen6WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 6, false, matches);
    int length = matches[0].length;

    ASSERT_EQ(length, 8);
}


TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForGAAGGGTTGenome3WithMinLen6WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 6, false, matches);
    string name = matches[1].genomeName;

    ASSERT_EQ(name, "Genome 3");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForGAAGGGTTGenome3WithMinLen6WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 6, false, matches);
    int position = matches[1].position;

    ASSERT_EQ(position, 35);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForGAAGGGTTGenome3WithMinLen6WhenExactMatchFalse){
    f.findGenomesWithThisDNA("GAAGGGTT", 6, false, matches);
    int length = matches[1].length;

    ASSERT_EQ(length, 7);
}



// -------------------------- fragment == ACGTGCGAGACTTAGAGCC --------------------------------
TEST_F(GenomeMatcherClassTests, ReturnsTrueForACGTGCGAGACTTAGAGCCGenomeWhenExactMatchFalse){
    bool result = f.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC", 12, false, matches);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, CorrectNumOfMatchesForACGTGCGAGACTTAGAGCCWhenExactMatchFalse){
    f.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC", 12, false, matches);
    int size = matches.size();

    ASSERT_EQ(size, 1);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForACGTGCGAGACTTAGAGCCWhenExactMatchFalse){
    f.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC", 12, false, matches);
    string name = matches[0].genomeName;

    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForACGTGCGAGACTTAGAGCCWhenExactMatchFalse){
    f.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC", 12, false, matches);
    int position = matches[0].position;

    ASSERT_EQ(position, 28);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForACGTGCGAGACTTAGAGCCWhenExactMatchFalse){
    f.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC", 12, false, matches);
    int length = matches[0].length;

    ASSERT_EQ(length, 19);
}



// -------------------------- fragment == ACGTGCGAGACTTAGAGCG --------------------------------
TEST_F(GenomeMatcherClassTests, ReturnsTrueForACGTGCGAGACTTAGAGCGGenomeWhenExactMatchFalse){
    bool result = f.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCG", 12, false, matches);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, CorrectNumOfMatchesForACGTGCGAGACTTAGAGCGWhenExactMatchFalse){
    f.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCG", 12, false, matches);
    int size = matches.size();

    ASSERT_EQ(size, 1);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectNameForACGTGCGAGACTTAGAGCGWhenExactMatchFalse){
    f.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCG", 12, false, matches);
    string name = matches[0].genomeName;

    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectPositionForACGTGCGAGACTTAGAGCGWhenExactMatchFalse){
    f.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCG", 12, false, matches);
    int position = matches[0].position;

    ASSERT_EQ(position, 28);
}

TEST_F(GenomeMatcherClassTests, ExtractedCorrectLengthForACGTGCGAGACTTAGAGCGWhenExactMatchFalse){
    f.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCG", 12, false, matches);
    int length = matches[0].length;

    ASSERT_EQ(length, 19);
}





// ========================== findRelatedGenomes False Tests ================================== //

TEST_F(GenomeMatcherClassTests, ReturnsFalseWhenFragmentMatchLenLessThanMinSearchLen){
    Genome query("test", "ABCD");
    bool result = f.findRelatedGenomes(query, 3, false, 23.0, results);

    ASSERT_FALSE(result);
}




// ========================== findRelatedGenomes True Tests ================================== //

TEST_F(GenomeMatcherClassTests, ReturnsTrueWhenExactMatchTrue){
    Genome query("test", "GAAG");
    bool result = f.findRelatedGenomes(query, 4, true, 0.0, results);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, CorrectNumberOfMatchesWhenExactMatchTrue){
    Genome query("test", "GAAG");
    f.findRelatedGenomes(query, 4, true, 0.0, results);
    int size = results.size();
    ASSERT_EQ(size, 3);
}

TEST_F(GenomeMatcherClassTests, CorrectFirstGenomeNameWhenExactMatchTrue){
    Genome query("test", "GAAG");
    f.findRelatedGenomes(query, 4, true, 0.0, results);
    string name = results[0].genomeName;
    ASSERT_EQ(name, "Genome 1");
}

TEST_F(GenomeMatcherClassTests, CorrectSecondGenomeNameWhenExactMatchTrue){
    Genome query("test", "GAAG");
    f.findRelatedGenomes(query, 4, true, 0.0, results);
    string name = results[1].genomeName;
    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, CorrectThirdGenomeNameWhenExactMatchTrue){
    Genome query("test", "GAAG");
    f.findRelatedGenomes(query, 4, true, 0.0, results);
    string name = results[2].genomeName;
    ASSERT_EQ(name, "Genome 3");
}



TEST_F(GenomeMatcherClassTests, FoundAtLeastOneMatch){
    Genome query("test", "GAAGACTT");
    bool result = f.findRelatedGenomes(query, 4, true, 50, results);

    ASSERT_TRUE(result);
}

TEST_F(GenomeMatcherClassTests, ResultsVectorContainsCorrectNumberOfMatches){
    Genome query("test", "GAAGACTT");
    f.findRelatedGenomes(query, 4, true, 50, results);
    int size = results.size();
    ASSERT_EQ(size, 3);
}

TEST_F(GenomeMatcherClassTests, CorrectOrderingOfGenomesInVector){
    Genome query("test", "GAAGACTT");
    f.findRelatedGenomes(query, 4, true, 50, results);
    string name = results[0].genomeName;
    ASSERT_EQ(name, "Genome 2");
}

TEST_F(GenomeMatcherClassTests, CorrectPercentageOfMatch){
    Genome query("test", "GAAGACTT");
    f.findRelatedGenomes(query, 4, true, 50, results);
    double result = results[0].percentMatch;
    ASSERT_EQ(result, 100);
}

TEST_F(GenomeMatcherClassTests, CorrectNextLargestPercentageOfMatchInResultsVector){
    Genome query("test", "GAAGACTT");
    f.findRelatedGenomes(query, 4, true, 50, results);
    string name = results[1].genomeName;
    ASSERT_EQ(name, "Genome 1");
}

TEST_F(GenomeMatcherClassTests, CorrectLastPercetageOfMatchInResultsVector){
    Genome query("test", "GAAGACTT");
    f.findRelatedGenomes(query, 4, true, 50, results);
    string name = results[2].genomeName;
    ASSERT_EQ(name, "Genome 3");
}
