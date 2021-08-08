<!-- sections:

    1. Title
    2. Introduction
    3. Implementation
    4. Features
    5. Usage
    6. Testing

 -->

 <!-- PROJECT TITLE -->

# Gee-nomics DNA Search System

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#introduction">Introduction</a></li>
    <li><a href="#implementation-overview">Implementation Overview</a></li>
    <li><a href="#features">Features</a></li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#testing">Testing</a></li>
  </ol>
</details>

<!-- Introduction -->

## Introduction

Virtually all organisms on earth (except for perhaps RNA-based viruses) are DNA-based. DNA, which stands for deoxyribonucleic acid, is a chemical strand comprised of long sequences of just four different chemical units: adenine, cytosine, thymine, and guanine. These four chemical units (called bases or nucleotides) are usually referred to by their letter abbreviations, A, C, T and G. Organisms from viruses and bacteria to humans have long strands of DNA, comprised of thousands to billions of these simple DNA bases. Each organism is uniquely defined by its particular strand of DNA, and with the exception of identical twins and organisms that clone themselves, no two organisms share the same sequence of A, C, T and G bases.

The DNA of a particular organism is called its genome. Each genome is comprised of up to tens of thousands of different genes, and each gene is made up of hundreds or thousands of these individual A, C, T and G DNA bases. Each gene is responsible for one or more aspects of the organism’s biological processes such as the organism’s eye color, its height, how the organism produces energy from its food sources, etc.

Here is an example of the first 60 bases of the DNA sequence (consists of over 3 million total DNA bases) for the organism Halobacterium jilantaiense:

    GGTTCTCAATGAATGGCAAGAGCTTCAACCCGACAACTCCGTCCTCACCGGCCGACAAT

Different organisms (even of different species) often share many of the same or related genes which is important for a number of reasons:

- We can test drugs on an organism (e.g., a mouse) with similar genetics to ours and predict whether the drugs will be toxic or likely work in humans.
- We can deduce how a drug will work on one infection that is closely related to another infection.
- We can understand how two different types of organisms are related and how they may be related to a common ancestor.

If two sequences of DNA bases differ by only a single DNA base, this is called a SNiP or single nucleotide polymorphism

This software serves to process genetic data and:

- Maintain a library of genomes from multiple organisms; the user can add new genomes to this library.
- Allow the user to search the library for a specified DNA sequence and identify all genomes in the library that contain that DNA sequence or any SNiP of it.
- Allow the user to present the genome/DNA of a new organism and quickly identify all genomes in the library that have a high percentage of matching DNA with the presented genome.

<!-- Implementation Overview  -->

## Implementation Overview

Implemented three main classes to process and store genetic data:

### Trie.h

Trie is a template based multi-map class based on the trie data structure. It can be used to map any C++ string of characters to one or more values (of the templated type). When the user searches for a key string (e.g. “ACTGGTCA”), not only will object provide all values associated with the exact, searched-for key string, but it will also be able to return all values associated with any string in the Trie which differs by at most one character from the searched for key string. So, when searching a Trie, the user can request that the class return either (a) only exact matches, or (b) both exact matches AND matches that differ by exactly one character (except that the first character of the search string does not differ)!

### Genome.cpp

Genome will be used to load organisms' genomes from a data file and, once loaded, allow a user to (a) obtain an organism’s name, and (b) extract any subsequence of an organism’s DNA genome. The user can call a function declared in the Genome class to load genome data from a specially-formatted genomic data file. The genomic data file contains both the name of the organism (e.g., Ferroglobus_placidus) and DNA sequences of the organism, consisting of millions of As, Cs, Ts and Gs.

### GenomeMatcher.cpp

Maintains a library of Genome objects and allows the user of the class to:

- Add a new organism’s Genome to the library
- Search all the genomes held in the library for a given DNA sequence, e.g. “Find the names of all genomes in the library whose DNA sequence contains ‘ACCATGGATTACA’ or some SNiP of that sequence such as ACCATGAATTACA’, and tell me at what offset(s) these located sequences were found in each genome.”
- Search the library to identify all genomes in the library whose DNA contains at least T% overlap with a given Genome, where the threshold T is specified by the user (e.g., T = 15%). This might be used to identify organisms whose genomes are closely related to a queried organism’s genome.

