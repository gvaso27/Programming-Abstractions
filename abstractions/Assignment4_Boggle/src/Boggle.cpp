/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gboggle.h"
#include "grid.h"
#include "set.h"
#include "vector.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void rollTheDice(Vector<Vector<char>> &board, string size);
void allPossibleSolutions(Vector<Vector<char>> cubes, Set<string> &solutions, 
						  int x, int y, string current, Lexicon words);
bool ifStandard(string &standardOrNot);
void humanTurn(Set<string> &solutions, Vector<Vector<char>> board);
void findInsertedWordOnBoard(Set<string> &solutions, string word, Vector<Vector<char>> board,
							 int x, int y, string unchanged);
void computerTurn(Set<string> solutions);
/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();
	Lexicon words("EnglishWords.dat");
	string standardOrNot;
	while(!(standardOrNot == "yes" || standardOrNot == "no")){
		standardOrNot = getLine ("Do you want to use standard (4X4) deck?(type yes or no) ");
		standardOrNot = toLowerCase(standardOrNot);
	}
	if(ifStandard(standardOrNot)){
		drawBoard(4, 4);
	}else{drawBoard(5, 5);}
	Vector<Vector<char>> board;
	rollTheDice(board, standardOrNot);
	Set<string> solutions;
	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j < board.size(); j++){
			allPossibleSolutions(board, solutions, i, j, "", words);
		}
	}
	humanTurn(solutions, board);
	computerTurn(solutions);
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

//this function finds all the words that can be found on the board
void allPossibleSolutions(Vector<Vector<char>> cubes, Set<string> &solutions, 
						  int x, int y, string current, Lexicon words){
	if(x < 0 || y < 0 || x >= cubes.size() || y >= cubes.size())return;
	if(cubes[x][y] == '0')return;
	if(!words.containsPrefix(current))return;
	current += cubes[x][y];
	cubes[x][y] = '0';
	if(words.contains(current))solutions.add(current);
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			allPossibleSolutions(cubes, solutions, x+i, y+j, current, words);
		}
	}
}

//this function rolls the dice
void rollTheDice(Vector<Vector<char>> &board, string standardOrNot){
	Vector<string> deck;
	if(ifStandard(standardOrNot)){
		for(int i = 0; i < 16; i++){
			deck.add(STANDARD_CUBES[i]);
		}
	}else{
		for(int i = 0; i < 25; i++){
			deck.add(BIG_BOGGLE_CUBES[i]);
		}
	}
	int m;
	string s;
	Vector<char> temp;
	for(int i = 0; i < deck.size(); i++){
		m = randomInteger(i, deck.size()-1);
		s = deck[m];
		deck[m] = deck[i];
		deck[i] = s;
		m = randomInteger(0, 5);
		temp.add(deck[i][m]);
		labelCube(board.size(), temp.size()-1, temp[temp.size()-1]);
		if(temp.size() == (int)sqrt((double)deck.size())){
			board.add(temp);
			temp.clear();
		}
	}
}

//check if inserted string is valid
bool ifStandard(string &standardOrNot){
	if(standardOrNot == "yes")return true;
	if(standardOrNot == "no")return false;
	return false;
}

//this function is responsible for human turn of the game
void humanTurn(Set<string> &solutions, Vector<Vector<char>> board){
	string word = " ";
	while(word != ""){
		word = getLine("Enter already found word(press enter if you are done)");
		while(word.length()<4 && word.length()>0){
			word = getLine("word must contain more than 3 charachters: ");
		}
		word = toUpperCase(word);
		if(solutions.contains(word)){
			for(int i = 0; i < board.size(); i++){
				for(int j = 0; j < board.size(); j++){
					findInsertedWordOnBoard(solutions, word, board, i, j, word);
				}
			}
			for(int i = 0; i < board.size(); i++){
				for(int j = 0; j < board.size(); j++){
					highlightCube(i, j, false);
				}
			}
			recordWordForPlayer(word, HUMAN);
		}else{cout<<"that word does not exist or it can't be found on the board"<<endl;}
	}
}

//this functions finds inserted word in the board
void findInsertedWordOnBoard(Set<string> &solutions, string word, Vector<Vector<char>> board,
							 int x, int y, string unchanged){
	if(x < 0 || y < 0 || x >= board.size() || y >= board.size())return;
	if(board[x][y] != word[0])return;
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			if(board[x][y] == word[0]){
				findInsertedWordOnBoard(solutions, word.substr(1), board, x+i, x+j, unchanged);
				if(word.length() == 1){
					highlightCube(x, y, true);
					solutions.remove(unchanged);
				}
			}
		}
	}
}

//this function is responsible for computer turn
void computerTurn(Set<string> solutions){
	string word;
	int size = solutions.size();
	for(int i = 0; i < size; i++){
		word = solutions.first();
		if(word.length()>3){
			recordWordForPlayer(word, COMPUTER);
		}
		solutions.remove(word);
	}
}

