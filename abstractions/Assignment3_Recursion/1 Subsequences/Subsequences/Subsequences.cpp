/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    cout<<isSubsequence("sdaadsvsdvafgarefdbtgbjmukm", "dvfrjk")<<endl;
    return 0;
}

bool isSubsequence(string text, string subsequence){

	//base case
	if(subsequence.empty())return true;

	/*ocasion when length of text string is 1 and length of subsequence string
	is more than 1 or text[0] and subsequence[0] are not the same*/
	if(text.length() == 1 && (subsequence.length() > 1 ||
		subsequence[0] != text[0]))return false;

	//if subsequence[0] in text was found
	if(text[0] == subsequence[0])return isSubsequence(text.substr(1), subsequence.substr(1));

	//if subsequence[0] in text was not found
	if(text[0] != subsequence[0])return isSubsequence(text.substr(1), subsequence);
}