<!-- FEATURES EXAMPLES -->

## Features

- Add a genome to the library by typing a name and DNA sequence
- Load a genome data file into the library
- If you have many genome files, load all of the genomes into the library at once to save you time
- Search for an exact DNA match like 'CGTTAGAG' without any mismatching bases
- Search for an DNA match like 'CGTTAGAG' allowing one mismatching base, e.g., searching for 'CGTTAGAG' could match 'CGTTAGGG' within a genome
- Type a DNA sequence and identify all genomes in the library that are close matches of that genome
- Specify a genome data file and identify all genomes in the library that are close matches to that genome.

<!-- USAGE EXAMPLES -->

## Usage

When you run the program, it might look like this:

```
Welcome to the Gee-nomics test harness!
The genome library is initially empty, with
Commands:
    c - create new genome library
    a - add one genome manually
    l - load one data file
    d - load all provided data files e - find matches exactly
    a default minSearchLength of 10
    s-find matching SNiPs
    r-find related genomes (manual) f-find related genomes (file) ?-show this menu
    q-quit
Enter command: a
Enter name: yeti
Enter DNA sequence: ACGTACGTAAAACCCCGGGGTTTTNANANANANA Enter command: e
Enter DNA sequence for which to find
Enter minimum sequence match length:
    1 matches of AAAACCCCGGGGTTNN found:
exact matches: AAAACCCCGGGGTTNN 12
    length 14 position 8 in yeti
Enter command: e
Enter DNA sequence for which to find
Enter minimum sequence match length:
    No matches of CCCCAAAATTTT were found.
Enter command: s
Enter DNA sequence for which to find exact matches and SNiPs: AAAACCTCGGGGTTNN Enter minimum sequence match length: 12
    1 matches and/or SniPs of AAAACCTCGGGGTTNN found:
    length 14 position 8 in yeti
Enter command: c
Enter minimum search length (3-100): 4
Enter command: a
Enter name: sasquatch
Enter DNA sequence: GGGGTTTTAAAACCCCACGTACGTACGTNANANANA Enter command: r
Enter DNA sequence: AAATCCCTGGGGTTTTNANA
Enter match percentage threshold (0-100): 20
Require (e)xact match or allow (S)NiPs (e or s): s
    1 related genomes were found: 50.00% sasquatch
Enter command: c
Enter minimum search length (3-100): 10
Enter command: d
    Loaded 1 genomes from Ferroplasma_acidarmanus.txt
    Loaded 2 genomes from Halobacterium_jilantaiense.txt
    Loaded 105 genomes from Halorubrum_chaoviator.txt
    Loaded 83 genomes from Halorubrum_californiense.txt
    Loaded 55 genomes from Halorientalis_regularis.txt
    Loaded 121 genomes from Halorientalis_persicus.txt
    Loaded 1 genomes from Ferroglobus_placidus.txt
    Loaded 1 genomes from Desulfurococcus_mucosus.txt
Enter command: e
Enter DNA sequence for which to find exact matches: ACGAATCACGTGCGAGA Enter minimum sequence match length: 11
    2 matches of ACGAATCACGTGCGAGA found:
    length 17 position 568 in NZ_AOJK01000080.1 Halorubrum californiensis DSM 19288 contig_80, whole genome shotgun sequence
    length 12 position 1977 in NZ_FOCX01000065.1 Halorientalis persicus strain IBRC- M 10043, whole genome shotgun sequence
Enter command: q
```

<!-- Testing -->

## Testing

Utilized [GoogleTest](https://github.com/google/googletest) to perform unit tests.

### Example of testing find method in Trie class

```
TEST_F(TrieClassTests, FindValuesAssocWithExactKeyWhenTrue){

    vector<int> result = trie.find("tap", true);
    vector<int> expected = {32, 6, 19};
    sortVectors(result, expected);

    ASSERT_EQ(result, expected);

}
```

### Example of testing load method in Genome class

```
TEST_F(GenomeClassTests, FirstLineStartsWithGreaterSymbolAndValidName){
    string filename = "FirstLineStartsWithGreaterAndValidName.txt";
    string file = concatFileNameToPath(filename);
    ifstream infile(file);

    bool result = Genome::load(infile, genomesForTrueTests);

    ASSERT_TRUE(result);
}
```
