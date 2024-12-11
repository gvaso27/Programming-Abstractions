/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "tokenscanner.h"
#include "simpio.h"
#include "console.h"
#include "strlib.h"
using namespace std;

//these are constants to calculate the final grade
const double C0 =  -15.59;
const double C1 =  0.39;
const double C2 =  11.8;

int numWords = 0;//number of words
int numSent = 0;//number of sentences
int numSyll = 0;//number of syllables
double grade = 0;

void countInfo(string line);//this counts words, sentences and syllables
int countSyllInWord(string word);//this counts number of syllables in the word
bool checkIfCharSyll(char ch);//returns true if the charachter is syllable
void countGrade(int wo, int se, int sy);//counts grade


int main() {
	string file = getLine("Enter the file name: ");
	ifstream input(file.c_str());
	string line;
	while(getline(input, line)){
		countInfo(line);
	}
	if(numWords == 0)numWords = 1;
	if(numSent == 0)numSent = 1;
	countGrade(numWords, numSent, numSyll);
	cout<<"Number of Words: "<<numWords<<endl;
	cout<<"Number of Sentences: "<<numSent<<endl;
	cout<<"Number of Syllables: "<<numSyll<<endl;
	cout<<"The final grade is: "<<grade<<endl;
    return 0;
}

void countInfo(string line){
	TokenScanner scanner(line);
	scanner.addWordCharacters("'");
	while(scanner.hasMoreTokens()){
		string token = scanner.nextToken();
		if(scanner.getTokenType(token) == WORD && token != "'"){
			numWords++;
			numSyll += countSyllInWord(token);
		}
		if(scanner.getTokenType(token) == OPERATOR){
			if(token == "." || token == "?" || token == "!")numSent++;
		}
	}
}

int countSyllInWord(string word){
	int syllInWord = 0;
	if(word.length() > 1){ 
		for(int i = 0; i < word.length() - 1; i++){
			if(checkIfCharSyll(word[i]) && !checkIfCharSyll(word[i + 1]))syllInWord++;
		}
		if(checkIfCharSyll(word[word.length() - 1]))syllInWord++;
		if((word[word.length() - 1] == 'e' || word[word.length() - 1] == 'E') && 
			!checkIfCharSyll(word[word.length() - 2]))syllInWord--;
	}
	if(syllInWord == 0)syllInWord = 1;
	return syllInWord;
}

bool checkIfCharSyll(char ch){
	if(ch == 'a' || ch == 'e' || ch == 'i' ||
		ch == 'o' || ch == 'u' || ch == 'y' ||
		ch == 'A' || ch == 'E' || ch == 'I' ||
		ch == 'U' || ch == 'O' || ch == 'Y'){
			return true;
	}else{
		return false;
	}
}

void countGrade(int wo, int se, int sy){
	grade = C0 + (C1*wo/se) + (C2*sy/wo);
}