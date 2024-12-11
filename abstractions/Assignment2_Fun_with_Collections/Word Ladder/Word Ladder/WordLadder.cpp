/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <vector>
#include <string>
#include "set.h"
#include "simpio.h"
#include "lexicon.h"
#include "queue.h"
#include "console.h"
using namespace std;

/*this vois finds the path if it exists*/
void findPath(Lexicon words, string startWord, string endWord);

int main() {
	while(true){
		Lexicon words("EnglishWords.dat");//read every word from file
		string startWord = getLine("Enter the start word (or nothing to quit): ");
		if(startWord == ""){
			cout<<"good bye!"<<endl;
			break;
		}
		while(!words.contains(startWord)){
			startWord = getLine("Try again. Enter the start word (or nothing to quit): ");
		}
		string endWord = getLine("Enter the end word: ");
		while(startWord.length() != endWord.length() || !words.contains(endWord)){
			cout<<"unable to find path, try again"<<endl;
			endWord = getLine("Enter the end word: ");
		}
		findPath(words, startWord, endWord);
	}
    return 0;
}

void findPath(Lexicon words, string startWord, string endWord){

	/*this vector is a path from start to end word*/
	vector<string> ladder;

	/*this queue stores every path of words*/
	Queue< vector<string> > wordLadder;

	ladder.push_back(startWord);
	wordLadder.enqueue(ladder);

	/*we use this vector to check if we have reached the end word*/
	vector<string> test;

	/*this set stores every used word*/
	Set<string> used;

	string newWord;
	while(!wordLadder.isEmpty()){
		test = wordLadder.dequeue();
		if(endWord == test.back()){
			for(int i = 0; i < test.size() - 1; i++){
				cout<<test[i]<<"->";
			}
			cout<<test.back()<<endl;
			break;
		}
		for(char ch = 'a'; ch <= 'z'; ch++){
			for(int i = 0; i < test.back().length(); i++){
				newWord = test.back();
				newWord[i] = ch;
				if(words.contains(newWord) && !used.contains(newWord)){
					vector<string> copy;
					copy = test;
					copy.push_back(newWord);
					used.add(newWord);
					wordLadder.enqueue(copy);
				}
			}
		}
	}
	if(endWord != test.back()){
	cout<<"path does not exist"<<endl;
	}
}
