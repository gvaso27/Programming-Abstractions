/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include "map.h"
#include "vector.h"
#include "random.h"
#include "simpio.h"
#include "console.h"
using namespace std;

/*this number shows how many charachters should be in generated text*/
const int numCharacters = 2000;

/*this void creates map with keys and their following values*/
void createMap(Map <string, Vector<char> > &association, Vector <string> keys, int k);

/*this string finds the most frequent k-length charachters*/
string findFrequent(Map <string, Vector<char> > association, Vector <string> keys, int k);

/*this void prints the final genrated text*/
void print (string first, Map <string, Vector<char> > association, int k);

int main() {
	string text = getLine("Write name of the text document: ");
	ifstream input(text.c_str());

	/*check if fileName is valid*/
	while(!input.is_open()){
		input.clear();
		text = getLine("This file does not exist. Try again: ");
		input.open(text.c_str());
	}

	/*check if markov number is in range*/
	int k = getInteger("Enter the markov order[1-10]: ");
	while(k < 1 || k >10){
		k = getInteger("Markov number is out of range. Try again [1-10]: ");
	}

	char ch;
	Vector <string> keyValues;
	string s;
	while(input.get(ch)){

		/*this creates vector of k+1 charachters where k charachters are keys
		and the last charachter is value*/
		s += ch;
		if(s.length() == k + 1){
			keyValues.add(s);
			s = s.substr(1);
		}

	}
	Map <string, Vector<char> > association;
	createMap(association, keyValues, k);
	string first = findFrequent(association, keyValues, k);
	print(first, association, k);
    return 0;
}

void createMap(Map <string, Vector<char> > &association, Vector <string> keys, int k){
	string key;
	char v;
	for(int i = 0; i < keys.size(); i++){
		key = keys[i].substr(0, k);
		v = keys[i][k];
		association[key].add(v);
	}
}

 string findFrequent(Map <string, Vector<char> > association, Vector <string> keys, int k){
	int maxSize = 0;
	string max;
	for(int i = 0; i < keys.size(); i++){
		if(association[keys[i].substr(0, k)].size() > maxSize){
			maxSize = association[keys[i].substr(0, k)].size();
			max = keys[i].substr(0, k);
		}
	}
	return max;
}

 void print (string first, Map <string, Vector<char> > association, int k){
	 cout<<first;//first k charachters must be the most frequent ones
	 int rand;
	 while(k != numCharacters){
		 rand = randomInteger(0, association[first].size() - 1);
		 cout<<association[first][rand];
		 first = first.substr(1) + association[first][rand];
		 k++;
	 }
 }