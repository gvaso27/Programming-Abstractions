/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "strlib.h"
#include "simpio.h"
#include "set.h"
#include "vector.h"
#include "map.h"
#include "console.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

//numOfSolutions is number of combinations we can get given protein
int numOfSolutions = 1;

//this vector stores all the combinations the we get given protein with
Vector <string> result;

//this number equals one if we have not yet removed a member from (protein[0])set 
int identifier = 1;

//this is the size of result vector after we have added the first codon of (protein[0])set in it
int size;

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();

	//I didn't want to change the original codons map so i created copy of it
	Map<char, Set<string> > copyMap = codons;

	string protein = getLine("Write protein to see it's codons: ");
	protein = toUpperCase(protein);

	//this for cycle count the number of solutions
	for(int i = 0; i < protein.length(); i++){
		numOfSolutions = numOfSolutions * codons[protein[i]].size();
	}

	//this for cycle adds (protein[0])set in vector
	for(int i = 0; i < codons[protein[0]].size(); i++){
		result.add(copyMap[protein[0]].first());
		copyMap[protein[0]].remove(copyMap[protein[0]].first());
	}

	//calling reccursive function
	listAllRNAStrandsFor(protein.substr(1), copyMap);

	cout<<result<<endl;
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){

	//base case is if we already have all the combinations in our result vector
	if(numOfSolutions == result.size())return;

	//if all the element of (protein[0])set have been aded correctly in vector we move to the new (peotein[1])set
	if(codons[protein[0]].isEmpty()){
		identifier = 1;
		listAllRNAStrandsFor(protein.substr(1), codons);

	/*in this if statement we add all the remaining members in the (protein[0])set 
	in result vector so that the combinations do not repeate themselves*/
	}else if(identifier == 0){

		//addMember is new string that we will add in result vector
		string addMember;

		for(int i = 0; i < size; i++){
			addMember = result[i].substr(0, result[i].size() - 3) + 
				codons[protein[0]].first();
			result.add(addMember);
		}
		codons[protein[0]].remove(codons[protein[0]].first());
		listAllRNAStrandsFor(protein, codons);

		//in this else statement we are adding first codon from (protein[0])set in vector
	}else{
		for(int i = 0; i < result.size(); i++){
			result[i] += codons[protein[0]].first();
		}
		codons[protein[0]].remove(codons[protein[0]].first());
		identifier = 0;
		size = result.size();
		listAllRNAStrandsFor(protein, codons);
	}
}